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
    String str2(str);
    std::cout << str2.c_str() << std::endl;
    String str3;
    str3 = str2;
    std::cout << str2 << std::endl;
    str3 = "apple";
    std::cout << std::boolalpha << (str == str2) << ' ' << (str2 == str3) << std::endl;
    std::cout << (str < str3) << std::endl;
    std::cout << str3[3] << std::endl;

    return 0;
}