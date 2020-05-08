# 目录

| [15.01](#1501) | [15.02](#1502) | [15.03](#1503hcpp) |      |      |      |
| :------------: | :------------: | :----------------: | :--: | :--: | :--: |
|                |                |                    |      |      |      |
|                |                |                    |      |      |      |
|                |                |                    |      |      |      |
|                |                |                    |      |      |      |
|                |                |                    |      |      |      |
|                |                |                    |      |      |      |

## 15.01

> 什么是虚成员？

对于某些函数，基类希望它的派生类各自定义适合自身的不同版本，此时基类就将这些函数生命成虚函数。

## 15.02

>  protected 访问说明符与 private 有何区别？

* `protected`：基类和其派生类还有友元可以访问。
* `private`：只有基类和友元可以访问。

## 15.03|[h](./ex15_03.h)|[cpp](./ex15_03.cpp)

> 定义你自己的 `Quote` 类和 `print_total` 函数。

`Quote.h`

```c++
//
// Created by wangheng on 2020/5/8.
//

#ifndef CPP_PRIMER_EX15_03_H
#define CPP_PRIMER_EX15_03_H

#include <iostream>

class Quote {
public:
    Quote() = default;
    Quote(const std::string& book, double sales_price) :
        bookNo(book), price(sales_price) {}
    std::string isbn() const { return bookNo; }
    virtual double net_price(std::size_t n) const { return n * price; }
    virtual ~Quote() = default;

private:
    std::string bookNo;

protected:
    double price = 0.0;
};
#endif //CPP_PRIMER_EX15_03_H

```

`print_total`函数

```c++
//
// Created by wangheng on 2020/5/8.
//

#include "ex15_03.h"

double print_total(std::ostream& os, const Quote& item, std::size_t n);

int main() {
    Quote book("Little Princess", 5);
    print_total(std::cout, book, 3);
    return 0;
}

double print_total(std::ostream& os, const Quote& item, std::size_t n) {
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << std::endl;

    return ret;
}
```

