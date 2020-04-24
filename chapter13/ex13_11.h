//
// Created by wangheng on 2020/4/24.
//

#ifndef CPP_PRIMER_EX13_11_H
#define CPP_PRIMER_EX13_11_H

#include <iostream>

class HasPtr {
public:
    HasPtr(const std::string& s = std::string()) : ps(new std::string(s)), i(0) {}
    HasPtr(const HasPtr& hp) : ps(new std::string(*hp.ps)), i(hp.i) {}
    HasPtr& operator=(const HasPtr&);
    ~HasPtr();

private:
    std::string *ps;
    int i;
};

HasPtr& HasPtr::operator=(const HasPtr &hp) {
    ps = new std::string(*hp.ps);
    i = hp.i;
    return *this;
}

HasPtr::~HasPtr() {
    delete ps;
    std::cout << "~HasPtr()" << std::endl;
}
#endif //CPP_PRIMER_EX13_11_H
