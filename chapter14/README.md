# 目录

| [14.01](#1401) | [14.02](#1402) |      |      |      |      |
| :------------: | :------------: | :--: | :--: | :--: | :--: |
|                |                |      |      |      |      |
|                |                |      |      |      |      |
|                |                |      |      |      |      |
|                |                |      |      |      |      |
|                |                |      |      |      |      |
|                |                |      |      |      |      |
|                |                |      |      |      |      |
|                |                |      |      |      |      |

## 14.01
>在什么情况下重载的运算符与内置运算符有所区别？在什么情况下重载的运算符又与内置运算符一样？

我们可以直接调用重载运算符函数，重载运算符和内置运算符具有相同的优先级和结合性。
## 14.02|[h](./ex14_02.h)|[cpp](./ex14_02.cpp)
> 为`Sales_data`编写重载的输入、输出、加法和复合赋值运算符。

Sales_data类的声明
```c++
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
public:
    Sales_data(std::string  s, unsigned n, double p) :
        bookNo(std::move(s)), units_sold(n), revenue(n * p){}
    Sales_data() : Sales_data("", 0, 0.0f) {}
    Sales_data(const std::string& s) : Sales_data(s, 0, 0.0f) {}
    Sales_data(std::istream& is);

    Sales_data& operator+=(const Sales_data&);  // 复合运算符
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

inline
double Sales_data::avg_price() const {
    return units_sold ? revenue / units_sold : 0;
}

#endif //CPP_PRIMER_EX14_02_H
```
Sales_data类的实现
```c++
//
// Created by wangheng on 2020/5/4.
//

#include "ex14_02.h"

Sales_data::Sales_data(std::istream &is) {
    is >> *this;
}

Sales_data& Sales_data::operator+=(const Sales_data &rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

std::istream& operator>>(std::istream& is, Sales_data& item) {
    double price = 0.0;
    is >> item.bookNo >> item.units_sold >> price;
    if (is) {
        item.revenue = price * item.units_sold;
    } else {
        item = Sales_data();
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, Sales_data& item) {
    os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.avg_price();
    return os;
}

Sales_data operator+(const Sales_data& lhs, const Sales_data& rhs) {
    Sales_data sum = lhs;
    sum += rhs;
    return sum;
}

int main() {
    Sales_data item1(std::cin);
    Sales_data item2("2", 3, 3.4);
    Sales_data sum = item1 + item2;
    std::cout << sum << std::endl;

    return 0;
}
```
## 14.03
>`string`和`vector`都定义了重载的`==`以比较各自的对象，假设`svec1`和`svec2`是存放`string`的`vector`，确定在下面的表达式中分别使用了哪个版本的`==`？
>
>(a)`"coblle" == "stone"`   (b)`svec1[0] == svec2[0]`
>
>(c)`svec1 == svec2`        (d)`"svec1[0] == "stone"`

