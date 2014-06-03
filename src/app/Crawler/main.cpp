#include <vector>
#include <iostream>
#include <string>
#include <curl/curl.h>
#include "Crawl/crawler.h"
#include "Misc/misc.h"
#include "Page/page.h"

using namespace std;

int main(int argc, char* argv[]){
	string value_passed = "";

	for(int i = 1; i < argc; i++) 
	  	value_passed += argv[i];

	Crawler c = Crawler(value_passed);
	return 0;
}
