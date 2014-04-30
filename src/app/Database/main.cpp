#include "DatabaseManager.h"
#include <iostream>

int main(int argc, char const *argv[])
{
	std::vector<Page> pages;
	std::vector<string> keywords;
	keywords.push_back("coucou ");
	keywords.push_back("motherfucking ");
	keywords.push_back("update ");

	Page insertion(keywords, "Tu sais que t'es un motherfucking son of a bitch connard ? Update. Allez je te laisse la page", "Do you know ?", "http://connard.com", "C'est ta mère la description enculé, update again");
	DatabaseManager manager("tcp://192.168.1.27:3306", "root", "bitnami", "searchengine");
	pages = manager.getPages("boulangerie motherfucking website");
	int pages_size = pages.size();

	for(int i = 0 ; i < pages_size ; ++i) 
	{
		std::cout << "Page : " << pages[i].get_title() << std::endl;
		std::cout << "Contentu : " << pages[i].get_content() << std::endl;
	}

	if(manager.savePage(insertion)) 
	{
		std::cout << "Success !" << endl;
	}	
	return 0;
}