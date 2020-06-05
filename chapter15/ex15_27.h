//
// Created by wangheng on 2020/6/5.
//

#ifndef CPP_PRIMER_EX15_27_H
#define CPP_PRIMER_EX15_27_H

#include <iostream>
#include "Disc_quote.h"

class Bulk_quote : public Disc_quote{
public:
    Bulk_quote() {
        std::cout << "default constructor" << std::endl;
    }

    using Disc_quote::Disc_quote;

    Bulk_quote(const Bulk_quote& bq) :
        Disc_quote(bq) {
        std::cout << "Bulk_quote: copy constructor" << std::endl;
    }

    Bulk_quote(Bulk_quote&& bq) : Disc_quote(std::move(bq)) {
        std::cout << "Bulk_quote: move constructor" << std::endl;
    }

    Bulk_quote& operator=(const Bulk_quote& rhs) {
        Disc_quote::operator=(rhs);
        std::cout << "Bulk_quote: copy =()" << std::endl;

        return *this;
    }

    Bulk_quote& operator=(Bulk_quote&& rhs) noexcept {
        Disc_quote::operator=(std::move(rhs));
        std::cout << "Bulk_quote: move =()" << std::endl;

        return *this;
    }

    double net_price(std::size_t n) const override {
        if (n < quantity)
            return n * price;
        else
            return n * (1 - discount) * price;
    }

    ~Bulk_quote() {
        std::cout << "destructor" << std::endl;
    }
};

#endif //CPP_PRIMER_EX15_27_H
