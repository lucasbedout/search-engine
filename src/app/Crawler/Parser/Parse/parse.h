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
public :
	Parser(string content_to_parse_in, Keywords* k_in);
	void parse();
	void cleanHTML();
	void getMetas();
	void findElement(string type);
	string getContent();
	void setContent(string content_in);
};

#endif
