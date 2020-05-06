//
// Created by wangheng on 2020/5/4.
//

#ifndef CPP_PRIMER_EX14_02_H
#define CPP_PRIMER_EX14_02_H

#include <string>
#include <iostream>
#include <utility>

class Sales_data {
    friend std::istream& operator>>(std::istream&, Sales_data&);    // 输入
    friend std::ostream& operator<<(std::ostream&, Sales_data&);    // 输出
    friend Sales_data operator+(const Sales_data&, const Sales_data&);  // 加法
    friend Sales_data operator-(const Sales_data&, const Sales_data&);  // 减法
public:
    Sales_data(std::string  s, unsigned n, double p) :
        bookNo(std::move(s)), units_sold(n), revenue(n * p){}
    Sales_data() : Sales_data("", 0, 0.0f) {}
    Sales_data(const std::string& s) : Sales_data(s, 0, 0.0f) {}
    Sales_data(std::istream& is);

    Sales_data& operator+=(const Sales_data&);  // 复合运算符
    Sales_data& operator-=(const Sales_data&);  // 符合运算符
    std::string isbn() const {return bookNo;}

private:
    inline double avg_price() const ;

    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

std::istream& operator>>(std::istream&, Sales_data&);
std::ostream& operator<<(std::ostream&, Sales_data&);
Sales_data operator+(const Sales_data&, const Sales_data&);
Sales_data operator-(const Sales_data&, const Sales_data&);

inline
double Sales_data::avg_price() const {
    return units_sold ? revenue / units_sold : 0;
}

#endif //CPP_PRIMER_EX14_02_H
