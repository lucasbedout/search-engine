#include <cstdlib>
#include <ctime>

#include "ranking.h"

using namespace std;

int nbWord(string chaine,string word);
vector<Page> ranking(vector<Page> pageFound,vector<string> rechercheUser);
void swapPage(int tableau[], vector<Page> page, int a, int b);
void quickSort(int tableau[],vector<Page> page,  int debut, int fin);

int main()
{
    //on voit le niveau de recherche que veux, l'utilisateur ( a faire après avoir réglé les bug)
    /*int level=2;
    cout << "Niveau de la recherche (1=tolerant;2=moderé{default};3=strict) : ";
    cin >> level;

    if(level!=1 && level!=2 && level!=3)
        level=2;*/

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
    listWord.push_back("Bateau"); listWord.push_back("Ocean"); listWord.push_back("Navigation");
    allPage.push_back(Page(listWord,textPage,titrePage,urlPage) );

    //page 2 : informatique
    titrePage="Informatique pour geek", urlPage="http://www.geek.com", textPage="Un geek aime l informatique car l informatique c est le futur. Le futur est notre maitre.";
    listWord.clear();
    listWord.push_back("Informatique"); listWord.push_back("Geek"); listWord.push_back("futur"); listWord.push_back("cheat"); listWord.push_back("cool");
    allPage.push_back(Page(listWord,textPage,titrePage,urlPage) );


    /*--------FIN---------------------*/

    ranking(allPage,keywordSearch);

    cout <<"Temps prit : "<< (t-clock()) <<  endl;

    return 0;
}

void swapPage(int tableau[], vector<Page> page, int a, int b)
{
    //variable temporaire
    Page tmp(page[a]);

    //Trie score
    tableau[a] ^= tableau[b];
    tableau[b] ^= tableau[a];
    tableau[a] ^= tableau[b];

    //Trie page
    page[a]=page[b];
    page[b]=tmp;
}

void quickSort(int tableau[],vector<Page> page,  int debut, int fin)
{
    int gauche = debut-1;
    int droite = fin+1;
    const int pivot = tableau[debut];

    if(debut >= fin)
        return ;

    while(1)
    {
        do droite--; while(tableau[droite] > pivot);
        do gauche++; while(tableau[gauche] < pivot);

        if(gauche < droite)
            swapPage(tableau, page, gauche, droite);
        else break;
    }

    quickSort(tableau, page, debut, droite);
    quickSort(tableau, page, droite+1, fin);
}

/*
CaseSensitive : Yes
If the word is seperate by space : No
*/
int nbWord(string chaine,string word)
{
    int nb(0),i(0),j(0),similaire(0);

    for(i=0;chaine[i]!='\0';i++)
    {
        if(chaine[i]==word[0])
        {
            for(j=1;word[j]!='\0' && chaine[i+j]!='\0';j++)
            {
                if(chaine[i+j]==word[j])
                    similaire++;
            }

            if( (j-1)==similaire)
                nb++;

            i+=(j-1);
            similaire=0;
        }
    }
    return nb;
}

vector<Page> ranking(vector<Page> pageFound,vector<string> rechercheUser)
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
            score[i]+=coefTitle*nbWord(pageFound[i].Title,rechercheUser[j]);
            cout << "Titre : " << score[i] << ' ';
            score[i]+=coefDomaineName*nbWord(pageFound[i].Url,rechercheUser[j]);
            cout << "Domaine : " << score[i] << ' ';
            for(int o=0; o<pageFound[i].Keywords.size();o++)
                score[i]+=coefKeyword*nbWord(pageFound[i].Keywords[o],rechercheUser[j]);
            cout << "Keywords : " << score[i] << ' ';
            score[i]+=coefUrl*nbWord(pageFound[i].Url,rechercheUser[j]);
            cout << "Url : " << score[i] << ' ';
            score[i]+=coefText*nbWord(pageFound[i].Text,rechercheUser[j]);
            cout << "Words : " << score[i] << endl;
        }

        cout << score[i] << " De :" << pageFound[i].Title << endl;
    }


    //------------------ETAPE 2----------------------

    //quickSort(score,pageFound,1,pageFound.size()); //erreur a réglé avant

    return pageFound;

}
