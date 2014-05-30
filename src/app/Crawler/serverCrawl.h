#ifndef SERVERASYN_H_INCLUDED
#define SERVERASYN_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

#include "Crawl/crawler.h"
#include "../Database/DatabaseManager.h"

#define PORT_NUMBER 12
#define MAX_BUFFER_URL 255

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
		char url[MAX_BUFFER_URL]="";
		boost::system::error_code error;

		socket_.read_some(boost::asio::buffer(url), error); 
		crawling(url);
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

	void crawling(string url)
	{
		Crawler c = Crawler(url);
	}

	boost::asio::ip::tcp::socket socket_;
};

class tcp_server
{
public:
	tcp_server(boost::asio::io_service& io_service)
		: acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PORT_NUMBER))
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