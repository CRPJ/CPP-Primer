//
// Created by wangheng on 2020/4/25.
//

#include <iostream>
#include "ex13_43.h"

int main() {
    StrVec sv({"hello", "zoom", "good", "china", "amazing"});
    for (auto iter = sv.begin(); iter != sv.end(); ++iter)
        std::cout << *iter << std::endl;
    std::cout << std::endl;
    sv.resize(6);
    for (auto iter = sv.begin(); iter != sv.end(); ++iter)
        std::cout << *iter << std::endl;
    std::cout << sv.capacity() << std::endl;
    StrVec sv1({"hello", "world", "good", "china", "big"});
    sv1.resize(6);
    std::cout << std::boolalpha << (sv == sv1) << std::endl;
    std::cout << (sv < sv1) << std::endl;

    return 0;
}