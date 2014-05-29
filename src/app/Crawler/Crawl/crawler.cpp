#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <curl/curl.h>
#include "crawler.h"
#include "../Misc/misc.h"
#include "../../Database/DatabaseManager.h"

using namespace std;

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
		for (int i = 0; i < _url.size(); i++)
		{ 
			cout << "starting download ..." << endl;
			string tmp = downloadFile(_url[i]);
			if (tmp != ""){
				cout << "starting new page : " << _url[i] << endl;
				Page p = Page(_url[i],tmp);
				cout << "crawling : " << _url[i] << endl;
				vector<string> tmp = p.get_links();
				_pages.push_back(p);
				int sizeTmp = tmp.size();
				for(int k = 0; k < sizeTmp; k++)
				{
					if (find(_url.begin(), _url.end(), tmp[k]) - _url.begin() == _url.size())
		        		{
		        			if (!has_suffix(tmp[k],".css") && !has_suffix(tmp[k],".js")){
		        					_url.push_back(tmp[k]);
		        				}
		        		}
		        }
		        if (p.get_title() == ""){
	        		p.set_title(p.get_url());
		        }
		        if (p.get_description() == ""){
		        	p.set_description(p.get_plain_text().substr(0,200));
		        }
		        cout << "title : " << p.get_title() << endl;
		        cout << "description : " << p.get_description() << endl;
				DatabaseManager manager = DatabaseManager("tcp://192.168.1.27:3306", "root", "bitnami", "searchengine");
				manager.savePage(p);
		    }
	    }
	    crawling = false;
	}
}

string Crawler::downloadFile(string url){
	CURL *curl;
	CURLcode res;
	string readBuffer;
    long http_code = 0;
	const string url_tmp = url;
	 
	curl = curl_easy_init();
	if(curl) {
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

	/* Perform the request, res will get the return code */ 
	res = curl_easy_perform(curl);
	curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
	/* Check for errors */ 
	if(res != CURLE_OK)
	  fprintf(stderr, "curl_easy_perform() failed: %s\n",
	          curl_easy_strerror(res));

	/* always cleanup */ 
	curl_easy_cleanup(curl);
	}
	cout << "download ok :" << http_code << endl;
	if (http_code == 200)
		return readBuffer;
	else
		return "";
}

vector<Page> Crawler::getPages(){
	return _pages;
}