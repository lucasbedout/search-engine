#include <iostream>
#include <string>
#include <vector>
#include "Misc/misc.h"
#include "File/file.h"
#include "Parse/parse.h"

using namespace std;

int main()
{
    vector<string> keywords;
    FileHandler f = FileHandler("keywords.html");
    f.extractDatas();
    Parser p = Parser(f.getContent());
    p.getMetas();
}
