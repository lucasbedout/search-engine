#include <string>
#include <vector>
#include "Parser/Page/page.h"

using namespace std;

class Crawler{
private :
	vector<string> _url;
	vector<Page> _pages;
public :
	Crawler(string url);
	void crawl();
	string downloadFile(string url);
};
