//
// Created by wangheng on 2020/5/9.
//

#ifndef CPP_PRIMER_EX15_07_H
#define CPP_PRIMER_EX15_07_H

#include "ex15_03.h"

class Limit_quote : public Quote {
public:
    Limit_quote() = default;
    Limit_quote(const std::string& book, double p, std::size_t qty, double disc) :
        Quote(book, p), max_qty(qty), discount(disc) {}

    double net_price(std::size_t n) const override ;

private:
    std::size_t max_qty = 0;
    double discount = 0.0;
};

double Limit_quote::net_price(std::size_t n) const {
    if (n <= max_qty)
        return n * (1 - discount) * price;
    else
        return max_qty * (1 - discount) * price + (n - max_qty) * price;
}

#endif //CPP_PRIMER_EX15_07_H
