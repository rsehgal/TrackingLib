/*
**	Filename : SingleTon_T.cpp
**	2022-03-22
**	username : rsehgal
*/
#include "SingleTon_T.h"

template<class T> 
SingleTon_T<T> *SingleTon_T<T>::s_instance=0;

template <class T> 
SingleTon_T<T>::SingleTon_T() { fObj = new T; }

template <class T>
SingleTon_T<T>::~SingleTon_T(){

}

template <class T> 
SingleTon_T<T>* SingleTon_T<T>::instance() {
  if (!s_instance) {
    s_instance = new SingleTon_T<T>();
  }
  return s_instance;
}

template<class T>
T* SingleTon_T<T>::GetTargetObject(){
  return fObj;
}

