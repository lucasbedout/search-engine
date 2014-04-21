#ifndef SERVERASYN_H_INCLUDED
#define SERVERASYN_H_INCLUDED

#include <iostream>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

#include "..\Research\Rankings\ranking.h"

class tcp_connection
	: public boost::enable_shared_from_this<tcp_connection>
{
public:
	typedef boost::shared_ptr<tcp_connection> pointer;

	static pointer create(boost::asio::io_service& io_service)
	{
		return pointer(new tcp_connection(io_service));
	}

	boost::asio::ip::tcp::socket& socket()
	{
		return socket_;
	}

	void start()
	{
		/*message_ = "Hello world";

		boost::asio::async_write(socket_, boost::asio::buffer(message_),
			boost::bind(&tcp_connection::handle_write, shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));*/

		char buf[128] = "";
		char typeSearch[2] = { '0' };
		int nb = 0;
		std::string keyword;
		boost::system::error_code error;

		socket_.read_some(boost::asio::buffer(typeSearch), error);
		socket_.read_some(boost::asio::buffer(buf), error);

		nb = atoi(typeSearch);
		for (int i = 0; i<127 && buf[i] != '\0'; i++)
			keyword.push_back( buf[i] );

		std::cout << "Type recherche : " << nb << " et texte : " << keyword << std::endl;

		rank(keyword, nb);
	}

private:
	tcp_connection(boost::asio::io_service& io_service)
		: socket_(io_service)
	{
	}

	void handle_write(const boost::system::error_code& /*error*/,
		size_t /*bytes_transferred*/)
	{
	}
	void handle_read(const boost::system::error_code& /*error*/,
		size_t /*bytes_transferred*/)
	{
	}

	boost::asio::ip::tcp::socket socket_;
	std::string message_;
};

class tcp_server
{
public:
	tcp_server(boost::asio::io_service& io_service)
		: acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 13))
	{
		start_accept();
	}

private:
	void start_accept()
	{
		tcp_connection::pointer new_connection =
			tcp_connection::create(acceptor_.get_io_service());

		acceptor_.async_accept(new_connection->socket(),
			boost::bind(&tcp_server::handle_accept, this, new_connection,
			boost::asio::placeholders::error));
	}

	void handle_accept(tcp_connection::pointer new_connection,
		const boost::system::error_code& error)
	{
		if (!error)
		{
			new_connection->start();
		}

		start_accept();
	}

	boost::asio::ip::tcp::acceptor acceptor_;
};

#endif // SERVERASYN_H_INCLUDED
