#include<iostream>
#include"virtualClass.h"
class Two:public virtualClass
{
    public:
    Two(){
        std::cout<<"hi constructor!!!"<<std::endl;
    } 
    int Run()
    {
        std::cout<<"Start Program in Two CLass"<<std::endl;
        return 0;
    }
};
virtualClass * theApp=new Two();