#include <string>
#include <vector>

#ifndef KEYWORDS_H_INCLUDED
#define KEYWORDS_H_INCLUDED

using namespace std;

struct Datas {
		vector<string> words;
		vector<int> values;
	};

class Keywords{
private :
	Datas d;
public :
	Keywords();
	void addWords(string string_to_insert, string type);
	void addWords(string string_to_insert, string type, char splitter);
	void addKeyword(string keyword, string type);
	int findPosition(string keyword);
	vector<int> getValues();
	vector<string> getKeywords();
	void displayKeywords();
};

#endif
