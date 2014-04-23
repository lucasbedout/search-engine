#include <string>
#include <vector>

#ifndef KEYWORDS_H_INCLUDED
#define KEYWORDS_H_INCLUDED

using namespace std;

class Keywords{
private :
	struct Links {
		vector<string> words;
		vector<int> values;
	};
public :
	Keywords();
	void addKeyword(string keyword, int value);
	void removeKeyword(string keyword, int value);
	vector<int> getValues();
	vector<string> getKeywords();
};

#endif
