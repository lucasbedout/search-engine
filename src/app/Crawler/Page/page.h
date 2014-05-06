#ifndef PAGE_H_INCLUDED
#define PAGE_H_INCLUDED

#include <string>
#include <vector>
#include "../Parser/parse.h"


//-------------------------------------------CLASS PAGE--------------------------------

using namespace std;

class Page{
private :
    int _ID;
    string _title;
    string _url;
	vector<string> _keywords;
	string _description;
	string _content;
	vector<string> _links;

public :
    //constructeur
	Page(vector<string> fKeywords,string fText,string fTitle,string fUrl,string fDescription);
	Page(int id,vector<string> fKeywords,string fText,string fTitle,string fUrl,string fDescription);
	Page(string url, string content);
	//constructeur copie
	Page& operator=(Page const& pageCopy);
	//void displayKeywords();

	//getter
	int get_ID();
	string get_content();
	string get_title();
	string get_url();
	vector<string> get_keywords();
	string get_description();
	vector<string> get_links();

	//Setter
	void set_content(const string content);
	void set_title(const string title);
	void set_url(const string url);
	void set_keywords(const vector<string> keywords);
	void set_description(const string description);
	void set_links(const vector<string> links);

	//Fonction page
	void displayKeywords();
	void displayLinks();
};

//-------------------------------------------CLASS PAGE--------------------------------


#endif // PAGE_H_INCLUDED
