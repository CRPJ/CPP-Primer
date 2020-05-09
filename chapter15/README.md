# 目录

| [15.01](#1501)  | [15.02](#1502) | [15.03](#1503hcpp) | [15.04](#1504) | [15.05](#1505h) | [15.06](#1506cpp) |
| :-------------: | :------------: | :----------------: | :------------: | :-------------: | :---------------: |
| [15.07](#1507h) | [15.08](#1508) |                    |                |                 |                   |
|                 |                |                    |                |                 |                   |
|                 |                |                    |                |                 |                   |
|                 |                |                    |                |                 |                   |
|                 |                |                    |                |                 |                   |
|                 |                |                    |                |                 |                   |

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

## 15.04

> 下面哪条声明语句是不正确的？请解释原因。
>
> ```c++
> class Base { ... };
> (a) class Derived : public Derived { ... };
> (b) class Derived : private Base { ... };
> (c) class Derived : public Base;
> ```

(a)：错误，类不能派生自己

(b)：正确

(c)：错误，类声明中不能有派生列表

## 15.05|[h](./ex15_05.h)

> 定义你自己的 Bulk_quote 类。

```c++
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

#endif //CPP_PRIMER_EX15_05_H

```

## 15.06|[cpp](./ex15_06.cpp)

> 将 Quote 和 Bulk_quote 的对象传给15.2.1节练习中的 print_total 函数，检查该函数是否正确。

```c++
//
// Created by wangheng on 2020/5/9.
//

#include "ex15_03.h"
#include "ex15_05.h"

#include <iostream>
#include <string>

double print_total(std::ostream&, const Quote&, std::size_t);

int main() {
    Quote q("textbook", 10.60);
    Bulk_quote bq("textbook", 10.60, 10, 0.3);

    print_total(std::cout, q, 12);
    print_total(std::cout, bq, 12);

    return 0;
}

double print_total(std::ostream& os, const Quote& item, std::size_t n) {
    double ret = item.net_price(n);

    os << "ISBN: " << item.isbn() << "　＃ sold: " << n << " total due: " << ret << std::endl;

    return ret;
}
```

## 15.07|[h](./ex15_07.h)

> 定义一个类使其实现一种数量受限的折扣策略，具体策略是：当购买书籍的数量不超过一个给定的限量时享受折扣，如果购买量一旦超过了限量，则超出的部分将以原价销售。

```c++
//
// Created by wangheng on 2020/5/9.
//

#ifndef CPP_PRIMER_EX15_07_H
#define CPP_PRIMER_EX15_07_H

#include "ex15_03.h"

class Limit_quote : public Quote {
public:
    Limit_quote() = default;
    Limit_quote(const std::string& book, double p, std::size_t qty, double disc) :
        Quote(book, p), max_qty(qty), discount(disc) {}

    double net_price(std::size_t n) const override ;

private:
    std::size_t max_qty = 0;
    double discount = 0.0;
};

double Limit_quote::net_price(std::size_t n) const {
    if (n <= max_qty)
        return n * (1 - discount) * price;
    else
        return max_qty * (1 - discount) * price + (n - max_qty) * price;
}

#endif //CPP_PRIMER_EX15_07_H

```

## 15.08

> 给出静态类型和动态类型的定义。

表达式的静态类型在编译时总是已知的，它是变量声明时的类型或表达式生成的类型。动态类型则是变量或表达式表示的内存中的对象的类型。动态类型直到运行时才可知。