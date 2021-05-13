#include <iostream>
#include<string>
#include<exception>
using namespace std;

template <class T>
class vectorClass
{
    private:
        T* arr;             // array buffer for storage 
        int size_arr;       // size of vector
        int capaCity ;      //capacity of vector
        
    public:
    
     typedef T* iterator;       //user defined datatype for iterator
     
     //Initializer
        vectorClass()throw(bad_alloc);                              // default constructor
        ~vectorClass();                             //vector class destructor
        vectorClass( vectorClass& x) throw(bad_alloc);               //copy constructor
        vectorClass& operator= (vectorClass& x) throw(bad_alloc);        //= operator


    //iterators
        T * begin();            // return begin of vector
        T * end();              // return end of vector
        
    //Modifiers
        void pushBack(T) throw(bad_alloc);           // push in the container 
        void pop() throw (string);                 // delete element from back
        
    //Acess Elements
        T& operator[](int ) throw(string); 
        T& at(int ) const throw (char const*);            // return element  at nth index
        
    //Capacity
        int size();             //return size of vector
        int CapaCity();         // return capacity of vector
        bool emPty();
};
// Defination
template<class T>
bool vectorClass<T>::emPty()
{
    if(size_arr==0)
    {
        return true;
    }
    else{
        return false;
    }
}
template<class T>
vectorClass<T>::vectorClass(vectorClass& x) throw(bad_alloc)
{
    this->size_arr=x.size_arr;
    this->capaCity=x.capaCity;
    delete[] arr;
    this->arr=new T[x.capaCity];
    for(int pos=0;pos<=size_arr;pos++)
    {
        this->arr[pos]=x.arr[pos];
    }
}

template<class T>
vectorClass<T>::vectorClass() throw(bad_alloc)
{
    size_arr=0;
    capaCity=1;
    arr=new T[capaCity];
    
}

template<class T>
vectorClass<T>& vectorClass<T>:: operator= (vectorClass& x) throw(bad_alloc)
{
    this->size_arr=x.size_arr;
    this->capaCity=x.capaCity;
    delete[] this->arr;
    this->arr=new T[capaCity];
    
    for(int pos=0;pos<=size_arr;pos++)
    {
        this->arr[pos]=x.arr[pos];
    }
    return *this;
}

template<class T>
void vectorClass<T>::pushBack(T Element) throw(bad_alloc)

{
    if(size_arr==capaCity)
    {
        capaCity=capaCity*2;
        T *temp;
        temp=arr;
            arr=new T[capaCity];           
            for(int pos =0;pos<size_arr;pos++)
                     arr[pos]=temp[pos];
            arr[size_arr]=Element;
        free(temp);
    }
    else
    {
        arr[size_arr]=Element;
    }
    size_arr++;
}

template<class T>
void vectorClass<T>::pop() throw (string)
{
    if(size_arr==0)
    {
        throw string("Empty Vector!!");
    }
    else
        size_arr--;
}

template<class T>
T* vectorClass<T>::begin()
{
    return arr;
}

template<class T>
int vectorClass<T>::size()
{
    return size_arr;
}

template<class T>
T& vectorClass<T>::operator[] (int n) throw (string)
{    
        if(n < capaCity)
    {
        T& ref = arr[n]; 
        return ref;
    }
    else
    {
        throw string("Element not found!!!");
    }
}

template<class T>
T& vectorClass<T>::at (int n) const throw (const char *)
{
    if(n < size_arr)
    {
        T& ref = arr[n]; 
        return ref;
    }
    else
    {
        throw string("Element not found!!!");
    }
}

template<class T>
T* vectorClass<T>::end()
{
    return &arr[size_arr];
}

template<class T>
int vectorClass<T>::CapaCity()
{
    return capaCity;
}
template<class T>
vectorClass<T>::~vectorClass()
{
    cout<<"Destructor called!!!"<<endl;
    delete[] arr;
    size_arr = 0;
    capaCity = 0; 
}

