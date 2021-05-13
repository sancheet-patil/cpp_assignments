#include<iostream>
#include"virtualClass.h"
class One:public virtualClass
{
    public:
    One(){
        std::cout<<"hi constructor!!!";
    } 
    int Run()
    {
        std::cout<<"Start Program in One CLass"<<std::endl;
        return 0;
    }
};
virtualClass * theApp=new One();