// g++ OverLoadedMain.cpp
#include"OverLoadedAVL.h" 
class UserDefined
{
    int v;
    public:
        
        UserDefined():v(0)
        {
        }
        UserDefined(int v1):v(v1)
        {
        } 
        void DisplayUserDef()                  //Function for what to display 
        {
            cout<<v;
        }
        friend ostream& operator << (ostream& out,UserDefined &c)  // operator overloaded 
        {
            c.DisplayUserDef();
            return out;
        }
        bool operator <(UserDefined &p2);          //Function for what to compare
        bool operator >(UserDefined &p2);          //Function for what to compare
        bool operator ==(UserDefined &p2);         //Function for what to compare
       
};
bool UserDefined::operator ==(UserDefined &p2)
{                                    
    if(v==p2.v)
    {
        return true;
    }
    else
    {
      return false;
    }   
}
bool UserDefined :: operator >(UserDefined &p2)
{   
    if(v > p2.v)
    {
        return true;
    }
    else
    {
        return false;
    }                                
            
}
bool UserDefined :: operator <(UserDefined &p2)
{                               
    if(v < p2.v)
    {
        return true;
    }
     else
    {
        return false;
    }        
}
int main()
{
    try{

            // User defined Data Type

            AVL<UserDefined> tree;
            UserDefined s(10);
            UserDefined s1(20);
            UserDefined s2(30);
            UserDefined s3(40);
            UserDefined s4(50);
            UserDefined s5(25);
            UserDefined s6(32);
            tree.insert(s);
            tree.insert(s1);
            tree.insert(s2);
            tree.insert(s3);
            tree.insert(s4);
            tree.insert(s5);
            tree.insert(s6);
            cout<<"Order of User defined data Type:";
            tree.display();
            cout<<endl;
            tree.erase(s2);
            cout<<"Order of User defined data Type After deleting a node:";
            tree.display();

            //Primitivee data Type

            AVL<int> tree2;
            tree2.insert(10);
            tree2.insert(20);
            tree2.insert(30);
            tree2.insert(40);
            tree2.insert(50);
            tree2.insert(25);
            cout<<endl;
            cout<<"Order of primitive defined data Type:";
            cout<<endl;
            tree2.display();
            cout<<endl;
            tree2.erase(30);
            cout<<endl;
            cout<<"Order of primitive defined data Type After deleting a node:";
            tree2.display();
        }
    catch(string e)
    {
        cout<<e;
    }
    catch(exception e)
    {
        cout<<"Exception Occured!!!"<<e.what();
    }
    catch(...)
    {
        cout<<"Exception Occur!!!";
    }

}