#include <cstdlib>
#include <ctime>
#include <limits>

#include "ranking.h"

using namespace std;

int main()
{
    //on voit le niveau de recherche que veux, l'utilisateur
    int level = 2;
    cout << "Niveau de la recherche (1=tolerant;2=moderé{default};3=strict) : ";
    cin >> level;

    if(level != 1 && level != 2 && level != 3)
        level = 2;

    //Vidons le buffer
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    //on obtient la recherche user
    string recherche="",word="";
    vector<string> keywordSearch;
    cout << "Votre recherche : ";
    getline(cin, recherche);

    for(int i=0; recherche[i]!='\0';i++)
    {
        if(recherche[i] == ' ')
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

    const int sizePage = allPage.size();
    for(int i=0; i < sizePage; i++)
    {
        cout << "Number " << i+1 << " : " << allPage[i].get_title() << endl;
    }

    cout <<"Temps prit : "<< ( clock()-t ) << "ms" <<  endl;

    return 0;
}
