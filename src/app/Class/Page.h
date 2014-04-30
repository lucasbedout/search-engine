#ifndef PAGE_H_INCLUDED
#define PAGE_H_INCLUDED

#include <string>
#include <vector>
#include "Crawler/Parser/Parse/parse.h"


//-------------------------------------------CLASS PAGE--------------------------------
class Page{
private :
    int _ID;
    std::string _title;
    std::string _url;
	std::vector<std::string> _keywords;
	std::string _description;
	std::string _content;
	std::vector<std::string> _links;
	//Parser _p;

public :
    //constructeur
	Page(std::vector<std::string> fKeywords,std::string fText,std::string fTitle,std::string fUrl,std:string fDescription);
	Page(int id,std::vector<std::string> fKeywords,std::string fText,std::string fTitle,std::string fUrl,std:string fDescription);
	Page(string url);
	//constructeur copie
	Page& operator=(Page const& pageCopy);
	//void displayKeywords();

	//getter
	int get_ID();
	std::string get_content();
	std::string get_title();
	std::string get_url();
	std::vector<std::string> get_keywords();
	std::string get_description();
	std::vector<std::string> get_links();

	//Setter
	std::string set_content(const std::string content);
	std::string set_title(const std::string title);
	std::string set_url(const std::string url);
	std::vector<std::string> set_keywords(const std::vector<std::string> keywords);
	std::string set_description(const std::string description);
	std::vector<std::string> set_links(const std::vector<std::string> links);

	//Fonction page
	//void Parse();

};
Page::Page(std::vector<std::string> fKeywords,std::string fText,std::string fTitle,std::string fUrl,std:string fDescription) : _keywords(fKeywords), _content(fText), _title(fTitle), _url(fUrl), _description(fDescription)
{
    //rien
}

Page::Page(int id, std::vector<std::string> fKeywords, std::string fText, std::string fTitle, std::string fUrl, std:string fDescription) : _ID(id), _keywords(fKeywords), _content(fText), _title(fTitle), _url(fUrl), _description(fDescription)
{
	//rien
}

/*Page::Page(string url_in) : k(),
						p("", k){ //initialisation du parser

	url = url_in;
	Keywords k = Keywords();
	FileHandler f = FileHandler(url);
	f.extractDatas();
	content = f.getContent();
	Parser p = Parser(content,k);
	title = p.getTitle();
	description = p.getDescription();
	k.displayKeywords();
};*/

Page& Page::operator=(Page const& pageCopy)
{
    if(this != &pageCopy)
    //On vérifie que l'objet n'est pas le même que celui reçu en argument
    {
        const int sizeW = pageCopy._keywords.vector::size();
        _keywords.vector::clear(); //par sécurité
        for(int i = 0; i < sizeW;i++ )
            _keywords.push_back(pageCopy._keywords[i]);

        _content = pageCopy._content;

        _title = pageCopy._title;

        _url = pageCopy._url;

        _description = pageCopy._description;

        const int sizeL = pageCopy._links.vector::size();
        _links.vector::clear(); //par sécurité
        for(int i = 0; i < sizeL;i++ )
            _links.push_back(pageCopy._links[i]);

    }
    return *this; //On renvoie l'objet lui-même
}

int Page::get_ID()
{
	return _ID;
}

std::string Page::get_content()
{
    return _content;
}

std::string Page::get_title()
{
    return _title;
}

std::string Page::get_url()
{
    return _url;
}

std::vector<std::string> Page::get_keywords()
{
    return _keywords;
}

std::string Page::get_description();
{
    return _description;
}

std::vector<std::string> Page::get_links();
{
    return _links;
}

std::string Page::set_content(const std::string content)
{
    _content = content;
}

std::string Page::set_title(const std::string title)
{
    _title = title;
}

std::string Page::set_url(const std::string url)
{
    _url = url;
}

std::vector<std::string> Page::set_keywords(const std::vector<std::string> keywords)
{
    const int sizeW = keywords.vector::size();
    _keywords.vector::clear(); //par sécurité
    for(int i = 0; i < sizeW;i++ )
        _keywords.push_back(keywords[i]);
}

std::string Page::set_description(const std::string description)
{
    _description = description;
}

std::vector<std::string> Page::set_links(const std::vector<std::string> links)
{
    const int sizeL = links.vector::size();
    _links.vector::clear();
    for(int i = 0; i < sizeL;i++ )
        _links.push_back(links[i]);
}


//-------------------------------------------CLASS PAGE--------------------------------


#endif // PAGE_H_INCLUDED
