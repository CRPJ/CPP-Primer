//
// Created by wangheng on 2020/4/26.
//

#include <iostream>
#include "ex13_43.h"

int main() {
    StrVec sv{"hello", "world"};
    sv.push_back("china");
    sv.push_back("amazing");
    sv.push_back("large");

    for (auto iter = sv.begin(); iter != sv.end(); ++iter)
        std::cout << *iter << std::endl;
    return 0;
}