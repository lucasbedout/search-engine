#include <iostream>
#include <ctime>
#include <boost/array.hpp>
#include <boost/asio.hpp>

#define MAX_BUFFER 255

using boost::asio::ip::tcp;

void receivePage(tcp::socket &socket);

int main(int argc, char* argv[])
{
	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage: client <host>" << std::endl;
			return 1;
		}

		boost::asio::io_service io_service;

		tcp::resolver resolver(io_service);
		tcp::resolver::query query(argv[1], "daytime");
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

		tcp::socket socket(io_service);
		boost::asio::connect(socket, endpoint_iterator);

		//----------On saisie les infos --------------------
		//on voit le niveau de recherche que veux, l'utilisateur
		int level = 2;
		std::cout << "Niveau de la recherche (1=tolerant;2=moderé{default};3=strict) : ";
		std::cin >> level;

		if (level != 1 && level != 2 && level != 3)
			level = 2;

		//Vidons le buffer
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		//on obtient la recherche user
		std::string recherche = "";
		std::cout << "Votre recherche : ";
		std::getline(std::cin, recherche);

		//--------FIN DE LA SAISIE-----

		//------ON INITIALISE LE TEMPS-------
		//initialisation du temps
		srand(time(0));
		clock_t t;
		t = clock();

		for (;;)
		{
			//on met le string dans un tableau statique
			char buf[255] = "";
			const int sizeRecherche = recherche.size();
			for (int i = 0; i < 128 && i <sizeRecherche; i++)
				buf[i] = recherche[i];
			char typeSearchChar[2] = { '2' }, totalPageFound[7] = "";
			itoa(level, typeSearchChar,10);


			boost::system::error_code error;

			//size_t len = socket.read_some(boost::asio::buffer(buf), error);
			socket.write_some(boost::asio::buffer(typeSearchChar), error);
			socket.write_some(boost::asio::buffer(buf), error);

			socket.read_some(boost::asio::buffer(totalPageFound), error);

			//Reçois toute les pages
			const int nbPage = atoi(totalPageFound);
			for (int i = 0; i < nbPage; i++)
			{
				std::cout << "------PAGE " << i + 1 << "------" << std::endl;
				receivePage(socket);
				std::cout << std::endl;
			}

			if (error == boost::asio::error::eof)
				break; // Connection closed cleanly by peer.
			else if (error)
				throw boost::system::system_error(error); // Some other error.

			std::cout << "Page found : " << totalPageFound << " on " << (clock() - t) << "ms." << std::endl;
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}

void receivePage(tcp::socket &socket)
{
	// 1. on reçois la taille du blocs texte et 2. on reçois le blocs
	std::vector<char> size(7);
	boost::system::error_code error;

	socket.read_some(boost::asio::buffer(size), error);
	std::vector<char> page(atoi(size.data()) +1 );
	socket.read_some(boost::asio::buffer(page), error);

	if (error)
		throw boost::system::system_error(error); // Some other error.

	std::cout << page.data() << std::endl;

}