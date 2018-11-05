// ÍÍÃÓ, ÂÌÊ, Êóðñ "Ìåòîäû ïðîãðàììèðîâàíèÿ-2", Ñ++, ÎÎÏ
//
// sample_matrix.cpp - Copyright (c) Ãåðãåëü Â.Ï. 07.05.2001
//   Ïåðåðàáîòàíî äëÿ Microsoft Visual Studio 2008 Ñûñîåâûì À.Â. (20.04.2015)
//
// Òåñòèðîâàíèå âåðõíåòðåóãîëüíîé ìàòðèöû

#include <iostream>
#include "utmatrix.h"
//---------------------------------------------------------------------------
int main()
{
  TMatrix<int> a(5), b(5), c(5);
  int i, j;

  setlocale(LC_ALL, "Russian");
  for (i = 0; i < 5; i++)
    for (j = i; j < 5; j++ )
    {
      a[i][j] =  i * 10 + j;
      b[i][j] = i+j*10;
    }
  a = a+b;
  cout << "Matrix a = " << endl << a << endl;
  cout << "Matrix b = " << endl << b << endl;
  try{
  c = a*b;
  }
  catch(const char * e){
    cout<<"~~~"<<e<<endl;
  }
  cout<<c<<endl;

  return 0;
}
//---------------------------------------------------------------------------
