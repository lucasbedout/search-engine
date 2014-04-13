#include <cstdlib>
#include <ctime>
#include <limits>

#include "ranking.h"

using namespace std;

int main()
{
    //on voit le niveau de recherche que veux, l'utilisateur
    int level=2;
    cout << "Niveau de la recherche (1=tolerant;2=moderé{default};3=strict) : ";
    cin >> level;

    if(level!=1 && level!=2 && level!=3)
        level=2;

    //Vidons le buffer
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    cout << level <<endl;

    //on obtient la recherche user
    string recherche="",word="";
    vector<string> keywordSearch;
    cout << "Votre recherche : ";
    getline(cin, recherche);

    for(int i=0; recherche[i]!='\0';i++)
    {
        if(recherche[i]==' ')
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
    vector<Page> allPage;
    vector<Page> result;
    //page 1 : Sur le traitement des bateaux
    vector<string> listWord;
    string titrePage="Les bateaux sont cool.", urlPage="http://www.bateau-cool.com",textPage="Venez voir mes bateaux carrement classe. Venez les tester, la vie est cool !";
    listWord.push_back("Bateau"); listWord.push_back("Ocean"); listWord.push_back("Navigation"); listWord.push_back("Hexa");
    allPage.push_back(Page(listWord,textPage,titrePage,urlPage) );

    //page 2 : informatique
    titrePage="Informatique pour geek", urlPage="http://www.geek.com", textPage="Un geek aime l informatique car l informatique c est le futur. Le futur est notre maitre.";
    listWord.clear();
    listWord.push_back("informatique"); listWord.push_back("Geek"); listWord.push_back("futur"); listWord.push_back("cheat"); listWord.push_back("cool"); listWord.push_back("Gone");
    allPage.push_back(Page(listWord,textPage,titrePage,urlPage) );

    //page 3 : Jardin
    titrePage="Main verte du jardin enchante", urlPage="http://www.jardin.com", textPage="Un Jardin c'est la vie au plein air, c est vraiment le futur de toute maison.";
    listWord.clear();
    listWord.push_back("Jardin"); listWord.push_back("Vert"); listWord.push_back("Beau"); listWord.push_back("Nature"); listWord.push_back("fun");
    allPage.push_back(Page(listWord,textPage,titrePage,urlPage) );

    //page 4 : Futur
    titrePage="Le futur du monde dans nos main", urlPage="http://www.futur.com", textPage="Le futur est notre avenir, nous devons y croire et aider.";
    listWord.clear();
    listWord.push_back("Futur"); listWord.push_back("Avenir"); listWord.push_back("Espoir"); listWord.push_back("Univer");
    allPage.push_back(Page(listWord,textPage,titrePage,urlPage) );

    //page 2 : feu
    titrePage="Feu brulant si etincelant", urlPage="http://www.feu-for-ever.com", textPage="Le feu est un ellement sacre de notre chere planette Terre.";
    listWord.clear();
    listWord.push_back("Feu"); listWord.push_back("Brulant"); listWord.push_back("Beau"); listWord.push_back("Nature"); listWord.push_back("Etincelant");
    allPage.push_back(Page(listWord,textPage,titrePage,urlPage) );

    /*--------FIN---------------------*/

    ranking(allPage,keywordSearch,level);

    for(int i=0; i < allPage.size();i++)
    {
        cout << "Number " << i+1 << " : " << allPage[i].Title << endl;
    }

    cout <<"Temps prit : "<< (clock()-t) <<  endl;

    return 0;
}

void swapPage(int tableau[], vector<Page>& page,const int& a,const int& b)
{
    //page temporaire
    Page tmp=page[a];

    //Trie score
    tableau[a] ^= tableau[b];
    tableau[b] ^= tableau[a];
    tableau[a] ^= tableau[b];

    //Trie page
    page[a]=page[b];
    page[b]=tmp;

}

void quickSort(int tableau[],vector<Page>& page,const int debut,const int fin)
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

string lowerString(const string& str)
{
    const int lg=str.length();
    string low(str);

    for(int i=0; i < lg; i++)
    {
        if(low[i] >='A' && 'Z' >= low[i])
            // 'a'-'A'= 32 <=> 'A'+32='a'
            low[i]+=32;
    }

    return low;
}

/*
CaseSensitive : Yes(3) & No(2/1)
If the word is seperate by space : No
*/
int nbWord(const string& chaine,const string& word,const int& level)
{
    int nb(0),i(0),j(0),similaire(0);

    //Si le niveau est strict
    if(level == 3)
    {
        for(i=0;chaine[i] != '\0';i++)
        {
            if(chaine[i]==word[0])
            {
                for(j=1;word[j]!='\0' && chaine[i+j]!='\0' ;j++)
                {
                    if(chaine[i+j] == word[j])
                        similaire++;
                }

                // -2 car on commence a comparait a l'emplacement 0 (tab[0]) et qu'on commence similaire++ a 1.
                if( (word.size()-2) == similaire)
                    nb++;

                i+=(j-1);
                similaire=0;
            }
        }
    }
    //si il est modéré
    else if(level == 2)
    {
        string chaineLow(lowerString(chaine)), wordLow(lowerString(word));

        for(i=0;chaineLow[i] != '\0';i++)
        {
            if(chaineLow[i]==wordLow[0])
            {
                for(j=1;wordLow[j]!='\0' && chaineLow[i+j]!='\0';j++)
                {
                    if(chaineLow[i+j] == wordLow[j])
                        similaire++;
                }

                if( (wordLow.size()-2) == similaire)
                    nb++;

                i+=(j-1);
                similaire=0;
            }
        }

    }
    //Si il est tolerant
    else
    {
        /*
        --------------PROTOTYPE--------------
        Logique :
            Nous avons W qui est le mot rechercher et N tel que N=W.size()/2.
            Si dans la chaine de caractère nous avons une suite de lettre de W de la taille de N,
            Alors celui-ci est compter comme un mot.
        Avantage :
            Très tolérant :
                Permet d'analiser si n'importe quel partie de W est identifier (exemple : Bonjour =>bonjo | jour | onjou | bonjour | bonjou | ...)
                Ressort plus de résultat
                Monte des pages en raport (exemple : Hexagone => Hexa | gone )
        Desavantage :
            Très lent a cause de plusieurs recherche
            Peut ressortir des pages qui n'ont rien a voir a cause de la haute tolérance
        */
        string chaineLow(lowerString(chaine)), wordLow(lowerString(word));
        bool chaineBin[chaineLow.size()-2];
        int maxi=0,minSize=(int)(wordLow.size()/2);

        for(i=0;chaineLow[i] != '\0';i++) //on parcour la chaine
        {
            for(int iw=0; iw < minSize+1;iw++) //on parcour le word
            {
                if(chaineLow[i]==wordLow[iw])
                {
                    chaineBin[i]=true;
                    for(j=1;wordLow[j+iw]!='\0' && chaineLow[i+j]!='\0' && chaineBin[i+j-1]==true;j++)
                    {
                        if(chaineLow[i+j] == wordLow[j+iw])
                            chaineBin[i+j]=true;
                        else
                            chaineBin[i+j]=false;
                    }

                    if(maxi < j)
                        maxi = j;
                }
            }
            if(maxi < minSize)
            {
                for(int z=0; z<maxi; z++)
                    chaineBin[i+z]=false;
            }
            else
            {
                i+=maxi-1;
                nb++;
            }
        }


    }

    return nb;
}

void ranking(vector<Page>& pageFound,vector<string>& rechercheUser,const int& lvlSrch)
{
    int score[rechercheUser.size()];
    const int coefTitle=16,coefDomaineName=8,coefKeyword=4,coefUrl=2,coefText=1;

    //------------------ETAPE 1----------------------
    //Parcour de toute les pages
    for(int i=0; i<pageFound.size();i++)
    {
        score[i]=0;
        //parcour toute la recherche user
        for(int j=0; j<rechercheUser.size();j++)
        {
            score[i]+=coefTitle*nbWord(pageFound[i].Title,rechercheUser[j],lvlSrch);
            //cout << "Titre : " << score[i] << ' ';
            score[i]+=coefDomaineName*nbWord(pageFound[i].Url,rechercheUser[j],lvlSrch);
            //cout << "Domaine : " << score[i] << ' ';
            for(int o=0; o<pageFound[i].Keywords.size();o++)
                score[i]+=coefKeyword*nbWord(pageFound[i].Keywords[o],rechercheUser[j],lvlSrch);
            //cout << "Keywords : " << score[i] << ' ';
            score[i]+=coefUrl*nbWord(pageFound[i].Url,rechercheUser[j],lvlSrch);
            //cout << "Url : " << score[i] << ' ';
            score[i]+=coefText*nbWord(pageFound[i].Text,rechercheUser[j],lvlSrch);
            //cout << "Words : " << score[i] << endl;
        }

        cout << "Score : " << score[i] << " de :" << pageFound[i].Title << endl;
    }


    //------------------ETAPE 2----------------------

    quickSort(score,pageFound,0,pageFound.size()-1);

}
