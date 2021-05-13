#include<iostream>
using namespace std;
class T
{
    public:
    T()
    {
        cout<<"Constructor!!!!T: "<<endl;
    }

    ~T()
    {
        cout<<"Destructor!!T: "<<endl;
    }
};
class A
{
    T obj;
    T obj2;
    int f;
    public:
    A(int d,T t,T t1):obj2(t1),f(d),obj(t)
    {
        cout<<"Constructor A!!"<<endl;
    }
};
class B
{
   T obj;
    public:
    B(T t)
    {
        cout<<"Constructor B!!"<<endl;
        obj=t;
    }
};
int main()
{
    T t;
    T t2;
    A a(4,t2,t);
    B b(t);
}