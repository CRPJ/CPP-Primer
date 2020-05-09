//
// Created by wangheng on 2020/5/9.
//

#ifndef CPP_PRIMER_BULK_QUOTE_H
#define CPP_PRIMER_BULK_QUOTE_H

#include "Disc_quote.h"

class Bulk_quote : public Disc_quote {
    Bulk_quote() = default;
    Bulk_quote(std::string& book, double p, std::size_t qty, double disc) :
        Disc_quote(book, p, qty, disc) {}

    double net_price(std::size_t n) const override ;
};

double Bulk_quote::net_price(std::size_t n) const {
    if (n > quantity)
        return n * (1 - discount) * price;
    else
        return n * price;
}

#endif //CPP_PRIMER_BULK_QUOTE_H
