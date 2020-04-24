//
// Created by wangheng on 2020/4/24.
//

#include <iostream>
#include "../chapter12/ex12_19.h"

int main() {
    StrBlob sb1;
    std::cout << "reference count of sb1 is " << sb1.count() << std::endl;
    StrBlob sb2 = sb1;
    std::cout << "reference count of sb1 is " << sb1.count() << std::endl;

    StrBlobPtr sbp1(sb1);
    std::cout << "reference count of sb1 is " << sb1.count() << std::endl;
    StrBlobPtr sbp2(sbp1);
    std::cout << "reference count of sb1 is " << sb1.count() << std::endl;

    return 0;
}