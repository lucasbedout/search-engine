#ifndef RANKING_H_INCLUDED
#define RANKING_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>

class Page{
public :
    int ID;
	std::vector<std::string> Keywords;
	std::string Text;
	std::string Title;
	std::string Url;

    //constructeur
	Page(std::vector<std::string> fKeywords,std::string fText,std::string fTitle,std::string fUrl);
	//constructeur copie
	Page& operator=(Page const& pageCopy);

};
Page::Page(std::vector<std::string> fKeywords,std::string fText,std::string fTitle,std::string fUrl) : Keywords(fKeywords), Text(fText), Title(fTitle), Url(fUrl)
{
    //rien
}

Page& Page::operator=(Page const& pageCopy)
{
    if(this != &pageCopy)
    //On vérifie que l'objet n'est pas le même que celui reçu en argument
    {
        int sizeW = pageCopy.Keywords.size();
        for(int i = 0; i<sizeW;i++ )
            Keywords.push_back( pageCopy.Keywords[i] ); // erreur ici

        Text = pageCopy.Text;

        Title = pageCopy.Title;

        Url = pageCopy.Url;
    }
    return *this; //On renvoie l'objet lui-même
}

#endif // RANKING_H_INCLUDED
