//
// Created by wangheng on 2020/4/23.
//

#include <iostream>
#include "ex12_22.h"

int main() {
    const StrBlob blob = {"the", "hello"};
    ConstStrBlobPtr blobptr(blob);
    for (auto iter = blob.cbegin(); iter != blob.cend(); iter.incr())
        std::cout << iter.dref() << std::endl;

    return 0;
}