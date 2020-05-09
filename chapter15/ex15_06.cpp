//
// Created by wangheng on 2020/5/9.
//

#include "ex15_03.h"
#include "ex15_05.h"

#include <iostream>
#include <string>

double print_total(std::ostream&, const Quote&, std::size_t);

int main() {
    Quote q("textbook", 10.60);
    Bulk_quote bq("textbook", 10.60, 10, 0.3);

    print_total(std::cout, q, 12);
    print_total(std::cout, bq, 12);

    return 0;
}

double print_total(std::ostream& os, const Quote& item, std::size_t n) {
    double ret = item.net_price(n);

    os << "ISBN: " << item.isbn() << "　＃ sold: " << n << " total due: " << ret << std::endl;

    return ret;
}