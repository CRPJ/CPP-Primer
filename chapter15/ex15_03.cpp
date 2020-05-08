//
// Created by wangheng on 2020/5/8.
//

#include "ex15_03.h"

double print_total(std::ostream& os, const Quote& item, std::size_t n);

int main() {
    Quote book("Little Princess", 5);
    print_total(std::cout, book, 3);
    return 0;
}

double print_total(std::ostream& os, const Quote& item, std::size_t n) {
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << std::endl;

    return ret;
}