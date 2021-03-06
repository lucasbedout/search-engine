#include <string>
#include <vector>
#include "../Page/page.h"

using namespace std;

/*

	********************
	** Header Crawler **
	********************

*/

class Crawler{
private :
	vector<string> _url;
	vector<Page> _pages;
public :
	Crawler(string url);
	void crawl();
	string downloadFile(string url);
	vector<Page> getPages();
};
