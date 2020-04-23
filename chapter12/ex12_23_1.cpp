//
// Created by wangheng on 2020/4/23.
//

#include <iostream>
#include <cstring>

int main() {
    const char *c1 = "hello";
    const char *c2 = "world";
    auto len = std::strlen(c1) + std::strlen(c2) + 1;
    auto p = new char[len]();
    std::strncat(p, c1, std::strlen(c1));
    std::strncat(p, c2, std::strlen(c2));
    std::cout << p << std::endl;

    return 0;
}