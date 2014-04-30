#ifndef SERVERASYN_H_INCLUDED
#define SERVERASYN_H_INCLUDED

#include <iostream>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

#include "../Research/Rankings/ranking.h"

#define MAX_BUFFER_SEARCH_KEYWORDS 255

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
		char recieveSearch[MAX_BUFFER_SEARCH_KEYWORDS] = "";
		char reciveTypeSearch[2] = { '0' }, totalPageSend[7] = "";
		int typeSearch = 0;
		std::string keywords;
		boost::system::error_code error;

		socket_.read_some(boost::asio::buffer(reciveTypeSearch), error); // reçois le type de recherche
		socket_.read_some(boost::asio::buffer(recieveSearch), error); //reçois la chaine de caractère

		typeSearch = atoi(reciveTypeSearch); //convertie un char en int
		//Convertie le tableau static char en string
		for (int i = 0; i<(MAX_BUFFER_SEARCH_KEYWORDS-1) && recieveSearch[i] != '\0'; i++)
			keywords.push_back(recieveSearch[i]);

		std::cout << "Type recherche : " << typeSearch << " et texte : " << keywords << std::endl;

		std::vector<Page> page = rank(keywords, typeSearch); //ranking

		//-----ENVOIT PAGE-----
		itoa(page.size(), totalPageSend, 10); //nombre total page convertie en char
		boost::asio::async_write(socket_, boost::asio::buffer(totalPageSend),
			boost::bind(&tcp_connection::handle_write, shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));

		const int totalPage = page.size();
		for (int i = 0; i < totalPage; i++)
			sendPage(page.at(i));
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

	void sendPage(Page page)
	{
		std::string size = "0", content;

		content = "ID : "; content += std::to_string( page.get_ID() );
		content += "\nTitle : "; content += page.get_title();
		content += "\nUrl : "; content += page.get_url();
		size = std::to_string( content.size() );

		std::cout << "size : " << size << std::endl << "Content : " << content << std::endl;

		boost::asio::async_write(socket_, boost::asio::buffer(size),
			boost::bind(&tcp_connection::handle_write, shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));

		boost::asio::async_write(socket_, boost::asio::buffer(content),
			boost::bind(&tcp_connection::handle_write, shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));

		/*char size[7] = "";
		char content[100] = "";
		std::string tmp = "", tmp2 = "0";

		tmp = "ID : "; tmp += std::to_string(page.get_ID());
		tmp += "\nTitle : "; tmp += page.get_title();
		tmp += "\nUrl : "; tmp += page.get_url();
		tmp2 = std::to_string(tmp.size());

		const int tmpLgt = tmp.size()-1, tmpLgt2 = tmp2.size()-1;
		for (int i = 0; i < tmpLgt; i++)
			content[i] = tmp.at(i);
		for (int i = 0; i < tmpLgt2; i++)
			size[i] = tmp2.at(i);

		socket_.write_some(boost::asio::buffer(size));
		socket_.write_some(boost::asio::buffer(content));*/
	}

	boost::asio::ip::tcp::socket socket_;
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
