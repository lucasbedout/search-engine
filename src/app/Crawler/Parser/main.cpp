#include <iostream>
#include <string>
#include <vector>
#include "Misc/misc.h"
#include "File/file.h"

using namespace std;

int main()
{
    vector<string> keywords;
    FileHandler f = FileHandler("keywords.txt");
    f.extractDatas();
    keywords = splitString(f.getContent(), ' ');
    int i = 0;
    for (i = 0; i < keywords.size(); i++)
        cout << keywords[i] << endl;
}
