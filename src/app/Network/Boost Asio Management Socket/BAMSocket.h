#include <iostream>
#include <string>
#include <vector>
#include <boost/asio.hpp>

#define DEFAULT_PORT 13

class BAMSocket{
private :
    boost::asio::io_service m_io_service;
	boost::asio::ip::tcp::socket *m_socket;
public :
    //Constructeur de socket serveur
	BAMSocket();
    //constructeur de socket client
	BAMSocket(std::string adresseIp);

	void send(std::string message);
	std::vector<std::string> recive();
	std::string getInfoConnect();
};

BAMSocket::BAMSocket()
{
	try
	{
		boost::asio::ip::tcp::acceptor acceptor(m_io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), DEFAULT_PORT));
		boost::asio::ip::tcp::socket socket(m_io_service);
		acceptor.accept(socket);
		m_socket = &socket;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}


BAMSocket::BAMSocket(std::string adresseIp)
{
	try
	{
		boost::asio::ip::tcp::resolver resolver(m_io_service);
		boost::asio::ip::tcp::resolver::query query(adresseIp);
		boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		boost::asio::ip::tcp::socket socket(m_io_service);
		boost::asio::connect(socket, endpoint_iterator);
		m_socket = &socket;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

void BAMSocket::send(std::string message)
{
	try
	{
		boost::system::error_code ignored_error;
		boost::asio::write(*m_socket, boost::asio::buffer(message), ignored_error);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

std::vector<std::string> BAMSocket::recive()
{
	try
	{
		std::vector<std::string> message;
		boost::system::error_code error;

		m_socket->read_some(boost::asio::buffer(message), error);

		if (error != boost::asio::error::eof)
			throw boost::system::system_error(error); // Some other error.
		return message;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

std::string BAMSocket::getInfoConnect()
{
	std::string info;
	info = m_socket->remote_endpoint().address().to_string() + ':';
	//info = info + m_socket.remote_endpoint().port();

	return info;
}