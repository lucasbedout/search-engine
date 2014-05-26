#include <vector>
#include <iostream>
#include <string>
#include <curl/curl.h>
#include "Crawl/crawler.h"
#include "Misc/misc.h"
#include "../Database/DatabaseManager.h"
#include "Page/page.h"

using namespace std;

int main(){
	Crawler c = Crawler("http://fr.openclassrooms.com/");
	DatabaseManager manager = DatabaseManager("tcp://192.168.1.27:3306", "root", "bitnami", "searchengine");
	vector<Page> pages = c.getPages();
	for(std::vector<Page>::iterator it = pages.begin(); it != pages.end(); ++it) {
    	manager.savePage(*it);
	}
} 