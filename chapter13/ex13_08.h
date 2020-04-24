//
// Created by wangheng on 2020/4/24.
//

#ifndef CPP_PRIMER_EX13_08_H
#define CPP_PRIMER_EX13_08_H

#include <string>

class HasPtr {
public:
    HasPtr(const std::string& s = std::string()) : ps(new std::string(s)), i(0) {}
    HasPtr(const HasPtr& hp) : ps(new std::string(*hp.ps)), i(hp.i) {}
    HasPtr& operator=(const HasPtr&);

private:
    std::string *ps;
    int i;
};

HasPtr& HasPtr::operator=(const HasPtr &hp) {
    ps = new std::string(*hp.ps);
    i = hp.i;
    return *this;
}

#endif //CPP_PRIMER_EX13_08_H
