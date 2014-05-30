#include "serverCrawl.h"

using boost::asio::ip::tcp;

int main()
{
	try
	{
		//On lance le service d'entrer et sortie de Boost
		boost::asio::io_service io_service;
		//Nous créons un server en indiquant son mode asynchrone
		tcp_server server(io_service);
		//Nous lançons le serveur asynchrone
		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}