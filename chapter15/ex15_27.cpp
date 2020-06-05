//
// Created by wangheng on 2020/6/5.
//

#include "ex15_27.h"
#include <iostream>

int main() {
    Bulk_quote bulk("123", 23.1, 20, 0.12);
    Bulk_quote bulk2(std::move(bulk));
    std::cout << bulk2.net_price(34) << std::endl;

    return 0;
}