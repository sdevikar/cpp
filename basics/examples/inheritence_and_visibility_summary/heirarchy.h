//******************************************************************************
// In this class we will show the INACCESSIBLE members only
//******************************************************************************


#include <iostream>
using namespace std;


class A{
private:
  int x;

protected:
  int y;

public:
  int z;

};

class B : public A{
private:
  int u;
protected:
  int v;
public:
  int w;
  void f(){x;} //trying to access x here will result in error, since x is private in base class A. It doesn't matter if the inheritence is public/protected/private
};

class C : protected A{
private:
  int u;
protected:
  int v;
public:
  int w;
  void f(){x;} //trying to access x here will result in error, since x is private in base class A. It doesn't matter if the inheritence is public/protected/private
};


class D : private A{
private:
  int u;
protected:
  int v;
public:
  int w;
  void f(){x;} //trying to access x here will result in error, since x is private in base class A. It doesn't matter if the inheritence is public/protected/private
};

class E : public B{
public:
  void f(){
    x; // can't access x because x was inaccessible in B, since it was a private member of A
    u; // can't access u because u was private in base class B
  }
};

class F : public C{
public:
  void f(){
    x; // can't access x because x was inaccessible in C, since it was a private member of A
    u; // can't access u because u was private in base class C
  }
};

class G : public D{
public:
  void f(){
    x; // can't access x because x was inaccessible in C, since it was a private member of A
    y; //can't access y because, y should come from base class D. And in base class D, y BECAME private because class D inherited class A "privately"
    z; //can't access z because, z should come from base class D. And in base class D, y BECAME private because class D inherited class A "privately"
    u; // can't access u because u was private in base class C
  }
};
