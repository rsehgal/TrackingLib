/*
**	Filename : SingleTon_T.h
**	2022-03-22
**	username : rsehgal
*/
#ifndef SingleTon_T_h
#define SingleTon_T_h

template <class T> 
class SingleTon_T {
  T *fObj;
  static SingleTon_T *s_instance;

public:
  SingleTon_T();
  ~SingleTon_T();
  static SingleTon_T *instance();
  T* GetTargetObject();
};

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

#endif
