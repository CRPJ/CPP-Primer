//
// Created by wangheng on 2020/4/24.
//

#include <iostream>
#include <string>

class HasPtr
{
public:
    friend void swap(HasPtr&, HasPtr&);
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) {}
    HasPtr(const HasPtr& hp) : ps(new std::string(*hp.ps)), i(hp.i) {}
    HasPtr& operator=(HasPtr rhs) {
        swap(*this, rhs);
        return *this;
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

int main() {
    HasPtr hp1;
    HasPtr hp2(hp1);
    HasPtr hp3;
    hp3 = hp1;  // 拷贝赋值运算符调用swap()函数
    swap(hp1, hp3); // 调用swap()函数

    return 0;
}