#include "DatabaseManager.h"
#include <iostream>

int main(int argc, char const *argv[])
{
	std::vector<Page> pages;
	DatabaseManager manager("tcp://192.168.1.27:3306", "root", "bitnami", "searchengine");
	pages = manager.getPages("boulangerie motherfucking");
	int pages_size = pages.size();

	for(int i = 0 ; i < pages_size ; ++i) 
	{
		std::cout << "Page : " << pages[i].get_title() << std::endl;
		std::cout << "Contentu : " << pages[i].get_content() << std::endl;
	}

	return 0;
}