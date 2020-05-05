# 目录

| [14.01](#1401) | [14.02](#1402hcpp) | [14.03](#1403) | [14.04](#1404) | [14.05](#1405) |      |
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
>(c)`svec1 == svec2`        (d)`svec1[0] == "stone"`

(a)都不是，(b)使用了`string`版的`==`，(c)使用了`vector`版的`==`，(d)使用了`string`版的`==`。

## 14.04
> 如何确定下列运算符是否应该是类的成员？
>
> ```
> (a) %
> (b) %=
> (c) ++
> (d) ->
> (e) <<
> (f) &&
> (g) ==
> (h) ()
> ```

* (a)不需要是成员
* (b)是成员
* (c)是成员
* (d)必须是成员
* (e)不能是成员
* (f)不需要是成员
* (g)不需要是成员
* (h)必须是成员

## 14.05
> 在7.5.1节的练习7.40（第261页）中，编写了下列类中某一个的框架，请问在这个类张应该定义重载的运算符吗？如果是，请写出来。
>
> ```
> (a) Book
> (b) Date
> (c) Employee
> (d) Vehicle
> (e) Object
> (f) Tree
> ```

`Book`需要定义重载的运算符。

[h](./ex14_05.h)|[cpp](./ex14_05.cpp)|[test](./ex14_05_main.cpp)

book.h

```c++
//
// Created by wangheng on 2020/5/5.
//

#ifndef CPP_PRIMER_EX14_05_H
#define CPP_PRIMER_EX14_05_H

#include <iostream>
#include <string>

class Book {
    friend std::istream& operator>>(std::istream&, Book&);
    friend std::ostream& operator<<(std::ostream&, const Book&);
    friend bool operator==(const Book&, const Book&);
    friend bool operator!=(const Book&, const Book&);

public:
    Book() = default;
    Book(unsigned no, std::string name, std::string author, std::string pubDate) :
        no(no), name(name), author(author), pubDate(pubDate) {}
    Book(std::istream& in) {in >> *this;}

private:
    unsigned no;
    std::string name;
    std::string author;
    std::string pubDate;
};

std::istream& operator>>(std::istream&, Book&);
std::ostream& operator<<(std::ostream&, const Book&);
bool operator==(const Book&, const Book&);
bool operator!=(const Book&, const  Book&);

#endif //CPP_PRIMER_EX14_05_H

```

book.cpp
```c++
//
// Created by wangheng on 2020/5/5.
//

#include "ex14_05.h"

std::istream& operator>>(std::istream& in, Book& book) {
    in >> book.no >> book.name >> book.author >> book.pubDate;
    return in;
}
std::ostream& operator<<(std::ostream& os, const Book& book) {
    os << book.no << ' ' << book.name << ' ' << book.author << ' ' << book.pubDate;
    return os;
}
bool operator==(const Book& lhs, const Book& rhs) {
    return lhs.no == rhs.no;
}
bool operator!=(const Book& lhs, const  Book& rhs) {
    return !(lhs.no == rhs.no);
}
```

main.cpp

```c++
//
// Created by wangheng on 2020/5/5.
//

#include "ex14_05.h"

int main() {
    Book book1(123, "Journey to the West", "Chengen Wu", "Ming dynasty");
    Book book2(123, "西游记", "吴承恩", "明朝");
    std::cout << book1 << ' ' << book2 << std::endl;
    std::cout << std::boolalpha << (book1 == book2) << std::endl;
    Book book3(std::cin);
    std::cout << (book2 == book3) << std::endl;

    return 0;
}
```



