# 目录

| [14.01](#1401) | [14.02](#1402hcpp) | [14.03](#1403) | [14.04](#1404) | [14.05](#1405) | [14.06](#1406hcpp) |
| :------------: | :------------: | :--: | :--: | :--: | :--: |
| [14.07](#1407hcpp) | [14.08](#1408hcpp) | [14.09](#1409hcpp) | [14.10](#1410) | [14.11](#1411) | [14.12](#1412hcpp) |
| [14.13](#1413hcpp) | [14.14](#1414) | [14.15](#1415hcpptest) | [14.16](#1416) | [14.17](#1417) | [14.18](#1418) |
| [14.19](#1419) | [14.20](#1420) | [14.21](#1421) | [14.22](#1422hcpp) | [14.23](#1423hcpp) | [14.24](#1424) |
| [14.25](#1425) | [14.26](#1426) | [14.27](#1427hcpp) | [14.28](#1428hcpp) | [14.29](#1429) | [14.30](#1430) |
| [14.31](#1431) | [14.32](#1432) | [14.33](#1433) | [14.34](#1434) | [14.35](#1435cpp) | [14.36](#1436cpp) |
| [14.37](#1437cpp) | [14.38](#1438cpp) | [14.39](#1439cpp) | [14.40](#1440cpp) | [14.41](#1441) | [14.42](#1442) |
| [14.43](#1443cpp) | [14.44](#1444cpp) |      |      |      |      |
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

## 14.20

>  为你的 Sales_data 类定义加法和复合赋值运算符。 

参看练习14.02的代码。[14.02](#1402hcpp)

## 14.21

>  编写 `Sales_data` 类的+ 和+= 运算符，使得 + 执行实际的加法操作而 += 调用+。相比14.3节和14.4节对这两个运算符的定义，本题的定义有何缺点？试讨论之。 

 缺点：使用了一个 `Sales_data` 的临时对象，但它并不是必须的。 

## 14.22[h](./ex14_02.h)|[cpp](./ex14_02.cpp)

> 定义赋值运算符的一个新版本，使得我们能把一个表示 ISBN 的 string 赋给一个 Sales_data 对象。

## 14.23|[h](../chapter13/ex13_43.h)|[cpp](../chapter13/ex13_43.cpp)

> 为你的`StrVec` 类定义一个 `initializer_list` 赋值运算符。

## 14.24

>  你在7.5.1节的练习7.40中曾经选择并编写了一个类，你认为它应该含有拷贝赋值和移动赋值运算符吗？如果是，请实现它们。

见练习14.15的代码。[h](./ex14_15.h)|[cpp](./ex14_15.cpp)|[test](./ex14_15_main.cpp)

## 14.25

>  上题的这个类还需要定义其他赋值运算符吗？如果是，请实现它们；同时说明运算对象应该是什么类型并解释原因。 

是，如上题。

## 14.26

> 为你的 `StrBlob` 类、`StrBlobPtr` 类、`StrVec` 类和 `String` 类定义下标运算符。

`StrBlob`|[h](../chapter12/ex12_19.h)|[cpp](../chapter12/ex12_19.cpp)

`StrBlobPtr`|[h](../chapter12/ex12_19.h)|[cpp](../chapter12/ex12_19.cpp)

`StrVec`|[h](../chapter13/ex13_43.h)|[cpp](../chapter13/ex13_43.cpp)

`String`|[h](../chapter13/ex13_44.h)|[cpp](../chapter13/ex13_44.cpp)

## 14.27|[h](../chapter12/ex12_19.h)|[cpp](../chapter12/ex12_19.cpp)

>  为你的 `StrBlobPtr` 类添加递增和递减运算符。 

见练习12.19的代码。

## 14.28|[h](../chapter12/ex12_19.h)|[cpp](../chapter12/ex12_19.cpp)

>  为你的 `StrBlobPtr` 类添加加法和减法运算符，使其可以实现指针的算术运算。 

见练习12.19的代码。

## 14.29

>  为什么不定义`const` 版本的递增和递减运算符？ 

因为递增和递减会改变对象本身，所以不能定义`const`版本的递增递减运算符。

## 14.30

>  为你的 `StrBlobPtr` 类和在12.1.6节练习12.22中定义的 `ConstStrBlobPtr` 的类分别添加解引用运算符和箭头运算符。注意：因为 `ConstStrBlobPtr` 的数据成员指向`const vector`，所以`ConstStrBlobPtr` 中的运算符必须返回常量引用。 

`StrBlobPtr`|[h](../chapter12/ex12_19.h)|[cpp](../chapter12/ex12_19.cpp)

`ConstStrBlobPtr`|[h](../chapter12/ex12_22.h)|[cpp](../chapter12/ex12_22.cpp)

## 14.31

>  我们的 `StrBlobPtr` 类没有定义拷贝构造函数、赋值运算符以及析构函数，为什么？ 

因为合成的默认版本足够满足要求。

## 14.32

>  定义一个类令其含有指向 `StrBlobPtr` 对象的指针，为这个类定义重载的箭头运算符。 

```c++
class StrBlobPtr;

class StrBlobPtr_pointer
{
public:
    StrBlobPtr_pointer() = default;
    StrBlobPtr_pointer(StrBlobPtr* p) : pointer(p) { }

    StrBlobPtr& operator *();
    StrBlobPtr* operator->();

private:
    StrBlobPtr* pointer = nullptr;
};
```

## 14.33

> 一个重载的函数调用运算符应该接受几个运算对象？

一个重载的函数调用运算符接受的运算对象应该和该运算符拥有的操作数一样多。

## 14.34

> 定义一个函数对象类，令其执行if-then-else 的操作：该类的调用运算符接受三个形参，它首先检查第一个形参，如果成功返回第二个形参值；如果不成功返回第三个形参的值。

```c++
struct Test {
    int operator()(bool flag, int a, int b) {
        return flag ? a : b;
    }
};
```

## 14.35|[cpp](./ex14_35.cpp)

> 编写一个类似于 `PrintString `的类，令其从 `istream` 中读取一行输入，然后返回一个表示我们所读内容的`string`。如果读取失败，返回空string。

```c++
//
// Created by wangheng on 2020/5/7.
//

#include <iostream>
#include <string>

class PrintString {
public:
    PrintString(std::istream& is = std::cin) : is(is) {}
    std::string operator()() const {
        std::string str;
        std::getline(is, str);
        return is ? str : std::string();
    }

private:
    std::istream& is;
};

int main() {
    PrintString printer;
    std::cout << printer() << std::endl;

    return 0;
}
```

## 14.36|[cpp](./ex14_36.cpp)

> 使用前一个练习定义的类读取标准输入，将每一行保存为 vector 的一个元素。

```c++
//
// Created by wangheng on 2020/5/7.
//

#include <iostream>
#include <string>
#include <vector>

class PrintString {
public:
    PrintString(std::istream& is = std::cin) : is(is) {}
    std::string operator()() const {
        std::string str;
        std::getline(is, str);
        return is ? str : std::string();
    }

private:
    std::istream& is;
};

int main() {
    PrintString printer;
    std::vector<std::string> sv;
    for (std::string temp; !(temp = printer()).empty(); )
        sv.push_back(temp);
    for (const auto &str : sv)
        std::cout << str << ' ';
    std::cout << std::endl;

    return 0;
}
```

## 14.37|[cpp](./ex14_37.cpp)

> 编写一个类令其检查两个值是否相等。使用该对象及标准库算法编写程序，令其替换某个序列中具有给定值的所有实例。

```c++
//
// Created by wangheng on 2020/5/7.
//

#include <iostream>
#include <algorithm>
#include <vector>

class IsEqual {
public:
    IsEqual(int v) :value(v) {}
    bool operator()(int elem) {
        return value == elem;
    }

private:
    int value;
};

int main() {
    std::vector<int> vec{3, 2, 1, 4, 3, 7};
    std::replace_if(vec.begin(), vec.end(), IsEqual(3), 5);
    for (int i : vec)
        std::cout << i << ' ';
    std::cout << std::endl;

    return 0;
}
```

## 14.38|[cpp](./ex14_38.cpp)

> 编写一个类令其检查某个给定的 `string` 对象的长度是否与一个阈值相等。使用该对象编写程序，统计并报告在输入的文件中长度为1的单词有多少个，长度为2的单词有多少个、......、长度为10的单词有多少个。

```c++
//
// Created by wangheng on 2020/5/7.
//

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>

class GetLength {
public:
    GetLength(std::size_t n) : sz(n) {}
    bool operator()(const std::string& s) {
        return s.size() == sz;
    }

private:
    std::size_t sz;
};

int main() {
    std::ifstream infile("C:\\Users\\wh969\\Desktop\\code\\CPP-Primer\\data\\ex14_38.txt", std::ios::in);
    std::vector<std::string> words;
    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream line_words(line);
        std::string word;
        while (line_words >> word)
            words.push_back(word);
    }

    // 对words按长度从小到大排序
    std::stable_sort(words.begin(), words.end(),
                     [] (const std::string& s1, const std::string& s2) {return s1.size() < s2.size();});

    // 计算words中最长的string的长度
    std::size_t maxLength = (words.end() - 1)->size();

    for (std::size_t i = 1; i <= maxLength; ++i) {
        auto number = std::count_if(words.begin(), words.end(), GetLength(i));
        std::cout << "Length " << i << ": " << number << std::endl;
        auto first = std::find_if(words.begin(), words.end(), GetLength(i));
        for (auto iter = first; iter != first + number; ++iter)
            std::cout << *iter << ' ';
        std::cout << std::endl;
    }

    return 0;
}
```

## 14.39|[cpp](./ex14_39.cpp)

> 修改上一题的程序令其报告长度在1到9之间的单词有多少个、长度在10以上的单词有多少个。

```c++
//
// Created by wangheng on 2020/5/7.
//

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>

class GetLength {
public:
    GetLength(std::size_t n) : sz(n) {}
    bool operator()(const std::string& s) {
        return s.size() == sz;
    }

private:
    std::size_t sz;
};

int main() {
    std::ifstream infile("C:\\Users\\wh969\\Desktop\\code\\CPP-Primer\\data\\ex14_38.txt", std::ios::in);
    std::vector<std::string> words;
    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream line_words(line);
        std::string word;
        while (line_words >> word)
            words.push_back(word);
    }

    // 对words按长度从小到大排序
    std::stable_sort(words.begin(), words.end(),
                     [] (const std::string& s1, const std::string& s2) {return s1.size() < s2.size();});

    std::size_t sz = 1;
    while (sz < 10) {
        auto number = std::count_if(words.begin(), words.end(), GetLength(sz));
        std::cout << "Length " << sz << ": " << number << std::endl;
        auto first = std::find_if(words.begin(), words.end(), GetLength(sz));
        for (auto iter = first; iter != first + number; ++iter)
            std::cout << *iter << ' ';
        std::cout << std::endl;
        ++sz;
    }
    auto first = std::find_if(words.begin(), words.end(),
            [sz](const std::string& s) {return s.size() >= sz;});
    std::cout << "Length >= 10: " << words.end() - first << std::endl;
    for (auto iter = first; iter != words.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << std::endl;

    return 0;
}
```

## 14.40|[cpp](./ex14_40.cpp)

> 重新编写10.3.2节的biggies 函数，使用函数对象替换其中的 lambda 表达式。

```c++
//
// Created by wangheng on 2020/5/7.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

class ShorterString {
public:
    bool operator()(const std::string& s1, const std::string& s2) const {
        return s1.size() < s2.size();
    }
};

class BiggerEqual {
public:
    BiggerEqual(std::size_t n) : sz(n) {}
    bool operator()(const std::string& s) {
        return s.size() >= sz;
    }

private:
    std::size_t sz;
};

class Printer {
public:
    Printer(std::ostream& os = std::cout, std::string str = " ") :
        os(os), str(str) {}
    void operator()(const std::string& s) {
        os << s << str;
    }

private:
    std::ostream& os;
    std::string str;
};

std::string make_plural(std::size_t ctr, const std::string &word, const std::string& ending) {
    return (ctr > 1) ? word + ending : word;
}

// 将wors按字典顺序排序，删除重复单词
void elimDups(std::vector<std::string>& words) {
    std::sort(words.begin(), words.end());
    auto end_unique = std::unique(words.begin(), words.end());
    words.erase(end_unique, words.end());
}

void biggies(std::vector<std::string>& words, std::vector<std::string>::size_type sz) {
    elimDups(words);
    std::stable_sort(words.begin(), words.end(), ShorterString());
    auto wc = std::find_if(words.begin(), words.end(), BiggerEqual(sz));
    auto count = words.end() - wc;
    std::cout << count << " " << make_plural(count, "word", "s")
        << " of length " << sz << " or longer" << std::endl;
    std::for_each(wc, words.end(), Printer());
    std::cout << std::endl;
}

int main() {
    std::vector<std::string> words = {"an", "the", "good", "football", "bike", "Chinese"};
    biggies(words, 4);

    return 0;
}
```



## 14.41

>  你认为 C++ 11 标准为什么要增加 lambda？对于你自己来说，什么情况下会使用 lambda，什么情况下会使用类？ 

使用`lambda`非常方便，当需要使用一个函数且这个函数非常简单和不常用时，使用`lambda`是比较简单的选择。

## 14.42

> 使用标准库函数对象及适配器定义一条表达式，令其
>
> ```
> (a) 统计大于1024的值有多少个。 
> (b) 找到第一个不等于pooh的字符串。
> (c)将所有的值乘以2。
> ```

统计大于1024的值的个数：

```c++
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {1,2,3,1025,2343,43554};
    auto count = std::count_if(vec.begin(), vec.end(),
            std::bind(std::greater<int>(), std::placeholders::_1, 1024));
    std::cout << count << std::endl;

    return 0;
}
```

找到第一个不等于`pooh`的字符串：

```c++
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <string>

int main() {
    std::vector<std::string> vec{"pooh", "pooh", "pooh", "good", "pooh"};
    auto first = std::find_if(vec.begin(), vec.end(),
            std::bind(std::not_equal_to<std::string>(), std::placeholders::_1, "pooh"));
    std::cout << *first << std::endl;

    return 0;
}
```

将所有的值乘2：

```c++
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec{1,2,3,4,5,6};
    std::transform(vec.begin(), vec.end(), vec.begin(),
            std::bind(std::multiplies<int>(), std::placeholders::_1, 2));
    for (auto iter = vec.begin(); iter != vec.end(); ++iter)
        std::cout << *iter << ' ';
    std::cout << std::endl;

    return 0;
}
```

## 14.43|[cpp](./ex14_43.cpp)

> 使用标准库函数对象判断一个给定的int值是否能被 int 容器中的所有元素整除。

```c++
//
// Created by wangheng on 2020/5/8.
//

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

int main() {
    bool flag = true;
    std::vector<int> vec{2,6,4,8};
    // 判断2是否能被容器内的所有元素整除
    auto count = std::count_if(vec.begin(), vec.end(),
            std::bind(std::equal_to<int>(), std::bind(std::modulus<int>(), std::placeholders::_1, 2), 0));
    if (count != vec.size())
        flag = false;
    std::cout << std::boolalpha << flag << std::endl;

    return 0;
}
```

## 14.44|[cpp](./ex14_44.cp)

> 编写一个简单的桌面计算器使其能处理二元运算。

```c++
//
// Created by wangheng on 2020/5/8.
//

#include <iostream>
#include <map>
#include <functional>
#include <string>

int add(int i, int j) { return i + j; }
auto mod = [](int i, int j) { return i % j; };
struct Div {int operator()(int i, int j) { return i / j; }};

auto binops = std::map<std::string, std::function<int(int, int)>> {
        {"+", add},                         // function pointer
        {"-", std::minus<int>()},       //library functor
        {"/", Div()},                   // user-defined functor
        {"*", [](int i, int j) { return i * j; }},   //unnamed lambda
        {"%", mod}                          // named lambda
};

int main() {
    while (std::cout << "Please enter as: num operator num: \n", true) {
        int lhs, rhs;
        std::string op;
        std::cin >> lhs >> op >> rhs;
        std::cout << binops[op](lhs, rhs) << std::endl;
    }
    return 0;
}
```

