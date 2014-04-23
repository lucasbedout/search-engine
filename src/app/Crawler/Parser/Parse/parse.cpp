#include <tidy/tidy.h>
#include <tidy/buffio.h>
#include <vector>
#include <iostream>
#include <string>
#include <libxml++/libxml++.h>
#include <libxml++/parsers/textreader.h>
#include "parse.h"

using namespace std;

Parser::Parser(string content_to_parse_in){
	content_to_parse = content_to_parse_in;
	parsed = false;
	parsed_content = vector<string>();
}
 
void Parser::cleanHTML(){
    const string tmp = content_to_parse;
    TidyDoc tidyDoc = tidyCreate();
    TidyBuffer tidyOutputBuffer = {0};
    bool configSuccess = tidyOptSetBool(tidyDoc, TidyXmlOut, yes)
        && tidyOptSetBool(tidyDoc, TidyQuiet, yes)
        && tidyOptSetBool(tidyDoc, TidyNumEntities, yes)
        && tidyOptSetBool(tidyDoc, TidyShowWarnings, no);
    int tidyResponseCode = -1;
    if (configSuccess)
        tidyResponseCode = tidyParseString(tidyDoc, tmp.c_str());
    if (tidyResponseCode >= 0)
        tidyResponseCode = tidyCleanAndRepair(tidyDoc);
    if (tidyResponseCode >= 0)
        tidyResponseCode = tidySaveBuffer(tidyDoc, &tidyOutputBuffer);
    if (tidyResponseCode < 0)
        throw ("Tidy encountered an error while parsing an HTML response. Tidy response code: " + tidyResponseCode);
    string tidyResult = (char*)tidyOutputBuffer.bp;
    tidyBufFree(&tidyOutputBuffer);
    tidyRelease(tidyDoc);
    content_to_parse = tidyResult;
}

void Parser::findElement(string type){
      string current_node = "";
      try
      {
        xmlpp::TextReader reader("keywords.html");
        while(reader.read())
        {
          string tmp = reader.get_name();
          if (!tmp.compare(type))
          {
            current_node = tmp;
            reader.move_to_element();
          }
          else if (!tmp.compare("#text") && !current_node.compare(type))
            {
              cout << "value: '" << reader.get_value() << "'" << endl;
              current_node = "";
            }
        }
      }
      catch(const exception& e)
      {
        cerr << "Exception caught: " << e.what() << endl;
      }
}

string Parser::parse(string type){
    cleanHTML();
    findElement(type);
}

string Parser::getContent(){
    return this->content_to_parse;
}