//
// Created by wangheng on 2020/4/25.
//

#include <iostream>
#include "ex13_39.h"

int main() {
    StrVec sv({"hello", "world", "good", "china", "amazing"});
    for (auto iter = sv.begin(); iter != sv.end(); ++iter)
        std::cout << *iter << std::endl;
    std::cout << std::endl;
    sv.resize(6);
    for (auto iter = sv.begin(); iter != sv.end(); ++iter)
        std::cout << *iter << std::endl;
    std::cout << sv.capacity() << std::endl;
    return 0;
}
