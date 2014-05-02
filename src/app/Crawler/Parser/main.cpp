#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Misc/misc.h"
#include "File/file.h"
#include "Parse/parse.h"
#include "Page/page.h"
#include "Keywords/keywords.h"

using namespace std;

int main(){
   Page p = Page("keywords.html");
   p.displayKeywords();
}
