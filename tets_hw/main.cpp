#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <cstring>
 
#include <fstream>
 
using namespace std;
 
const int _maxLengthName = 21;
 
//Структура для автобуса
struct Bus
{
    int bus;
    char *name;
    char i;
    char o;
  int route;
};
 
//Один узел очереди
struct Node
{
    Bus *data;
 
    Node *next;
    Node *prev;
};
 
//Выделение памяти под данные
Bus * InitData()
{
    Bus *tk = new Bus;
    tk->name = new char [_maxLengthName];
    return tk;
}
 
//Ввод данных
Bus * EnterData()
{
    Bus *bt = InitData();
    cout<<"Bus = ";     cin>>bt->bus;
    cout<<"Driver (Fname I.O.) = ";     cin>>bt->name>>bt->i>>bt->o;
    cout<<"Route = ";       cin>>bt->route;
    return bt;
}
 
//Создание первого узла списка
Node * First(Bus * tk)
{
    Node * pv= new Node;
    pv->data = tk;
    pv->next = 0;
    pv->prev = 0;
    return pv;
}
 
//Добавление ула в конец списка
void Add(Node ** pend, Bus *tk)
{
    Node *pv = new Node;
    pv->data = tk;
    pv->next = 0;
    pv->prev = *pend;
    (*pend)->next = pv;
    *pend = pv;
}
 
//Поиск элемента в списке
Node *Find(Node * const pbeg, int bus)
{
    Node *pv = pbeg;
    while (pv)
    {
        if (pv->data->bus == bus) break;
        pv = pv->next;
    }
    return pv;
}
 
//Удаление элемента из списка по коду
bool Remove(Node **pbeg, Node **pend, int bus)
{
    if (Node *pkey = Find(*pbeg, bus))
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
 
//Вставка элемента по ключу (Очередь будет упорядоченныя по коду)
Node * insert (Node ** pbeg, Node **pend, Bus *bk)
{
    Node *pkey = *pbeg;
    if (pkey->data->bus < bk->bus)
    {
        while (pkey->next && pkey->data->bus < bk->bus)
            pkey = pkey->next;
        Node *pv = new Node;
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
        Node *pv = new Node;
        pv->data = bk;
        pv->next = *pbeg;
        pv->prev = 0;
        
        pkey->prev = pv;
        *pbeg = pv;
        return pv;
    }
    return 0;
}
 
//Печать списка
void Print(Node * const pbeg)
{
    Node *pv = pbeg;
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
 
//Поиск записи
Bus* Search(Node * const pbeg)
{
    Node *pv = pbeg;
 
    int bus;
    char date[13];
    cout<<" bus             = "; cin>>bus;
    while (pv)
    {
        if (pv->data->bus == bus)
        {
            Node *pbeg = First(pv->data);
            Print(pbeg);
      return pbeg->data;
        }
        pv = pv->next;
    }
}
 
//Обобщил добавление элемента. Если очередт нет - он создаст
void NodeRead(Node ** pbeg, Node **pend, Bus *bk)
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
 
void FileRead(Node **pbeg, Node **pend)
{
  char * fname = new char [32];//Это что за конструкция была?
  strcpy(fname,"test.txt");
  ifstream fin(fname);
 
  while(!fin.eof())
  {
    
    Bus *bt = InitData();
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
 
 
//Меню
int main()
{
    Node *pbeg=0, *pend=0;
  Node *rbeg=0, *rend=0;
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
      NodeRead(&pbeg,&pend, EnterData());
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
            Node *pv = Find(pbeg,bus);
            if (pv)
            {
                Node *next = pv->next;
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
 
    //Освобождение памяти
    while (pbeg)
    {
        Node *pv = pbeg;
        pbeg = pbeg->next;
        delete pv->data;
        delete pv;
    }
    return 0;
}