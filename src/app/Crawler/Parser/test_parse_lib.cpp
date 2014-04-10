#include <tidy/tidy.h>
#include <tidy/buffio.h>
#include <iostream>
#include <string>
#include <libxml++/libxml++.h>
 
std::string CleanHTML(const std::string &html){
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
        tidyResponseCode = tidyParseString(tidyDoc, html.c_str());
 
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
    std::string tidyResult = (char*)tidyOutputBuffer.bp;
    tidyBufFree(&tidyOutputBuffer);
    tidyRelease(tidyDoc);
 
    return tidyResult;
}

int main()
{
	std::cout << "hello world !" << std::endl;
	xmlpp::DomParser doc;
	 
	// 'response' contains your HTML
	doc.parse_memory(CleanHTML("<html></html>"));
	 
	xmlpp::Document* document = doc.get_document();
	xmlpp::Element* root = document->get_root_node();
	 
	xmlpp::NodeSet elemns = root->find("descendant-or-self::*[@id = 'some_id']");
	std::cout << elemns[0]->get_line() << std::endl;
	std::cout << elemns.size() << std::endl;
}
