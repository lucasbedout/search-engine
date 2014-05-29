#include "misc.h"
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

//Création de la fonction value of type qui permettra d'assigner une valeur à un keyword

int findNth(string str, char c, int n){
    int pos = 0;
    for(std::string::iterator it = str.begin(); it != str.end(); ++it) {
        if(n > 0){
            pos++;
            if (*it == c)
                n--;
        }
    }
    if (n == 0)
        return pos;
    else
        return -1;
}

int valueOfType(string type){
    int value;
    if (type == "meta")
        value = 10;
    else if (type == "h1" || type == "description")
        value = 7;
    else if (type == "strong" || type == "em")
        value = 6;
    else if (type == "h2" || type == "italic" || type == "bold")
        value = 5;
    else if (type == "h3")
        value = 4;
    else if (type == "h4" || type == "h5")
        value = 3;
    else if (type == "h6")
        value = 2;
    else
        value = 1;
    return value;
}

bool has_suffix(const std::string &str, const std::string &suffix)
{
    return str.size() >= suffix.size() &&
           str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

string removeWhiteSpaces(string text){
    int spaces = 0;
    for(int i = 0; i < text.length(); i++) {
        if(text.at(i) == '\\s+'){
            //cout << "found space !" << endl;
            spaces++;
        }
        else if (text.at(i) == '<'){
            //cout << "found <" << endl;
            i = text.length();
        }
    }
    text.erase(0,spaces);
    //cout << "2" << text.substr(0,100) << endl;
    return text;
}

string extractHost(string url_in){
    string final_host;
    int pos;
    url_in = url_in + "/";
    if (url_in.find("http://") == 0){
        final_host = url_in.substr(0,findNth(url_in, '/',3));
    }
    else{
        final_host = "";
    }
    return final_host;
}

//Création de la fonction qui va retirer la ponctuation des mots clé.
void removePunctuation(string &keyword){
    string result_space;
    string result;
    remove_copy_if(keyword.begin(), keyword.end(),
                        back_inserter(result_space),
                        ptr_fun<int, int>(&isspace)
    );
    remove_copy_if(result_space.begin(), result_space.end(),
                        back_inserter(result),
                        ptr_fun<int, int>(&ispunct)
                       );
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    keyword = result;
}

//Fonction pour chercher si le keyword est un mot simple ou pas
bool simpleWord(string keyword){
    bool test = true;
    if(keyword.size()>3)
        test = false;
    return test; // La fonction reste à élaborder. C'est pour le moment trop basique
}


vector<string> splitString(string content, char special_char){
    stringstream ss(content);
    string word;
    vector<string> keywords;
    while (getline(ss, word, special_char)) {
            removePunctuation(word);
        if (!simpleWord(word))
            keywords.push_back(word);
    }
    return keywords;
}
