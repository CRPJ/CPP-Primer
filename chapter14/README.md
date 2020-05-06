# 目录

| [14.01](#1401) | [14.02](#1402hcpp) | [14.03](#1403) | [14.04](#1404) | [14.05](#1405) | [14.06](#1406hcpp) |
| :------------: | :------------: | :--: | :--: | :--: | :--: |
| [14.07](#1407hcpp) | [14.08](#1408hcpp) | [14.09](#1409hcpp) | [14.10](#1410) | [14.11](#1411) | [14.12](#1412hcpp) |
| [14.13](#1413hcpp) | [14.14](#1414) | [14.15](#1415hcpptest) | [14.16](#1416) | [14.17](#1417) | [14.18](#1418) |
| [14.19](#1419) |                |      |      |      |      |
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

## 14.06|[h](./ex14_02.h)|[cpp](./ex14_02.cpp)

> 为你的Sales_data类定义输出运算符。

见练习14.2的代码

## 14.07|[h](../chapter13/ex13_44.h)|[cpp](../chapter13/ex13_44.cpp)

> 你在13.5节的练习（第470页）中曾经编写了一个`String`类，为它定义一个输出运算符。

见练习13.44的代码

## 14.08|[h](./ex14_05.h)|[cpp](./ex14_05.cpp)

> 你在7.5.1节的练习7.40（第261页）中曾经选择并编写了一个类，为它定义一个输出运算符。

见练习14.05的代码。

## 14.09|[h](./ex14_02.h)|[cpp](./ex14_02.cpp)

> 为你的Sales_data类定义输入运算符。

见练习14.02的代码

## 14.10

> 对于Sales_data的输入运算符来说如果给定了下面的输入将发生什么情况？

```
(a)0-201-99999-9 10 24.95
(b)10 24.95 0-210-99999-9
```

(a)格式正确，可以正常构造一个`Sales_data`对象

(b)非法输入，因为程序试图将`0-210-99999-9`字符串转换为`double`类型，所以输入操作失败，但是输入运算符重载代码中处理了这一情况，会给读取失败的对象用默认构造函数初始化。

## 14.11

>  下面的 `Sales_data` 输入运算符存在错误吗？如果有，请指出来。对于这个输入运算符如果仍然给定上个练习的输入将会发生什么情况？ 
>
> ```c++
> istream& operator>>(istream& in, Sales_data& s)
> {
> 	double price;
> 	in >> s.bookNo >> s.units_sold >> price;
> 	s.revence = s.units_sold * price;
> 	return in;
> }
> ```

存在错误，因为这样重载输入运算符没有对输入操作失败的情况进行处理。针对上一题，(a)格式正确，可以正常构造一个`Sales_data`对象，但是(b)由于输入格式错误，不能成功构造一个对象。

## 14.12|[h](./ex14_05.h)|[cpp](./ex14_05.cpp)

>  你在7.5.1节的练习中曾经选择并编写了一个类，为它定义一个输入运算符并确保该运算符可以处理输入错误。 

## 14.13|[h](./ex14_02.h)|[cpp](./ex14_02.cpp)

>  你认为 Sales_data 类还应该支持哪些其他算术运算符？如果有的话，请给出它们的定义。 

`Sales_data`可以重载`-`、`-=`运算符。具体实现见练习14.02的代码。

## 14.14

>  你觉得为什么调用 operator+= 来定义operator+ 比其他方法更有效？ 

 因为用 `operator+=` 会避免使用一个临时对象，而使得更有效。 

## 14.15|[h](./ex14_15.h)|[cpp](./ex14_15.cpp)|[test](./ex14_15_main.cpp)

>  你在7.5.1节的练习7.40中曾经选择并编写了一个类，你认为它应该含有其他算术运算符吗？如果是，请实现它们；如果不是，解释原因。 

可以给`Book`类添加`<`、`>`、`+`、`-`重载运算符。

`Book.h`

```c++
//
// Created by wangheng on 2020/5/6.
//

#ifndef CPP_PRIMER_EX14_15_H
#define CPP_PRIMER_EX14_15_H

#include <iostream>
#include <string>

class Book {
    friend std::istream& operator>>(std::istream&, Book&);
    friend std::ostream& operator<<(std::ostream&, const Book&);
    friend bool operator==(const Book&, const Book&);
    friend bool operator!=(const Book&, const Book&);
    friend bool operator<(const Book&, const Book&);
    friend bool operator>(const Book&, const Book&);
    friend Book operator+(const Book&, const Book&);
    friend Book operator-(const Book&, const Book&);

public:
    Book() = default;
    Book(unsigned no, std::string name, std::string author, std::string pubDate, unsigned number) :
            no(no), name(name), author(author), pubDate(pubDate), number(number) {}
    Book(std::istream& in) {in >> *this;}
    Book& operator+=(const Book&);
    Book& operator-=(const Book&);

private:
    unsigned no;
    std::string name;
    std::string author;
    std::string pubDate;
    unsigned number = 0;
};

std::istream& operator>>(std::istream&, Book&);
std::ostream& operator<<(std::ostream&, const Book&);
bool operator==(const Book&, const Book&);
bool operator!=(const Book&, const  Book&);
bool operator<(const Book&, const Book&);
bool operator>(const Book&, const Book&);
Book operator+(const Book&, const Book&);
Book operator-(const Book&, const Book&);

#endif //CPP_PRIMER_EX14_15_H

```

`Book.cpp`

```c++
//
// Created by wangheng on 2020/5/6.
//

#include "ex14_15.h"

Book& Book::operator+=(const Book &rhs) {
    number += rhs.number;
    return *this;
}

Book& Book::operator-=(const Book &rhs) {
    number -= rhs.number;
    return *this;
}

std::istream& operator>>(std::istream& in, Book& book) {
    in >> book.no >> book.name >> book.author >> book.pubDate >> book.number;
    if (!in)
        book = Book();
    return in;
}
std::ostream& operator<<(std::ostream& os, const Book& book) {
    os << book.no << ' ' << book.name << ' ' << book.author << ' ' << book.pubDate << ' ' << book.number;
    return os;
}
bool operator==(const Book& lhs, const Book& rhs) {
    return lhs.no == rhs.no;
}
bool operator!=(const Book& lhs, const  Book& rhs) {
    return !(lhs.no == rhs.no);
}

bool operator<(const Book& lhs, const Book& rhs) {
    return lhs.no < rhs.no;
}
bool operator>(const Book&lhs, const Book& rhs) {
    return lhs.no > rhs.no;
}
Book operator+(const Book& lhs, const Book& rhs) {
    Book result = lhs;
    result += rhs;
    return result;
}
Book operator-(const Book& lhs, const Book& rhs) {
    Book result = lhs;
    result -= rhs;
    return result;
}
```

`main.cpp`

```c++
//
// Created by wangheng on 2020/5/6.
//

#include <iostream>
#include "ex14_15.h"

int main() {
    Book book1(123, "Journey to the West", "Chengen Wu", "Ming dynasty", 2);
    Book book2(123, "西游记", "吴承恩", "明朝", 3);
    std::cout << book1 << ' ' << book2 << std::endl;
    std::cout << std::boolalpha << (book1 == book2) << std::endl;
    Book book3(std::cin);
    std::cout << (book2 == book3) << std::endl;
    std::cout << (book1 + book2) << std::endl;

    return 0;
}
```

## 14.16

>  为你的 `StrBlob` 类、`StrBlobPtr` 类、`StrVec` 类和 `String` 类分别定义相等运算符和不相等运算符。 

`StrBlob`|[h](../chapter12/ex12_19.h)|[cpp](../chapter12/ex12_19.cpp)

`StrBlobPtr`|[h](../chapter12/ex12_19.h)|[cpp](../chapter12/ex12_19.cpp)

`StrVec`|[h](../chapter13/ex13_43.h)|[cpp](../chapter13/ex13_43.cpp)

`String`|[h](../chapter13/ex13_44.h)|[cpp](../chapter13/ex13_44.cpp)

## 14.17

>  你在7.5.1节中的练习7.40中曾经选择并编写了一个类，你认为它应该含有相等运算符吗？如果是，请实现它；如果不是，解释原因。 

应该有相等运算符，代码见练习14.05。[h](./ex14_05.h)|[cpp](./ex14_05.cpp)

## 14.18

>  为你的 `StrBlob` 类、`StrBlobPtr` 类、`StrVec` 类和 `String` 类分别定义关系运算符。 

`StrBlob`|[h](../chapter12/ex12_19.h)|[cpp](../chapter12/ex12_19.cpp)

`StrBlobPtr`|[h](../chapter12/ex12_19.h)|[cpp](../chapter12/ex12_19.cpp)

`StrVec`|[h](../chapter13/ex13_43.h)|[cpp](../chapter13/ex13_43.cpp)

`String`|[h](../chapter13/ex13_44.h)|[cpp](../chapter13/ex13_44.cpp)

## 14.19

>  你在7.5.1节的练习7.40中曾经选择并编写了一个类，你认为它应该含有关系运算符吗？如果是，请实现它；如果不是，解释原因。 

应该有，代码见练习14.05。[h](./ex14_05.h)|[cpp](./ex14_05.cpp)

