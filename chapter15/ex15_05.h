//
// Created by wangheng on 2020/5/9.
//

#ifndef CPP_PRIMER_EX15_05_H
#define CPP_PRIMER_EX15_05_H

#include "ex15_03.h"

class Bulk_quote : public Quote {
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string& book, double p, std::size_t qty, double disc) :
        Quote(book, p), min_qty(qty), discount(disc) {}
    double net_price(std::size_t) const override ;
    void debug() const override ;

private:
    std::size_t min_qty = 0;
    double discount = 0.0;
};

double Bulk_quote::net_price(std::size_t cnt) const {
    if (cnt >= min_qty)
        return cnt * (1 - discount) * price;
    else
        return cnt * price;
}

void Bulk_quote::debug() const {
    std::cout << "data members of this class:\n"
        << "price = " << price << " "
        << "min_qty = " << min_qty << " "
        << "discount = " << discount << std::endl;
}

#endif //CPP_PRIMER_EX15_05_H
