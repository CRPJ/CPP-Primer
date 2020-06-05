//
// Created by wangheng on 2020/6/6.
//

#include <iostream>
#include <vector>
#include <memory>
#include "ex15_26.h"
#include "ex15_26_1.h"
#include "ex15_26_2.h"

int main() {
    std::vector<Quote> ivec;
    ivec.push_back(Quote("123", 3.5));
    ivec.push_back(Bulk_quote("1234", 5.0, 10, 0.12));
    std::cout << ivec.back().net_price(10) << std::endl;

    return 0;
}