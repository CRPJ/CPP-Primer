//
// Created by wangheng on 2020/5/4.
//

#include <iostream>
#include "ex13_26.h"

int main() {
    StrBlob sb;
    std::string s("china");
    sb.push_back(s);    // 调用push_back(const std::string&)
    sb.push_back(std::move(s));     // 调用push_back(std::string&&)
    std::cout << sb.front() << '\t' << sb.back() << std::endl;

    return 0;
}