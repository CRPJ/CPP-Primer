//
// Created by wangheng on 2020/4/27.
//

#include <iostream>
#include "ex13_53.h"

int main() {
    HasPtr hp(std::string("hello"));
    HasPtr hp2 = hp;
    HasPtr hp3 = std::move(hp);
    HasPtr hp4;
    hp4 = hp3;
    hp4 = std::move(hp);

    return 0;
}