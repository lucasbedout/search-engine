#include <string>
#include <iostream>

using namespace std;

class FileHandler{
private :
    char* path;
    string content;
public :
    FileHandler(string path);
    void extractDatas();
    string getContent();
};