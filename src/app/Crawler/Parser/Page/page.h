#include <string>
#include <vector>
#include '../Keywords/keywords.h'
#include '../Parse/parse.h'

#ifndef PAGE_H_INCLUDED
#define PAGE_H_INCLUDED

using namespace std;

class Page{
private :
	Parser p;
	string url;
	string content;
	string title;
	string description;
	Keywords k;
public :
	Page();
};

#endif
