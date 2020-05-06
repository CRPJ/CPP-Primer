//
// Created by wangheng on 2020/4/23.
//

#include <iostream>
#include "ex12_19.h"

int main() {
    StrBlob blob = {"an", "the"};
    StrBlobPtr blobptr(blob);
    std::cout << blobptr.dref() << std::endl;
    StrBlob blob1 = {"an", "zoom"};
    std::cout << std::boolalpha << (blob == blob1) << std::endl;
    std::cout << (blob < blob1) << std::endl;
    std::cout << blob[1] << std::endl;

    return 0;
}