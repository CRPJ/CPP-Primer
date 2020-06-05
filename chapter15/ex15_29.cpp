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
    std::vector<std::shared_ptr<Quote>> ivec;
    ivec.push_back(std::make_shared<Bulk_quote>("123", 5.0, 100, 0.12));
    std::cout << ivec.back()->net_price(110) << std::endl;

    return 0;
}