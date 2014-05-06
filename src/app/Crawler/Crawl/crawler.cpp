#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <curl/curl.h>
#include "crawler.h"

using namespace std;

bool has_suffix(const std::string &str, const std::string &suffix)
{
    return str.size() >= suffix.size() &&
           str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) //fonction pour récupérer le texte de la page. On est obligé de passer par un buffer.
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

Crawler::Crawler(string url){
	_url.push_back(url);
	crawl();
}

void Crawler::crawl(){
	bool crawling = true;
	while (crawling == true){	
		for (int j = 0; j < _url.size(); j++)
		{
			Page p = Page(_url[0],downloadFile(_url[0]));
			cout << "crawling : " << _url[0] << endl;
			p.displayKeywords();
			p.displayLinks();
			vector<string> tmp = p.get_links();
			_pages.push_back(p);
			int sizeTmp = tmp.size();
			for(int i = 0; i < sizeTmp; i++)
			{
				if (find(_url.begin(), _url.end(), tmp[i]) - _url.begin() == _url.size())
	        		{
	        			if (has_suffix(tmp[i],".php") || has_suffix(tmp[i],".html") || has_suffix(tmp[i],".aspx"))
	        				_url.push_back(tmp[i]);
	        		}
	        }
	        _url.erase(_url.begin());
	        if (_url.size() == 0)
	        	crawling = false;
	    }
	}
}

string Crawler::downloadFile(string url){
	CURL *curl;
	CURLcode res;
	string readBuffer;
	const string url_tmp = url;
	 
	curl = curl_easy_init();
	if(curl) {
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
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