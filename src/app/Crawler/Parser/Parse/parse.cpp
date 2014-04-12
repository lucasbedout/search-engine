#include <tidy/tidy.h>
#include <tidy/buffio.h>
#include <vector>
#include <iostream>
#include <string>
#include <libxml++/libxml++.h>
#include <libxml++/parsers/textreader.h>
#include "parse.h"

using namespace std;

struct indent {
  int depth_;
  indent(int depth): depth_(depth) {};
};

std::ostream & operator<<(std::ostream & o, indent const & in)
{
  for(int i = 0; i != in.depth_; ++i)
  {
    o << "  ";
  }
  return o;
}

Parser::Parser(string content_to_parse_in){
	content_to_parse = content_to_parse_in;
	parsed = false;
	parsed_content = vector<string>();
}
 
void Parser::cleanHTML(){
    const string tmp = content_to_parse;
    // Initialize a Tidy document
    TidyDoc tidyDoc = tidyCreate();
    TidyBuffer tidyOutputBuffer = {0};
 
    // Configure Tidy
    // The flags tell Tidy to output XML and disable showing warnings
    bool configSuccess = tidyOptSetBool(tidyDoc, TidyXmlOut, yes)
        && tidyOptSetBool(tidyDoc, TidyQuiet, yes)
        && tidyOptSetBool(tidyDoc, TidyNumEntities, yes)
        && tidyOptSetBool(tidyDoc, TidyShowWarnings, no);
 
    int tidyResponseCode = -1;
 
    // Parse input
    if (configSuccess)
        tidyResponseCode = tidyParseString(tidyDoc, tmp.c_str());
 
    // Process HTML
    if (tidyResponseCode >= 0)
        tidyResponseCode = tidyCleanAndRepair(tidyDoc);
 
    // Output the HTML to our buffer
    if (tidyResponseCode >= 0)
        tidyResponseCode = tidySaveBuffer(tidyDoc, &tidyOutputBuffer);
 
    // Any errors from Tidy?
    if (tidyResponseCode < 0)
        throw ("Tidy encountered an error while parsing an HTML response. Tidy response code: " + tidyResponseCode);
 
    // Grab the result from the buffer and then free Tidy's memory
    string tidyResult = (char*)tidyOutputBuffer.bp;
    tidyBufFree(&tidyOutputBuffer);
    tidyRelease(tidyDoc);
    
    content_to_parse = tidyResult;
}

void Parser::findElement(string type){

      try
      {
        xmlpp::TextReader reader("keywords.html");

        while(reader.read())
        {
          int depth = reader.get_depth();
          std::cout << indent(depth) << "--- node ---" << std::endl;
          std::cout << indent(depth) << "name: " << reader.get_name() << std::endl;
          std::cout << indent(depth) << "depth: " << reader.get_depth() << std::endl;
          if(reader.has_attributes())
          {
            std::cout << indent(depth) << "attributes: " << std::endl;
            reader.move_to_first_attribute();
            do
            {
              std::cout << indent(depth) << "  " << reader.get_name() << ": " << reader.get_value() << std::endl;
            } while(reader.move_to_next_attribute());
            reader.move_to_element();
          }
          else
          {
            std::cout << indent(depth) << "no attributes" << std::endl;
          }

          if(reader.has_value())
            std::cout << indent(depth) << "value: '" << reader.get_value() << "'" << std::endl;
          else
            std::cout << indent(depth) << "novalue" << std::endl;

        }
      }
      catch(const std::exception& e)
      {
        std::cerr << "Exception caught: " << e.what() << std::endl;
      }
	/*xmlpp::DomParser doc;
	
	// 'response' contains your HTML
	doc.parse_memory(content_to_parse);
	 
	xmlpp::Document* document = doc.get_document();
	xmlpp::Element* root = document->get_root_node();
	 
	xmlpp::NodeSet elemns = root->find(type);
	cout << elemns[0]->get_line() << endl;
	cout << elemns.size() << endl;*/
}

string Parser::parse(string type){
    cleanHTML();
    findElement(type);
}

string Parser::getContent(){
    return this->content_to_parse;
}