//
// Created by wangheng on 2020/5/9.
//

#ifndef CPP_PRIMER_DISC_QUOTE_H
#define CPP_PRIMER_DISC_QUOTE_H

#include "ex15_03.h"

class Disc_quote : public Quote {
public:
    Disc_quote() = default;
    Disc_quote(const std::string& book, double p, std::size_t qty, double disc) :
        Quote(book, p), quantity(qty), discount(disc) {}

    double net_price(std::size_t) const override = 0;

protected:
    std::size_t quantity = 0;
    double discount = 0.0;
};

#endif //CPP_PRIMER_DISC_QUOTE_H
