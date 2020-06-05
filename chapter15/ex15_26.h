//
// Created by wangheng on 2020/6/5.
//

#ifndef CPP_PRIMER_EX15_26_H
#define CPP_PRIMER_EX15_26_H

#include <string>
#include <iostream>

class Quote{
public:
    Quote() { std::cout << "Quote: default constructor" << std::endl; }

    Quote(const std::string& b, double p) : bookNo(b), price(p) {
        std::cout << "Quote(const std::string&, double p) " << std::endl;
    }
    // copy constructor
    Quote(const Quote& q) :bookNo(q.bookNo), price(q.price) {
        std::cout << "Quote: copy constructor" << std::endl;
    }

    Quote& operator=(const Quote& rhs) {
        if (this != &rhs) {
            bookNo = rhs.bookNo;
            price = rhs.price;
        }
        std::cout << "Quote: copy =()" << std::endl;

        return *this;
    }
    // move constructor
    Quote(Quote&& q) noexcept : bookNo(std::move(q.bookNo)), price(std::move(q.price)) {
        std::cout << "Quote: move constructor" << std::endl;
    }

    Quote& operator=(Quote&& rhs) noexcept {
        if (this != &rhs) {
            bookNo = std::move(rhs.bookNo);
            price = std::move(rhs.price);
        }
        std::cout << "Quote: move =()" << std::endl;

        return *this;
    }

    std::string isbn() { return bookNo; }
    virtual double net_price(std::size_t n) const { return n * price; }
    virtual ~Quote() {
        std::cout << "Quote: destructor" << std::endl;
    }

private:
    std::string bookNo;

protected:
    double price = 0.0;
};

#endif //CPP_PRIMER_EX15_26_H
