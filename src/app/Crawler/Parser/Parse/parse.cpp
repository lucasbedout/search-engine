#include <tidy/tidy.h>
#include <tidy/buffio.h>
#include <vector>
#include <iostream>
#include <string>
#include <libxml++/libxml++.h>
#include <libxml++/parsers/textreader.h>
#include "parse.h"

using namespace std;

Parser::Parser(string content_to_parse_in, Keywords& k){ //travail par référence
	content_to_parse = content_to_parse_in;
	parsed = false;
  if (content_to_parse != "")
  {
    k.addKeyword("toto","h1");
    if (content_to_parse != ""){
      parse(k);
    }
  }
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

void Parser::getMetas(Keywords& k){
  vector<string> words;
  string current_node = "";
  try
      {
        xmlpp::TextReader reader("keywords.html");
        while(reader.read())
        {
          string tmp = reader.get_name();
          if (!tmp.compare("title")){
            current_node = tmp;
            reader.move_to_element();
          }
          else if (!tmp.compare("#text") && !current_node.compare("title"))
          {
            title_of_page = reader.get_value();
            cout << "title : " << title_of_page << endl;
            k.addWords(title_of_page, "meta");
            current_node = reader.get_name();
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
                description_of_page = reader.get_value();
                k.addWords(description_of_page, "meta");
                desc = false;
              }
            else if (!reader.get_name().compare("content") && key == true)
              {
                k.addWords(reader.get_value(), "meta", ',');
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

void Parser::parse(Keywords &k){
    cleanHTML();
    getMetas(k);
}

string Parser::getContent(){
    return content_to_parse;
}

void Parser::setContent(string content_in){
  content_to_parse = content_in;
}

string Parser::getDescription(){
  return description_of_page; 
}

string Parser::getTitle(){
  return title_of_page;
}