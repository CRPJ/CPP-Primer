//
// Created by wangheng on 2020/4/24.
//

#include <iostream>
#include "ex13_26.h"

int main() {
    StrBlob sb1;
    StrBlob sb2(sb1);
    StrBlob sb3;
    sb3 = sb1;

    return 0;
}