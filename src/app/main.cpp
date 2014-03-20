#include <iostream>
#include <string>
#include <vector>
#include "Headers/misc.h"

using namespace std;

int main()
{
    vector<string> keywords;
    string test = "Voici, une string à test !";
    keywords = splitString(test, ' ');
    int i = 0;
    for (i = 0; i < keywords.size(); i++)
        cout << keywords[i] << endl;
}