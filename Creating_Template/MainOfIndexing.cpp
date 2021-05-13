#include<iostream>
#include"Indexing.h"
#include<exception>
int main()
{
    try
    {
            std::string s="DatabaseFile.csv";
            createIndexing(s, "::","NewIndexing.txt");
            CreateTemplate("template.txt",s,",","NewIndexing.txt");
    }
    catch(std::exception e)
    {
        std::cout<<e.what();
    }
}