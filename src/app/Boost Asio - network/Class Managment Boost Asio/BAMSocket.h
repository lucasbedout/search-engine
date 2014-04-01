#include <iostream>
#include <string>
#include <boost/asio.hpp>

#define DEFAULT_PORT 13

class BAMSocket{
private :
    boost::asio::io_service m_io_service;
    boost::asio::ip::tcp::socket m_socket;
public :
    //Constructeur de socket serveur
    BAMSocket()
    {
        try
        {
            boost::asio::ip::tcp::acceptor acceptor(m_io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), DEFAULT_PORT));
            m_socket(io_service);
			acceptor.accept(socket);
        }
        catch (std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    //constructeur de socket client
    BAMSocket(string adresseIp)
    {
        try
        {
            boost::asio::ip::tcp::resolver resolver(m_io_service);
            boost::asio::ip::tcp::resolver::query query(adresseIp);
            boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
            m_socket(m_io_service);
            boost::asio::connect(m_socket, endpoint_iterator);
        }
        catch (std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
};
