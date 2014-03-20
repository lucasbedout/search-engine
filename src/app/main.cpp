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
    cout << keywords[1];
}
