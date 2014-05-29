#include <tidy/tidy.h>
#include <tidy/buffio.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <libxml++/libxml++.h>
#include <libxml++/parsers/textreader.h>
#include "parse.h"
#include "../Misc/misc.h"

using namespace std;

Parser::Parser(string content_to_parse_in, string url_in){ //travail par référence
  content_to_parse = removeWhiteSpaces(content_to_parse_in);
  plain_text = "";
  parsed = false;
  url = extractHost(url_in);
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
        && tidyOptSetBool(tidyDoc, TidyForceOutput, yes)
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
    cout << "tidy cleaned HTML" << endl;
}

void Parser::parseAll(){
  cout << "parsing !" << endl;
      string current_node = "";
      try
      {
        xmlpp::TextReader reader((const unsigned char*)content_to_parse.c_str(), content_to_parse.size(), "");
        do
        {
          cout << "crawling : " << reader.get_name() << endl;
          string tmp = reader.get_name();
          if(tmp.compare("#text")){
            current_node = tmp;
            reader.move_to_element();
          }
          else if (!tmp.compare("#text"))
          {
            if (current_node.compare("title") && current_node.compare("script"))
              {
                string tmp_txt = reader.get_value();
                tmp_txt.erase(std::remove(tmp_txt.begin(), tmp_txt.end(), '\n'), tmp_txt.end());
                plain_text += tmt_txt;
              }
            if (!title_of_page.compare("") && !current_node.compare("title")){
              title_of_page = reader.get_value();
              title_of_page.erase(std::remove(title_of_page.begin(), title_of_page.end(), '\n'), title_of_page.end());
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
              if (reader.get_value().find("description") != std::string::npos)
                desc = true;
              else if (!reader.get_value().compare("keywords"))
                key = true;
              else if (!reader.get_name().compare("href"))
                link = true;
              if (!reader.get_name().compare("content") && desc == true)
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
              if (link == true)
                {
                  int pos = 0;
                  if (links.size() > 0)
                    pos = find(links.begin(), links.end(), reader.get_value()) - links.begin();
                  if (pos == 0 || pos >= links.size() && reader.get_value() != "#")
                    {
                      if (reader.get_value().find(url) == 0 
                        && reader.get_value().find("mailto") == std::string::npos 
                        && reader.get_value().find("http") == std::string::npos)
                        {
                          links.push_back(reader.get_value());
                          cout << reader.get_value() << endl;
                        }
                      else if (reader.get_value().find("http://") == std::string::npos 
                        && reader.get_value().find("@") == std::string::npos 
                        && reader.get_value().find("?") == std::string::npos
                        && reader.get_value().find("//") == std::string::npos)
                      {
                        string tmp_reader = reader.get_value();
                        cout << reader.get_value();
                        if (tmp_reader.find("/") == 0)
                          links.push_back(url+tmp_reader.substr(1,tmp_reader.size()));
                        else
                          links.push_back(url+reader.get_value());
                      }
                    }
                  link = false;
                }
            } while(reader.move_to_next_attribute());
          }
        
}        while (reader.read());
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
    string tmp = content_to_parse.substr(0,100);
    cout << tmp << endl << "tata" << endl;
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

string Parser::getPlainText(){
  return plain_text;
}