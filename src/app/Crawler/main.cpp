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
} 