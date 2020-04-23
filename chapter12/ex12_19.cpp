//
// Created by wangheng on 2020/4/23.
//

#include <iostream>
#include "ex12_19.h"

int main() {
    StrBlob blob = {"an", "the"};
    StrBlobPtr blobptr(blob);
    std::cout << blobptr.dref() << std::endl;
    return 0;
}