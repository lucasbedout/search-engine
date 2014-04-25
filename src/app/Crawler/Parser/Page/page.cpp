#include <string>
#include <vector>
#include <iostream>
#include "page.h"
#include "../File/file.h"
#include "../Keywords/keywords.h"
#include "../Parse/parse.h"
#include "../Misc/misc.h"

using namespace std;

Page::Page(string url_in) : k(),
							p("", &k){ //initialisation du parser
	url = url_in;
	/*FileHandler f = FileHandler(url);
	f.extractDatas();
	content = f.getContent();
	p.setContent(content);*/
};

string Page::getContent(){
	return content;
}

void Page::displayKeywords(){
	vector<string> toto = k.getKeywords();
	for (vector<string>::iterator it = toto.begin(); it != toto.end(); ++it)
	{
		cout << *it << " ! " << endl;
	}
}