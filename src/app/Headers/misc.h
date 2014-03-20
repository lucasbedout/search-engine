#include <string>
#include <vector>
#ifndef MISC_H_INCLUDED
#define MISC_H_INCLUDED

using namespace std;

int valueOfType(string type);
void removePunctuation(string &keyword);
bool simpleWord(string keyword);
vector<string> splitString(string content, char special_char);

#endif // MISC_H_INCLUDED
