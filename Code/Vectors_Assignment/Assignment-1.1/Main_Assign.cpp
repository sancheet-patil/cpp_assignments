//Run these file with following command g++ Main_Assign.cpp
#include"Skeleton.h"    
using namespace std;
class sancheet{
	public:
	int v;
	sancheet()
	{
		v=45;
	}
};
int main() {	
	vectorClass<sancheet> v;
	{
		sancheet s;
		try
		{
			v.pushBack(s);
			/*v.pushBack("3");
			v.pushBack("10");
			v.pushBack("8");
			v.pushBack("20");
			v.pushBack("74");
			v.pushBack("222");*/
			vectorClass<sancheet> v2=v;
			vectorClass<sancheet> v3;
			v3=v2;
			//v3[1]="20000";
			vectorClass<sancheet>::iterator itr = v.begin();
			while(itr!=v.end())
			{
				cout<<itr->v<<endl;
				++itr;
			}
			cout <<"Size of Vector: "<< v.size() << endl;
			vectorClass<sancheet>::iterator itr1 = v2.begin();
			while(itr1!=v2.end())
			{
				cout<<itr1->v<<endl;
				++itr1;
			}
			cout<<"CapaCity of Vector:"<<v.CapaCity()<<endl;
			vectorClass<sancheet>::iterator itr2 = v3.begin();
			while(itr2!=v3.end())
			{
				cout<<itr2->v<<endl;
				++itr2;
			}
		}
		catch(bad_alloc e)
		{
			cout<<"New Allocation Failed !!!"<<e.what();
		}
		catch(string w)
		{
			cout<<w;
		}
		catch(...)
		{
			cout<<"Exception Occured!!!";
		}
		return 0;
	}
}