//
// Created by wangheng on 2020/5/10.
//

#include <iostream>
#include <string>

class Base {
public:
    void pub_mem(); // public成员
protected:
    int prot_mem;   // protected成员
private:
    char priv_mem;  // private成员
};

struct Pub_Derv : public Base {
    void memfcn(Base& b) { b = *this; }
};

struct Prot_Derv : protected Base {
    void memfcn(Base& b) { b = *this; }
};

struct Priv_Derv : private Base {
    void memfcn(Base& b) { b = *this; }
};

struct Derived_from_Public : public Pub_Derv {
    void memfcn(Base& b) { b = *this; }
};

struct Derived_from_Protected: public Prot_Derv {
    void memfcn(Base& b) { b = *this; }
};

struct Derived_from_Private : public Priv_Derv {
    // Cannot cast 'const Derived_from_Private' to its private base class 'const Base'
    // 不能将派生类向其私有继承的基类转换
    // void memfcn(Base& b) { b = *this; }
};

int main()
{
    Pub_Derv d1;
    Base *p = &d1;

    Priv_Derv d2;
    //p = &d2;

    Prot_Derv d3;
    //p = &d3;

    Derived_from_Public dd1;
    p = &dd1;

    Derived_from_Private dd2;
    //p =& dd2;

    Derived_from_Protected dd3;
    //p = &dd3;


    return 0;
}