//
// Created by wangheng on 2020/6/10.
//

#include "Vec.h"
#include <iostream>
#include <string>

int main() {
    Vec<std::string> strVec({"hello", "good", "big"});
    std::cout << "size: " << strVec.size() << " capacity:" << strVec.capacity() << std::endl;
    std::cout << *strVec.begin() << std::endl;
    strVec.reserve(10);
    std::cout << "size: " << strVec.size() << " capacity:" << strVec.capacity() << std::endl;
    Vec<int> intVec({1,3,5});
    Vec<int> intVec2(std::move(intVec));
    std::cout << *intVec2.begin() << std::endl;
    std::cout << intVec2.back() << std::endl;
    intVec2.push_back(10);
    std::cout << intVec2.back() << std::endl;

    return 0;
}