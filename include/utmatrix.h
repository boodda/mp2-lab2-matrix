// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;
const int INDENT = 6;
// Шаблон вектора
template <class ValType>
class TVector
{
protected:
  ValType *pVector;
  int Size;       // размер вектора
  int StartIndex; // индекс первого элемента вектора
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector &v);                // конструктор копирования
  ~TVector();
  int GetSize()      { return Size;       } // размер вектора
  int GetStartIndex(){ return StartIndex; } // индекс первого элемента
  ValType& operator[](int pos);             // доступ
  bool operator==(const TVector &v) const;  // сравнение
  bool operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector &v);     // присваивание

  // скалярные операции
  TVector  operator+(const ValType &val);   // прибавить скаляр
  TVector  operator-(const ValType &val);   // вычесть скаляр
  TVector  operator*(const ValType &val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector &v);     // сложение
  TVector  operator-(const TVector &v);     // вычитание
  ValType  operator*(const TVector &v);     // скалярное произведение

  // ввод-вывод
  friend istream& operator>>(istream &in, TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      in >> v.pVector[i];
    return in;
  }
  friend ostream& operator<<(ostream &out, const TVector &v)
  {
    cout.width(v.StartIndex*(INDENT+1));
    cout<<"";
    for (int i = 0; i < v.Size; i++){
      cout.width(INDENT);
      out << v.pVector[i] << ' ';
    }
    return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
  pVector = new ValType[s];
  if(pVector==nullptr){
    throw "Недостаточно памяти";
  }
  Size = s;
  StartIndex = si;
}  

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
  pVector = new ValType[v.Size];
  if(pVector==nullptr){
    throw "Недостаточно памяти";
  }
  for(int i=0;i<v.Size;i++){
    pVector[i] = v.pVector[i];
  }
  Size = v.Size;
  StartIndex = v.StartIndex;
}  

template <class ValType>
TVector<ValType>::~TVector()
{
  delete[] pVector;
}  

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
  int respos = pos - StartIndex;
  if (respos<0 || respos>=Size){
    throw "Некорректный индекс";
  }
  return pVector[respos];
}  

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
  if(Size!=v.Size) return false;
  if(StartIndex!=v.StartIndex) return false;
  for(int i=0;i<Size;i++){
    if(pVector[i]!=v.pVector[i]) return false;
  }
  return true;
}  

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
  return !((*this)==v);
}  

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
  if(this==&v) return *this;
  delete[] pVector;
  pVector = new ValType[v.Size];
  if(pVector==nullptr){
    throw "Недостаточно памяти";
  }
  for(int i=0;i<v.Size;i++){
    pVector[i] = v.pVector[i];
  }
  Size = v.Size;
  StartIndex = v.StartIndex;

}  

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
  TVector<ValType> res(*this);
  for(int i=0;i<Size;i++){
    res[i]+=val;
  }
  return res;
}  

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
  TVector<ValType> res(*this);
  for(int i=0;i<Size;i++){
    res[i]-=val;
  }
  return res;
}  

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
  TVector<ValType> res(*this);
  for(int i=0;i<Size;i++){
    res[i]*=val;
  }
  return res;
}  

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
  if (Size!=v.Size || StartIndex!=v.StartIndex) throw "Размеры должны быть одинаковыми";
  TVector<ValType> res(*this);
  for(int i=0;i<Size;i++){
    res.pVector[i]+=v.pVector[i];
  }
  return res;
}  

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
  if (Size!=v.Size || StartIndex!=v.StartIndex) throw "Размеры должны быть одинаковыми";
  TVector<ValType> res(*this);
  for(int i=0;i<Size;i++){
    res.pVector[i]-=v.pVector[i];
  }
  return res;
}  

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
  if (Size!=v.Size || StartIndex!=v.StartIndex) throw "Размеры должны быть одинаковыми";
  ValType res=0;
  for(int i=0;i<Size;i++){
    res+=v.pVector[i]*pVector[i];
  }
  return res;

}  


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
  bool operator==(const TMatrix &mt) const;      // сравнение
  bool operator!=(const TMatrix &mt) const;      // сравнение
  TMatrix& operator= (const TMatrix &mt);        // присваивание
  TMatrix  operator+ (const TMatrix &mt);        // сложение
  TMatrix  operator- (const TMatrix &mt);        // вычитание

  // ввод / вывод
  friend istream& operator>>(istream &in, TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }
  friend ostream & operator<<( ostream &out, const TMatrix &mt)
  {
    for(int i=0;i<mt.Size*(INDENT+1);i++)
    {
        out<<"-";
    }
    out<<endl;
    for (int i = 0; i < mt.Size; i++){

      out <<"|"<< mt.pVector[i]<<"|" << endl;
    }
    for(int i=0;i<mt.Size*(INDENT+1);i++)
    {
        out<<"-";
    }
    out<<endl;
    return out;
  }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s): TVector<TVector<ValType> >(s)
{
  for(int i=0;i<s;i++){
    TVector<TVector<ValType>>::pVector[i] = TVector<ValType>(s-i,i);
  }
}  

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):  TVector<TVector<ValType> >(mt) {}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):  TVector<TVector<ValType> >(mt) {}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
  if(TVector<TVector<ValType>>::Size!=mt.Size) return false;
  if(TVector<TVector<ValType>>::StartIndex!=mt.StartIndex) return false;
  for(int i=0;i<(TVector<TVector<ValType>>::Size); i++){
    if((TVector<TVector<ValType>>::pVector[i])!=mt.pVector[i]) return false;
  }
  return true;

} 
template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
  return !((*this)==mt);
} 

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
  if(this==&mt) return *this;
  delete[] (TVector<TVector<ValType>>::pVector);
  TVector<TVector<ValType>>::pVector = new TVector<ValType>[mt.Size];
  if((TVector<TVector<ValType>>::pVector)==nullptr){
    throw "Недостаточно памяти";
  }
  for(int i=0;i<mt.Size;i++){
   TVector<TVector<ValType>>:: pVector[i] = mt.pVector[i];
  }
  TVector<TVector<ValType>>::Size = mt.Size;
  TVector<TVector<ValType>>::StartIndex = mt.StartIndex;
}  

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
  if ((TVector<TVector<ValType>>::Size)!=mt.Size || (TVector<TVector<ValType>>::StartIndex)!=mt.StartIndex) throw "Размеры должны быть одинаковыми";
  TMatrix<ValType> res(*this);
  for(int i=0;i<(TVector<TVector<ValType>>::Size);i++){
    res.pVector[i]= res.pVector[i]+mt.pVector[i];
  }
  return res;
}  

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
  if ((TVector<TVector<ValType>>::Size)!=mt.Size || (TVector<TVector<ValType>>::StartIndex)!=mt.StartIndex) throw "Размеры должны быть одинаковыми";
  TMatrix<ValType> res(*this);
  for(int i=0;i<(TVector<TVector<ValType>>::Size);i++){
    res.pVector[i]= res.pVector[i]-mt.pVector[i];
  }
  return res;
}  


#endif
