//renommer dossier misc

#include <string>
#include <vector>

using namespace std;

int valueOfType(string type);
void removePunctuation(string &keyword);
bool simpleWord(string keyword);
vector<string> splitString(string content, char special_char);
bool has_suffix(const std::string &str, const std::string &suffix);
string extractHost(string url_in);
int findNth(string str, char c, int n);
string removeWhiteSpaces(string text);
void replaceQuotes(string& string_to_change);
vector<string> splitKeywords(string content, char special_char);
