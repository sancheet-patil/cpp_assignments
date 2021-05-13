#include<iostream>
#include"virtualClass.h"

extern virtualClass * theApp;
int main()
{
	theApp->Run();
}