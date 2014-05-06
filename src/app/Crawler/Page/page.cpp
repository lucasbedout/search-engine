#include <vector>
#include <string>
#include <iostream>
#include "page.h"


Page::Page(vector<string> fKeywords,string fText,string fTitle,string fUrl,string fDescription) : _keywords(fKeywords), _content(fText), _title(fTitle), _url(fUrl), _description(fDescription)
{
    //rien
}

Page::Page(int id, vector<string> fKeywords, string fText, string fTitle, string fUrl, string fDescription) : _ID(id), _keywords(fKeywords), _content(fText), _title(fTitle), _url(fUrl), _description(fDescription)
{
	//rien
}

Page::Page(string url_in, string content){ //initialisation du parser
	_url = url_in;
	_content = content;
	Parser p = Parser(_content, _url);
	_keywords = p.parse();
	_title = p.getTitle();
	_description = p.getDescription();
    _links = p.getLinks();
};

Page& Page::operator=(Page const& pageCopy)
{
    if(this != &pageCopy)
    //On vérifie que l'objet n'est pas le même que celui reçu en argument
    {
		set_keywords(pageCopy._keywords);

        _content = pageCopy._content;

        _title = pageCopy._title;

        _url = pageCopy._url;

        _description = pageCopy._description;

		set_links(pageCopy._links);

    }
    return *this; //On renvoie l'objet lui-même
}

int Page::get_ID()
{
	return _ID;
}

string Page::get_content()
{
    return _content;
}

string Page::get_title()
{
    return _title;
}

string Page::get_url()
{
    return _url;
}

vector<string> Page::get_keywords()
{
    return _keywords;
}

string Page::get_description()
{
    return _description;
}

vector<string> Page::get_links()
{
    return _links;
}

void Page::set_content(const string content)
{
    _content = content;
}

void Page::set_title(const string title)
{
    _title = title;
}

void Page::set_url(const string url)
{
    _url = url;
}

void Page::set_keywords(const vector<string> keywords)
{
    const int sizeW = keywords.vector::size();
    _keywords.vector::clear(); //par sécurité
    for(int i = 0; i < sizeW;i++ )
        _keywords.push_back(keywords[i]);
}

void Page::set_description(const string description)
{
    _description = description;
}

void Page::set_links(const vector<string> links)
{
    const int sizeL = links.vector::size();
    _links.vector::clear();
    for(int i = 0; i < sizeL;i++ )
        _links.push_back(links[i]);
}

void Page::displayKeywords(){
	for (vector<string>::iterator it = _keywords.begin(); it != _keywords.end(); ++it){
		cout << *it << endl;
	}
}

void Page::displayLinks(){
    for (vector<string>::iterator it = _links.begin(); it != _links.end(); ++it){
        cout << *it << endl;
    }
}

