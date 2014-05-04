#include <tidy/tidy.h>
#include <tidy/buffio.h>
#include <vector>
#include <iostream>
#include <string>
#include <libxml++/libxml++.h>
#include <libxml++/parsers/textreader.h>
#include "parse.h"

using namespace std;

Parser::Parser(string content_to_parse_in, string url_in){ //travail par référence
	content_to_parse = content_to_parse_in;
	parsed = false;
  url = url_in;
  links = vector<string>();
  k = Keywords();
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

void Parser::parseAll(){
      string current_node = "";
      try
      {
        xmlpp::TextReader reader((const unsigned char*)content_to_parse.c_str(), content_to_parse.size(), "");
        do
        {
          string tmp = reader.get_name();
          if(tmp.compare("#text")){
            current_node = tmp;
            reader.move_to_element();
          }
          else if (!tmp.compare("#text"))
          {
            if (!title_of_page.compare("") && !current_node.compare("title")){
              title_of_page = reader.get_value();
              cout << "title : " << title_of_page << endl;
              k.addWords(title_of_page, "meta");
              current_node = reader.get_name();
            }
            else if(current_node.compare("") && current_node.compare("script") && current_node.compare("style")){
              k.addWords(reader.get_value(), current_node);
              current_node = "";
            }
            string tmp_str = reader.get_value();
          }
         if(reader.has_attributes() && (!current_node.compare("meta") || !current_node.compare("a")))
          {
            reader.move_to_first_attribute();
            bool desc = false;
            bool key = false;
            bool link = false;
            do
            {
              if (!reader.get_value().compare("description"))
                desc = true;
              else if (!reader.get_value().compare("keywords"))
                key = true;
              else if (!reader.get_value().compare("href"))
                link = true;
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
              else if (!reader.get_name().compare("content") && link == true)
                {
                  links.push_back(reader.get_value());
                  link = false;
                }
              else
                desc = false;
            } while(reader.move_to_next_attribute());
          }
        }
        while (reader.read());
      }
      catch(const exception& e)
      {
        cerr << "Exception caught: " << e.what() << endl;
      }
}

vector<string> Parser::getLinks(){
  return links;
}

std::vector<string> Parser::parse(){
    cleanHTML();
    parseAll();
    k.sortKeywords();
    vector<string> k_tmp = k.getKeywords();
    vector<string> returned;
    for(vector<string>::iterator it = k_tmp.begin(); it != k_tmp.begin()+20; ++it) {
        returned.push_back(*it);
    }
    return returned;
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