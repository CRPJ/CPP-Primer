//
// Created by wangheng on 2020/4/23.
//

#ifndef CPP_PRIMER_EX13_22_H
#define CPP_PRIMER_EX13_22_H

#include <string>
class HasPtr
{
public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) {}
    HasPtr(const HasPtr& hp) : ps(new std::string(*hp.ps)), i(hp.i) {}
    HasPtr& operator=(const HasPtr& hp) {
        auto newp = new std::string(*hp.ps);
        delete ps;  // ps在指向新的地址前要先销毁原来指向的内存，否则原来指向的内存将无法找到，内存泄漏
        ps = newp;
        i = hp.i;
        return *this;
    }
    ~HasPtr() {
        delete ps;
    }
private:
    std::string *ps;
    int i;
};

#endif //CPP_PRIMER_EX13_22_H
