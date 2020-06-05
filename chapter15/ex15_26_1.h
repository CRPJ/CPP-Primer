//
// Created by wangheng on 2020/6/5.
//

#ifndef CPP_PRIMER_EX15_26_1_H
#define CPP_PRIMER_EX15_26_1_H

#include "ex15_26.h"

class Disk_quote : public Quote{
public:
    Disk_quote() {
        std::cout << "Disk_quote: default constructor" << std::endl;
    }

    Disk_quote(const std::string& b, double p, std::size_t n, double d) :
        Quote(b, p), quantity(n), discount(d) {
        std::cout << "Disk_quote: constructor takes 4 parameters" << std::endl;
    }

    Disk_quote(const Disk_quote& disk) :
        Quote(disk), quantity(disk.quantity), discount(disk.discount) {
        std::cout << "Disk_quote: copy constructor" << std::endl;
    }

    Disk_quote& operator=(const Disk_quote& rhs) {
        if (this != &rhs) {
            Quote::operator=(rhs);
            quantity = rhs.quantity;
            discount = rhs.discount;
        }
        std::cout << "Disk_quote: copy operator=()" << std::endl;

        return *this;
    }

    Disk_quote(Disk_quote&& disk) noexcept :
        Quote(std::move(disk)), quantity(disk.quantity), discount(disk.discount) {
        std::cout << "Disk_quote: move constructor" << std::endl;
    }

    Disk_quote& operator=(Disk_quote&& rhs) noexcept {
        if (this != &rhs) {
            Quote::operator=(rhs);
            quantity = rhs.quantity;
            discount = rhs.discount;
        }
        std::cout << "Disk_quote: move operator=()" << std::endl;

        return *this;
    }

    ~Disk_quote() {
        std::cout << "Disk_quote: destructor" << std::endl;
    }

    double net_price(std::size_t n) const override {
        if (n < quantity)
            return n * price;
        else
            return n * price * (1 - discount);
    }

protected:
    std::size_t quantity = 0;
    double discount = 0.0;
};

#endif //CPP_PRIMER_EX15_26_1_H
