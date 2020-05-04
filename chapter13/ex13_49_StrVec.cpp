//
// Created by wangheng on 2020/4/26.
//

#include <iostream>
#include <vector>
#include "ex13_43.h"

int main() {
    std::vector<StrVec> v{StrVec({"hello", "world"})};
    v.push_back(StrVec({"good"}));

    return 0;
}