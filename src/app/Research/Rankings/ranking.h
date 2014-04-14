#ifndef RANKING_H_INCLUDED
#define RANKING_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>


//-------------------------------------------CLASS PAGE--------------------------------
class Page{
private :
    int _ID;
	std::vector<std::string> _keywords;
	std::string _text;
	std::string _title;
	std::string _url;

public :
    //constructeur
	Page(std::vector<std::string> fKeywords,std::string fText,std::string fTitle,std::string fUrl);
	Page(int id,std::vector<std::string> fKeywords,std::string fText,std::string fTitle,std::string fUrl);
	//constructeur copie
	Page& operator=(Page const& pageCopy);

	//getter
	std::string get_text();
	std::string get_title();
	std::string get_url();
	std::vector<std::string> get_keywords();

};
Page::Page(std::vector<std::string> fKeywords,std::string fText,std::string fTitle,std::string fUrl) : _keywords(fKeywords), _text(fText), _title(fTitle), _url(fUrl)
{
    //rien
}

Page::Page(int id,std::vector<std::string> fKeywords,std::string fText,std::string fTitle,std::string fUrl)
{
    _ID=id;
    Page(fKeywords, fText, fTitle, fUrl);
}

Page& Page::operator=(Page const& pageCopy)
{
    if(this != &pageCopy)
    //On vérifie que l'objet n'est pas le même que celui reçu en argument
    {
        const int sizeW = pageCopy._keywords.vector::size();
        _keywords.clear(); //par sécurité
        for(int i = 0; i < sizeW;i++ )
            _keywords.push_back(pageCopy._keywords[i]);

        _text = pageCopy._text;

        _title = pageCopy._title;

        _url = pageCopy._url;
    }
    return *this; //On renvoie l'objet lui-même
}

std::string Page::get_text()
{
    return _text;
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

//-------------------------------------------CLASS PAGE--------------------------------


int nbWord(const std::string& chaine,const std::string& word,const int& level);
void ranking(std::vector<Page>& pageFound,std::vector<std::string>& rechercheUser,const int& lvlSrch);
void swapPage(int tableau[], std::vector<Page>& page,const int& a,const int& b);
void quickSort(int tableau[],std::vector<Page>& page,const int& debut,const int& fin);
std::string lowerString(const std::string& str);


#endif // RANKING_H_INCLUDED
