//
// Created by wangheng on 2020/6/5.
//

#ifndef CPP_PRIMER_EX15_26_2_H
#define CPP_PRIMER_EX15_26_2_H

#include <iostream>
#include "ex15_26_1.h"

class Bulk_quote : public Disk_quote{
public:
    Bulk_quote() { std::cout << "Bulk_quote: default constructor" << std::endl; }
    Bulk_quote(const std::string& b, double p, std::size_t n, double d) :
        Disk_quote(b, p, n, d) {
        std::cout << "Bulk_quote: normal constructor" << std::endl;
    }

    Bulk_quote(const Bulk_quote& bulk) :
        Disk_quote(bulk) {
        std::cout << "Bulk_quote: copy constructor" << std::endl;
    }

    Bulk_quote& operator=(const Bulk_quote& rhs) {
        if (this != &rhs) {
            Disk_quote::operator=(rhs);
        }
        std::cout << "Bulk_quote: copy operator()" << std::endl;
        return *this;
    }

    Bulk_quote(Bulk_quote&& bulk) : Disk_quote(std::move(bulk)) {
        std::cout << "Bulk_quote: move constructor" << std::endl;
    }

    Bulk_quote& operator=(Bulk_quote&& rhs) {
        if (this != &rhs) {
            Disk_quote::operator=(rhs);
        }
        std::cout << "Bulk_quote: move operator=()" << std::endl;
        return *this;
    }

    ~Bulk_quote() {
        std::cout << "Bulk_quote: destructor" << std::endl;
    }

    double net_price(std::size_t n) const override {
        if (n < quantity)
            return n * price;
        else {
            return (n - quantity) * price * (1 - discount) + quantity * price;
        }
    }
};

#endif //CPP_PRIMER_EX15_26_2_H
