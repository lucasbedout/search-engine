#ifndef RANKING_H_INCLUDED
#define RANKING_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

#include "../../Class/Page.h"

std::vector<Page> rank(std::string recherche, int level); // Va chercher dans la base de donnée les pages, sort les mots clé dans la chaine de recherche
int nbWord(const std::string& chaine,const std::string& word,const int& level); // Compte le nombre de mot (3 niveaux)
void ranking(std::vector<Page>& pageFound,std::vector<std::string>& rechercheUser,const int& lvlSrch); //Attribue un score puis trie
void swapPage(int tableau[], std::vector<Page>& page,const int& a,const int& b); //échange les pages a et b ainsi que le score a et b
void quickSort(int tableau[],std::vector<Page>& page,const int& debut,const int& fin); //Trie les pages en fonction du score
std::string lowerString(const std::string& str); //Met une chaine de charactère en minuscule

std::vector<Page> rank(std::string recherche, int level)
{
	//on obtient la recherche user
	std::string word = "";
	std::vector<std::string> keywordSearch;

	for (int i = 0; recherche[i] != '\0'; i++)
	{
		if (recherche[i] == ' ')
		{
			word.push_back('\0');
			keywordSearch.push_back(word);
			word.clear();
		}
		else
			word.push_back(recherche[i]);
	}
	word.push_back('\0');
	keywordSearch.push_back(word);
	word.clear();

	//initialisation du temps
	srand(time(0));
	clock_t t;
	t = clock();

	/*---------CREATION PAGE-----------*/
	std::vector<Page> allPage;
	std::vector<Page> result;
	//page 1 : Sur le traitement des bateaux
	std::vector<std::string> listWord;
	std::string titrePage = "Les bateaux sont cool.", urlPage = "http://www.bateau-cool.com", textPage = "Venez voir mes bateaux carrement classe. Venez les tester, la vie est cool !";
	listWord.push_back("Bateau"); listWord.push_back("Ocean"); listWord.push_back("Navigation"); listWord.push_back("Hexa");
	allPage.push_back(Page(1,listWord, textPage, titrePage, urlPage));

	//page 2 : informatique
	titrePage = "Informatique pour geek", urlPage = "http://www.geek.com", textPage = "Un geek aime l informatique car l informatique c est le futur. Le futur est notre maitre.";
	listWord.clear();
	listWord.push_back("informatique"); listWord.push_back("Geek"); listWord.push_back("futur"); listWord.push_back("cheat"); listWord.push_back("cool"); listWord.push_back("Gone");
	allPage.push_back(Page(2, listWord, textPage, titrePage, urlPage));

	//page 3 : Jardin
	titrePage = "Main verte du jardin enchante", urlPage = "http://www.jardin.com", textPage = "Un Jardin c'est la vie au plein air, c est vraiment le futur de toute maison.";
	listWord.clear();
	listWord.push_back("Jardin"); listWord.push_back("Vert"); listWord.push_back("Beau"); listWord.push_back("Nature"); listWord.push_back("fun");
	allPage.push_back(Page(3, listWord, textPage, titrePage, urlPage));

	//page 4 : Futur
	titrePage = "Le futur du monde dans nos main", urlPage = "http://www.futur.com", textPage = "Le futur est notre avenir, nous devons y croire et aider.";
	listWord.clear();
	listWord.push_back("Futur"); listWord.push_back("Avenir"); listWord.push_back("Espoir"); listWord.push_back("Univer");
	allPage.push_back(Page(4, listWord, textPage, titrePage, urlPage));

	//page 2 : feu
	titrePage = "Feu brulant si etincelant", urlPage = "http://www.feu-for-ever.com", textPage = "Le feu est un ellement sacre de notre chere planette Terre.";
	listWord.clear();
	listWord.push_back("Feu"); listWord.push_back("Brulant"); listWord.push_back("Beau"); listWord.push_back("Nature"); listWord.push_back("Etincelant");
	allPage.push_back(Page(5, listWord, textPage, titrePage, urlPage));

	/*--------FIN---------------------*/

	ranking(allPage, keywordSearch, level);

	const int sizePage = allPage.size();
	for (int i = 0; i < sizePage; i++)
	{
		std::cout << "Number " << i + 1 << " : " << allPage[i].get_title() << std::endl;
	}

	std::cout << "Temps prit : " << (clock() - t) << "ms" << std::endl;

	return allPage;
}

void swapPage(int tableau[], std::vector<Page>& page,const int& a,const int& b)
{
    //page temporaire
    Page tmp = page[a];

    //Trie score
    tableau[a] ^= tableau[b];
    tableau[b] ^= tableau[a];
    tableau[a] ^= tableau[b];

    //Trie page
    page[a] = page[b];
    page[b] = tmp;

}

void quickSort(int tableau[],std::vector<Page>& page,const int& debut,const int& fin)
{
    int gauche = debut-1;
    int droite = fin+1;
    const int pivot = tableau[debut];

    if(debut >= fin)
        return ;

    while(1)
    {
        do droite--; while(tableau[droite] < pivot);
        do gauche++; while(tableau[gauche] > pivot);

        if(gauche < droite)
            swapPage(tableau, page, gauche, droite);
        else break;
    }

    quickSort(tableau, page, debut, droite);
    quickSort(tableau, page, droite+1, fin);
}

std::string lowerString(const std::string& str)
{
    const int lg = str.length();
    std::string low(str);

    for(int i = 0; i < lg; i++)
    {
        if(low[i] >='A' && 'Z' >= low[i])
            // 'a'-'A'= 32 <=> 'A'+32='a'
            low[i] += 32;
    }

    return low;
}

int nbWord(const std::string& chaine,const std::string& word,const int& level)
{
    int nb(0), i(0), j(0), similaire(0);

    //Si le niveau est strict
    if(level == 3)
    {
        for(i = 0; chaine[i] != '\0'; i++) //parcour de la chaine
        {
            if(chaine[i] == word[0])
            {
                for(j=1; word[j] != '\0' && chaine[i+j] != '\0'; j++) //comparaison lettre par lettre
                {
                    if(chaine[i+j] == word[j])
                        similaire++;
                }

                // -2 car on commence a comparait a l'emplacement 0 (tab[0]) et qu'on commence similaire++ a 1.
                if( (int)(word.size()-2) == similaire)
                    nb++;

                i += (j-1);
                similaire = 0;
            }
        }
    }
    //si il est modéré
    else if(level == 2)
    {
        std::string chaineLow(lowerString(chaine)), wordLow(lowerString(word));

        for(i=0;chaineLow[i] != '\0';i++)
        {
            if(chaineLow[i] == wordLow[0])
            {
                for(j=1; wordLow[j] != '\0' && chaineLow[i+j] != '\0'; j++)
                {
                    if(chaineLow[i+j] == wordLow[j])
                        similaire++;
                }

                if( (int)(wordLow.size()-2) == similaire)
                    nb++;

                i+=(j-1);
                similaire=0;
            }
        }

    }
    //Si il est tolerant
    else
    {
        std::string chaineLow(lowerString(chaine)), wordLow(lowerString(word));
        std::vector<bool>chaineBin( chaineLow.size() - 2 );
        int maxi = 0, minSize = (int)(wordLow.size()/2);

        for(i = 0; chaineLow[i] != '\0'; i++) //on parcour la chaine
        {
            for(int iw = 0; iw < minSize+1; iw++) //on parcour le word
            {
                if(chaineLow[i] == wordLow[iw]) //Si la première lettre est identique
                {
                    chaineBin[i] = true;
                    for(j = 1; wordLow[j+iw] != '\0' && chaineLow[i+j] != '\0' && chaineBin[i+j-1] == true; j++) //on compare
                    {
                        if(chaineLow[i+j] == wordLow[j+iw])
                            chaineBin[i+j] = true; //On a une similitude !
                        else
                            chaineBin[i+j] = false;
                    }

                    if(maxi < j)
                        maxi = j;
                }
            }
            if(maxi < minSize) // si on trouve aucun word similaire faisant plus de la moitier du word, on initialise le tableau binaire
            {
                for(int z = 0; z < maxi; z++)
                    chaineBin[i+z] = false;
            }
            else //si la chaine identique la plus longue est supérieur ou égal a la moitier du word
            {
                i += maxi - 1;
                nb++;
            }
        }


    }

    return nb;
}

void ranking(std::vector<Page>& pageFound,std::vector<std::string>& rechercheUser,const int& lvlSrch)
{
	//Alocation dynamique du score en fonction du nombre de page
	int *score = new int( rechercheUser.size() );
    const int coefTitle = 16, coefDomaineName = 8, coefKeyword = 4, coefUrl = 2, coefText = 1, sizePage = pageFound.size();
    const int sizeSearch = rechercheUser.size();

    //------------------ETAPE 1----------------------
    //Parcour de toute les pages
    for(int i = 0; i < sizePage; i++)
    {
        score[i] = 0;
        //parcour toute la recherche user
        for(int j = 0; j < sizeSearch; j++)
        {
            score[i] += coefTitle * nbWord( pageFound[i].get_title(), rechercheUser[j], lvlSrch);
            //cout << "Titre : " << score[i] << ' ';
            score[i] += coefDomaineName * nbWord( pageFound[i].get_url(), rechercheUser[j], lvlSrch);
            //cout << "Domaine : " << score[i] << ' ';
            const int sizeKeyword = pageFound[i].get_keywords().size();
            for(int o = 0; o < sizeKeyword; o++)
                score[i] += coefKeyword * nbWord( pageFound[i].get_keywords()[o], rechercheUser[j], lvlSrch);
            //cout << "Keywords : " << score[i] << ' ';
            score[i] += coefUrl * nbWord( pageFound[i].get_url(), rechercheUser[j], lvlSrch);
            //cout << "Url : " << score[i] << ' ';
            score[i] += coefText * nbWord( pageFound[i].get_text(), rechercheUser[j], lvlSrch);
            //cout << "Words : " << score[i] << endl;
        }

        //cout << "Score : " << score[i] << " de :" << pageFound[i].Title << endl;
    }


    //------------------ETAPE 2----------------------

    quickSort( score, pageFound, 0, pageFound.size()-1 );

}


#endif // RANKING_H_INCLUDED
