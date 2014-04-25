#include <string>
#include <vector>

#ifndef KEYWORDS_H_INCLUDED
#define KEYWORDS_H_INCLUDED

using namespace std;

class Keywords{
private :
	struct Datas {
		vector<string> words;
		vector<int> values;
	};
public :
	Keywords();
	void addWords(string string_to_insert, string type);
	void addKeyword(string keyword, string type);
	void removeKeyword(string keyword);
	int findPosition(string keyword);
	vector<int> getValues();
	vector<string> getKeywords();
};

#endif
