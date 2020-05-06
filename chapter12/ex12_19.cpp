//
// Created by wangheng on 2020/4/23.
//

#include <iostream>
#include "ex12_19.h"

int main() {
    StrBlob blob = {"an", "the", "good", "high", "low"};
    StrBlobPtr blobptr(blob);
    std::cout << blobptr.dref() << std::endl;
    StrBlob blob1 = {"an", "zoom"};
    std::cout << std::boolalpha << (blob == blob1) << std::endl;
    std::cout << (blob < blob1) << std::endl;
    std::cout << blob[1] << std::endl;
    std::cout << blobptr[1] << std::endl;
    std::cout << blobptr.dref() << std::endl;
    std::cout << (++blobptr).dref() << std::endl;
    std::cout << blobptr--.dref() << std::endl;
    std::cout << blobptr.dref() << std::endl;
    std::cout << (blobptr + 4).dref() << std::endl;
    std::cout << (blobptr - 2).dref() << std::endl;

    return 0;
}