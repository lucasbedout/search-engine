#include <iostream>
#include <fstream>
#include <string>
#include "file.h"

using namespace std;

FileHandler::FileHandler(string path_entered){
    path = (char*)path_entered.c_str();
    content = "";
}

void FileHandler::extractDatas(){
    string line;
    ifstream myfile (this->path);
    if (myfile.is_open())
    {
        while (getline(myfile,line))
        {
            content += line;
        }
        myfile.close();
    }
    else
        cout << "Unable to open file";
}

string FileHandler::getContent(){
    return this->content;
}