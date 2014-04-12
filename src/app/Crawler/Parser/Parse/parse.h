#include <string>
#include <vector>

#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

using namespace std;

class Parser{
private :
	string content_to_parse;
	bool parsed;
	vector<string> parsed_content;
public :
	Parser(string content_to_parsee_in);
	string parse(string type);
	void cleanHTML();
	void findElement(string type);
	string getContent();
};

#endif
