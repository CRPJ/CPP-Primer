//
// Created by wangheng on 2020/4/24.
//

#include <iostream>
#include <string>
#include <cstring>

int main() {
    std::string s1("hello");
    std::string s2("world");
    char *p = new char[s1.size()+s2.size()]();
    std::strcat(p, (s1+s2).c_str());
    std::cout << p << std::endl;

    return 0;
}