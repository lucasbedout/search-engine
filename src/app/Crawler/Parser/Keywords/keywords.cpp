#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include "keywords.h"
#include "../Misc/misc.h"

using namespace std;

Keywords::Keywords(){
	Datas d;
}

void Keywords::addWords(string string_to_insert, string type){
	vector<string> tmp = splitString(string_to_insert, ' ');
	for(vector<string>::iterator it = tmp.begin(); it != tmp.end(); ++it) {
		addKeyword(*it, type);
	}
}

void Keywords::addKeyword(string keyword, string type){
	removePunctuation(keyword);
	int pos = 0;
	cout << "words : " << d.words.size() << endl << "values : " << d.values.size() << endl;
	/*if (d.words.size() > 0)
		pos = findPosition(keyword);
	if (pos < d.words.size() && d.words.size() > 0){
		d.values[pos] += valueOfType(type);
	}*/
	/*else{
		d.words.push_back(keyword);
		d.values.push_back(valueOfType(type));
	}*/
}

int Keywords::findPosition(string keyword){
	return find(d.words.begin(), d.words.end(), keyword) - d.words.begin();
}

vector<string> Keywords::getKeywords(){
	return this->d.words;
}