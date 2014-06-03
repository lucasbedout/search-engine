#include <iostream>
#include <sstream>

#include "ranking.h"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc >= 2)
    {
        try
        {
            int level = 0;
            string recherche = "";

            istringstream ss(argv[1]);
            if (!(ss >> level))
            {
                cerr << "Invalid number " << argv[1] << '\n';
                return 0;
            }

            for(int i = 2; i < argc; i++)
                recherche += argv[i] + std::string(" ");
            cout << recherche << endl;

            std::vector<Page> allPage = ranked(recherche, level);

            const int sizePage = allPage.vector::size();
            for(int i = 0; i < sizePage; i++)
                cout << allPage.at(i).to_JSON();

        } catch(exception e)
        {
            cout << e.what() << endl;
        }

    }
    else
        cout << "You must enter parameters. Use : ./program <level> <keywords>";
    return 0;
}
