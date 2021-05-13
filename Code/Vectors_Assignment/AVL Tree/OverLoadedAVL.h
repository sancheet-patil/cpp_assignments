// Header file 
#include<iostream>
#include<string>
#include<exception>
using namespace std;
template <class T>
class Node                                          //single node
{
   public:
        T data;
        Node<T>* left;
        Node<T>* right;
        int height;
        Node():data(NULL),left(NULL),right(NULL),height(1)
        {

        }
        Node(T element):data(element),left(NULL),right(NULL),height(1)
        {

        }
};
template <class T>
class AVL                                   // AVLTree Class 
{
    Node<T>* head= NULL;
    Node<T>* push(Node<T>* head,T element) noexcept(false);
    int height(Node<T>* root);
    int balance(Node<T>* root);
    Node<T>* leftRotation(Node<T>* root);
    Node<T>* InOrderSucessor(Node<T>* head);
    int max(int x, int y);
    Node<T>* rightRotation(Node<T>* root);
    Node<T>* deleteNode(Node<T>*head,T element) noexcept(false);
     void displayPre(Node<T>*root);
    void displayIn(Node<T>*root);
    void displayPost(Node<T>*root);

    public:

    void insert(T element) noexcept(false);   //wrapper push 
    void display();                        //wrapper display
    void erase(T element) noexcept(false);   //wrapper erase
   
   
};

//Push for Primitive data type
template <class T>
void AVL<T> :: insert(T element) noexcept(false)
{
        head=push(head,element);
}
template <class T>
void AVL<T> :: erase(T element) noexcept(false)
{
      head=deleteNode(head,element);
}
template <class T>
void AVL<T> :: display()
{
        cout<<"\nPreOrder of Tree:";
        displayPre(head);
        cout<<"\nInOrder of Tree:";
        displayIn(head);
        cout<<"\nPostOrder of Tree:";
        displayPost(head);
}
template <class T>
Node<T>* AVL<T> :: push(Node<T>* head,T element) noexcept(false)
{
    if(head==NULL)
    {
     Node<T>* noDe=new Node<T>(element);
     return noDe;
    }
    else
    {
        if(head->data > element)
        {
            head->left=push(head->left,element);
            
        }
        else if(head->data < element)
        {
            
            head->right=push(head->right,element);
        }
        else
            throw string("No Equal Elements!!!");
    }

    head->height = 1 + max(height(head->left),  
                        height(head->right)); 

    int bal=balance(head);
  if (bal > 1 && element < head->left->data) 
    {
        return rightRotation(head);
    }
   else if (bal < -1 && element > head->right->data)  
    {
        return leftRotation(head);
    }
   else if (bal > 1 && element > head->left->data)  
    {
        head->left = leftRotation(head->left);  
        return rightRotation(head);  
    }
    else if (bal < -1 && element < head->right->data)
    {
         head->right = rightRotation(head->right);  
        return leftRotation(head);  
    } 
    return head;
}
template <class T>
Node<T>* AVL<T>:: leftRotation(Node<T>* root)
{
    Node<T>* temp=root->right->left;
    root->right->left=root;
    root=root->right;
    root->left->right=temp;
    root->left->height=1+max(height(root->left->left),height(root->left->right));
    root->height=1+max(height(root->left),height(root->right));
    return root;
}
/*Delete Node*/
template <class T>
Node<T>* AVL<T> :: deleteNode(Node<T>* head,T element) noexcept(false)
{
    if(head==NULL)
    {   
        throw string("Element Not Found To delete!!");
    }
    else
    {
        if(head->data > element)
        {
            head->left=deleteNode(head->left,element);
            
        }
       else if(head->data < element)
        {
            head->right=deleteNode(head->right,element);
        }
        else if (head->data==element && head->right!=NULL)
        {
            Node<T>* temp = InOrderSucessor(head->right);
            head->data = temp->data;
            head->right=deleteNode(head->right,temp->data);
            return head;
        }
        else if (head->data==element && head->right==NULL)
        {
            free(head);
            return NULL;
        }
      

    }

    head->height = 1 + max(height(head->left),  
                        height(head->right)); 

    int bal=balance(head);
  if (bal > 1 && head->left->data > element) 
    {
        return rightRotation(head);
    }
   if (bal < -1 && element > head->right->data)  
    {
        return leftRotation(head);
    }
    if (bal > 1 && element>head->left->data)  
    {
        head->left = leftRotation(head->left);  
        return rightRotation(head);  
    }
    if (bal < -1 && head->right->data > element)
    {
         head->right = rightRotation(head->right);  
        return leftRotation(head);  
    }  
    return head;
}
/*Delete Node */
template <class T>
Node<T>* AVL<T>:: InOrderSucessor(Node<T>* head)
{
    while(head->left!=NULL)
    {
        head=head->left;
    }
    return head;
}
/*Complex Push*/
/*template <class T>
Node<T>* AVL<T>:: push(Node<T>* head,T element) throw(string)
{
    if(head==NULL)
    {
     Node<T>* noDe=new Node<T>();
     noDe->data=element;
     noDe->left=NULL;
     noDe->right=NULL;
     noDe->height=1;
     return noDe;
    }
    else
    {
        if(compare(head->data , element))
        {
            head->left=push(head->left,element);
            
        }
        else if (compare(element,head->data))
        {
            
            head->right=push(head->right,element);
        }
        else
            throw string("N0 Similar keys allowed in AVL tree");
    }

    head->height = 1 + max(height(head->left),  
                        height(head->right)); 

    int balance=balance(head);
  if (balance > 1 && compare(head->data , element)) 
    {
        return rightRotation(head);
    }
   if (balance < -1 && compare(element,head->data))  
    {
        return leftRotation(head);
    }
    if (balance > 1 && compare(element,head->data))  
    {
        head->left = leftRotation(head->left);  
        return rightRotation(head);  
    }
    if (balance < -1 &&compare(head->data , element))
    {
         head->right = rightRotation(head->right);  
        return leftRotation(head);  
    }  
    return head;
}*/
/*Delete Node */

/*Complex End*/


template <class T>
int AVL<T>:: max(int x, int y)
{
    return ((x >= y) ? x : y);
}
template <class T>
Node<T>* AVL<T> :: rightRotation(Node<T>* root)
{
    Node<T>* temp=root->left->right;
    root->left->right=root;
    root=root->left;
    root->right->left=temp;
    root->right->height=1+max(height(root->right->left),height(root->right->right));
    root->height=1+max(height(root->left),height(root->right));
    
    return root;
}
template <class T>
void AVL<T> :: displayPre(Node<T>* root)
{
    if(root==NULL)
        return;
    cout<<root->data;
    cout<<",";
    displayPre(root->left);
    displayPre(root->right);

}
template <class T>
void AVL<T> :: displayPost(Node<T>* root)
{
    if(root==NULL)
        return;
    
    displayPost(root->left);
    displayPost(root->right);
    cout<<root->data;
    cout<<",";
}
template <class T>
void AVL<T> :: displayIn(Node<T>* root)
{
    if(root==NULL)
        return;
    
    displayIn(root->left);
    cout<<root->data;
    cout<<",";
    displayIn(root->right);
}
template <class T>
int AVL<T> :: height(Node<T>* root)
{
    if(root==NULL)
        return 0;
    else    
        return root->height;
}
template <class T>
int AVL<T> :: balance(Node<T>* root)
{
    return (height(root->left)-height(root->right));
}

