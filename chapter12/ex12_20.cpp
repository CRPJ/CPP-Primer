//
// Created by wangheng on 2020/4/23.
//

#include "ex12_19.h"
#include <iostream>

int main() {
    StrBlob blob;
    std::string str;
    while (std::cin >> str) {
        if (str == "q")
            break;
        blob.push_back(str);
    }
    for (StrBlobPtr sp = blob.begin(); sp != blob.end(); sp.incr()) {
        std::cout << sp.dref() << std::endl;
    }

    return 0;
}