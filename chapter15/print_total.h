//
// Created by wangheng on 2020/6/7.
//

#ifndef CPP_PRIMER_PRINT_TOTAL_H
#define CPP_PRIMER_PRINT_TOTAL_H

#include <iostream>
#include "ex15_26.h"

double print_total(std::ostream& os, const Quote &item, std::size_t n) {
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << std::endl;
    return ret;
}

#endif //CPP_PRIMER_PRINT_TOTAL_H
