#include <string>
#include <vector>

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