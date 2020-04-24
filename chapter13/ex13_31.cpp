//
// Created by wangheng on 2020/4/24.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class HasPtr
{
public:
    friend void swap(HasPtr&, HasPtr&);
    friend bool operator<(const HasPtr& lhs, const HasPtr& rhs);
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) {}
    HasPtr(const HasPtr& hp) : ps(new std::string(*hp.ps)), i(hp.i) {}
    HasPtr& operator=(HasPtr rhs) {
        swap(*this, rhs);
        return *this;
    }
    void show() const {
        std::cout << *ps << std::endl;
    }
    ~HasPtr() {
        delete ps;
    }
private:
    std::string *ps;
    int i;
};

void swap(HasPtr& lhs, HasPtr& rhs) {
    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, lhs.i);
    std::cout << "execute swap()" << std::endl;
}

bool operator<(const HasPtr& lhs, const HasPtr& rhs) {
    return *lhs.ps < *rhs.ps;
}

int main() {
    std::vector<HasPtr> vHp{HasPtr("zoom"), HasPtr("hello"), HasPtr("good")};
    std::sort(vHp.begin(), vHp.end());
    for (auto& iter : vHp) {
        iter.show();
    }

    return 0;
}