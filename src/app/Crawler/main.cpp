#include <vector>
#include <iostream>
#include <string>
#include <curl/curl.h>
#include "Crawl/crawler.h"
#include "Misc/misc.h"
#include "Page/page.h"

using namespace std;

int main(){
	Crawler c = Crawler("http://stackoverflow.com/questions/23914686/parsing-ssl-traffic-in-pcap-file-using-python"); 
}