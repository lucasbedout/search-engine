#include <vector>
#include <iostream>
#include <string>
#include <curl/curl.h>
#include "crawler.h"

using namespace std;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

Crawler::Crawler(string url){
	_url.push_back(url);
	cout << downloadFile(_url[0]) << endl;
	Page p = Page(_url[0],downloadFile(_url[0]));
}

void Crawler::crawl(){

}

string Crawler::downloadFile(string url){
	CURL *curl;
	CURLcode res;
	string readBuffer;
	 
	curl = curl_easy_init();
	if(curl) {
	curl_easy_setopt(curl, CURLOPT_URL, "http://www.toto.fr");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

	/* Perform the request, res will get the return code */ 
	res = curl_easy_perform(curl);
	/* Check for errors */ 
	if(res != CURLE_OK)
	  fprintf(stderr, "curl_easy_perform() failed: %s\n",
	          curl_easy_strerror(res));

	/* always cleanup */ 
	curl_easy_cleanup(curl);
	}
	return readBuffer;
}