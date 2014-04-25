#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include "keywords.h"
#include "../Misc/misc.h"

using namespace std;

Keywords::Keywords(){
	Datas d;
	d.words = vector<string>();
	d.values = vector<int>();
}

void Keywords::addWords(string string_to_insert, string type){
	vector<string> tmp = splitString(string_to_insert);
	for(vector<T>.iterator it = tmp.begin(); it != tmp.end(); ++it) {
		addKeyword(*it, type);
	}
}

void Keywords::addKeyword(string keyword, string type){
	removePunctuation(keyword);
	if (find(begin(d.words), end(d.words), keyword) != end(d.words))
    {

    }
}

void Keywords::removeKeyword(string keyword){

}

int Keywords::findPosition(string keyword){

}
