#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <cstring>
 
#include <fstream>
 
using namespace std;
 
const int _maxLengthName = 21;
 
//&#323;&#328;&#273;у&#281;&#328;у&#273;&#341; дл&#729; &#341;в&#328;обу&#324;&#341;
 
struct Tram {
 int bus;
    char *name;
    char i;
    char o;
  int route;
 
 
};
 
struct Trolley {
     int bus;
    char *name;
    char i;
    char o;
  int route;
 
};
 
struct Bus
{
    int bus;
    char *name;
    char i;
    char o;
  int route;
};
 
template <class T>
struct Node
{
    T *data;
    Node *next;
    Node *prev;
};
 
template <class T>
T * InitData()
{
    T *tk = new T;
    tk->name = new char [_maxLengthName];
    return tk;
}
 
template <class T>
T * EnterData()
{
    T *bt = InitData<T>();
    cout<<"Bus = ";     cin>>bt->bus;
    cout<<"Driver (Fname I.O.) = ";     cin>>bt->name>>bt->i>>bt->o;
    cout<<"Route = ";       cin>>bt->route;
    return bt;
}
 
template <class T>
Node <T> * First(T * tk)
{
    Node <T> * pv= new Node <T>;
    pv->data = tk;
    pv->next = 0;
    pv->prev = 0;
    return pv;
}
 
template <class T>
void Add(Node  <T>** pend, T *tk)
{
    Node  <T> *pv = new Node  <T>;
    pv->data = tk;
    pv->next = 0;
    pv->prev = *pend;
    (*pend)->next = pv;
    *pend = pv;
}
 
template <class T>
Node  <T> *Find(Node  <T> * const pbeg, int bus)
{
    Node<T> *pv = pbeg;
    while (pv)
    {
        if (pv->data->bus == bus) break;
        pv = pv->next;
    }
    return pv;
}
 
template <class T>
bool Remove(Node  <T> **pbeg, Node  <T> **pend, int bus)
{
    if (Node  <T> *pkey = Find(*pbeg, bus))
    {
        if (pkey == *pbeg)
        {
            if ((*pbeg)->next)
            {
            *pbeg = (*pbeg)->next;
            (*pbeg)->prev = 0;
            }
            else
            {
                *pbeg = 0;
                *pend = 0;
            }
        }else if (pkey == *pend)
        {
            *pend = (*pend)->prev;
            (*pend)->next = 0;
        }else
        {
            (pkey->prev)->next = pkey->next;
            (pkey->next)->prev = pkey->prev;
        }
        delete pkey;
        return true;
    }
    return false;
}
 
 
template <class T>
Node  <T> * insert (Node  <T> ** pbeg, Node<T>**pend, T *bk)
{
    Node  <T> *pkey = *pbeg;
    if (pkey->data->bus < bk->bus)
    {
        while (pkey->next && pkey->data->bus < bk->bus)
            pkey = pkey->next;
        Node<T> *pv = new Node<T>;
        pv->data = bk;
        pv->next = pkey->next;
        pv->prev = pkey;
        pkey->next = pv;
        if (pkey != *pend)
            (pv->next)->prev = pv;
        else
            *pend = pv;
        return pv;
    }else
    {
        Node  <T> *pv = new Node  <T>;
        pv->data = bk;
        pv->next = *pbeg;
        pv->prev = 0;
 
        pkey->prev = pv;
        *pbeg = pv;
        return pv;
    }
    return 0;
}
 
template <class T>
void Print(Node  <T> * const pbeg)
{
    Node  <T> *pv = pbeg;
    if (!pv)
    {
        cout<<" List is empty "<<endl;
        return;
    }
  cout<<("---------------------------------------------\n");
    cout<<("|  bus | Fio           | Route              |\n");
    cout<<("---------------------------------------------\n");
    while (pv)
    {
        Bus *bk = pv->data;
        printf("|%6d",bk->bus);
        printf("|%9s",bk->name);
        printf(" %c.",bk->i);
        printf(" %c.",bk->o);
        printf("|%19d",bk->route);
        printf("|\n");
        pv = pv->next;
 
    }
    printf("----------------------------------------------\n");
 
}
template <class T>
T* Search(Node  <T> * const pbeg)
{
    Node  <T> *pv = pbeg;
 
    int bus;
    char date[13];
    cout<<" bus             = "; cin>>bus;
    while (pv)
    {
        if (pv->data->bus == bus)
        {
            Node<T> *pbeg = First(pv->data);
            Print(pbeg);
      return pbeg->data;
        }
        pv = pv->next;
    }
}
 
template <class T>
void NodeRead(Node  <T> ** pbeg, Node  <T> **pend, T *bk)
{
//  Bus *bk = EnterData();
    if (*pbeg)
        insert(pbeg,pend,bk);
    else
    {
        (*pbeg) = First(bk);
        (*pend) = (*pbeg);
    }
}
 
template <class T>
void FileRead( Node  <T> **pbeg, Node  <T> **pend)
{
  char * fname = new char [32];
  strcpy(fname,"test.txt");
  ifstream fin(fname);
 
  while(!fin.eof())
  {
 
    Bus *bt = InitData<Bus>();
    fin>>bt->bus;
      fin>>bt->name>>bt->i>>bt->o;
      fin>>bt->route;
 
    if (*pbeg)
          insert(pbeg,pend,bt);
      else
      {
        (*pbeg) = First(bt);
        (*pend) = (*pbeg);
      }
  }
 
  fin.close();
}
 
int main()
{
  Node<Bus> *pbeg=0, *pend=0;
  Node<Bus> *rbeg=0, *rend=0;
    int menu,bus;
    do
    {
        system("cls");
        cout<<" 1 - Add bus"<<endl;
        cout<<" 2 - Print All"<<endl;
        cout<<" 3 - Search "<<endl;
        cout<<" 4 - Delete "<<endl;
        cout<<" 5 - SearchDate"<<endl;
        cout<<" 6 - Read file"<<endl;
        cout<<" 7 - Set bus on route"<<endl;
        cout<<" 0 - Exit "<<endl;
        cout<<"Select menu ";
        cin>>menu;
        switch (menu)
        {
        case 1:
      NodeRead(&pbeg,&pend, EnterData<Bus>());
            break;
        case 2:
      cout<<"Bus in park"<<endl;
            Print(pbeg);
      cout<<"Bus in route"<<endl;
      Print(rbeg);
            _getch();
            break;
        case 3:{
            cout<<" bus = ";
            cin>>bus;
            Node<Bus> *pv = Find(pbeg,bus);
            if (pv)
            {
                Node<Bus> *next = pv->next;
                pv->next = 0;
                Print(pv);
                pv->next = next;
            }else cout<<" Bus not found"<<endl;
            _getch();
            break;}
        case 4:
            cout<<" Bus = ";
            cin>>bus;
            Remove(&pbeg,&pend,bus);
            _getch();
            break;
        case 5:
            Search(pbeg);
           _getch();
            break;
    case 6:
      FileRead(&pbeg, &pend);
      break;
    case 7:
      {
      Bus * b = Search(pbeg);
      Remove(&pbeg,&pend,b->bus);
      NodeRead(&rbeg, &rend, b);
      break;
      }
        }
    }while (menu);
 
    while (pbeg)
    {
        Node <Bus> *pv = pbeg;
        pbeg = pbeg->next;
        delete pv->data;
        delete pv;
    }
    return 0;
}