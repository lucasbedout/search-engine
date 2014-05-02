#include <string>
#include <vector>
#include "../Keywords/keywords.h"

#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

using namespace std;

class Parser{
private :
	string content_to_parse;
	bool parsed;
	string description_of_page;
	string title_of_page;
	Keywords k;
public :
	Parser(string content_to_parse_in);
	vector<string> parse();
	void cleanHTML();
	void parseAll();
	string getContent();
	string getDescription();
	string getTitle();
	void setContent(string content_in);
};

#endif
