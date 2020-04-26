//
// Created by wangheng on 2020/4/26.
//

#include <iostream>
#include "ex13_44.h"

int main() {
    String str("hello");
    for (auto iter = str.begin(); iter != str.end(); ++iter)
        std::cout << *iter << '\t';
    std::cout << std::endl;
    std::cout << str.c_str() << std::endl;
    std::cout << str.front() << '\t' << str.back() << '\t' << str[1] << std::endl;
    String str2(str);
    std::cout << str2.c_str() << std::endl;
    String str3;
    str3 = str2;
    return 0;
}