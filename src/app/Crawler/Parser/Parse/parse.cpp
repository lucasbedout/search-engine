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
        do
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
        while (reader.read());
      }
      catch(const exception& e)
      {
        cerr << "Exception caught: " << e.what() << endl;
      }
}

void Parser::getMetas(){
  string type = "title";
  vector<string> words;
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
            cout << "title : " << reader.get_value()<< endl;
            current_node = "";
          }
         if(reader.has_attributes())
          {
          reader.move_to_first_attribute();
          bool desc = false;
          bool key = false;
          do
          {
            if (!reader.get_value().compare("description"))
              desc = true;
            else if (!reader.get_value().compare("keywords"))
              key = true;
            else if (!reader.get_name().compare("content") && desc == true)
              {
                cout << "description : " << reader.get_value() << endl;
                desc = false;
              }
            else if (!reader.get_name().compare("content") && key == true)
              {
                cout << "keywords : " << reader.get_value() << endl;
                key = false;
              }
            else
              desc = false;
          } while(reader.move_to_next_attribute());
          reader.move_to_element();
        }
      }
  }catch(const exception& e)
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