# 目录

| [15.01](#1501)  |  [15.02](#1502)   | [15.03](#1503hcpp) |  [15.04](#1504)   |  [15.05](#1505h)  | [15.06](#1506cpp) |
| :-------------: | :---------------: | :----------------: | :---------------: | :---------------: | :---------------: |
| [15.07](#1507h) |  [15.08](#1508)   |   [15.09](#1509)   |  [15.10](#1510)   |  [15.11](#1511)   |  [15.12](#1512)   |
| [15.13](#1513)  |  [15.14](#1514)   |   [15.15](#1515)   |  [15.16](#1516h)  |  [15.17](#1517)   |  [15.18](#1518)   |
| [15.19](#1519)  | [15.20](#1520cpp) |   [15.21](#1521)   |  [15.22](#1522)   |  [15.23](#1523)   |  [15.24](#1524)   |
| [15.25](#1525)  |  [15.26](#1526)   |  [15.27](#1527h)   | [15.28](#1528cpp) | [15.29](#1529cpp) |  [15.30](#1530)   |
| [15.31](#1531)  |  [15.32](#1532)   |   [15.33](#1533)   |  [15.34](#1534)   |  [15.35](#1535)   |  [15.36](#1536)   |
| [15.37](#1537)  |  [15.38](#1538)   |   [15.39](#1539)   |  [15.40](#1540)   |  [15.41](#1541)   |  [15.42](#1542)   |

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

## 15.09

> 在什么情况下表达式的静态类型可能与动态类型不同？请给出三个静态类型与动态类型不同的例子。

基类的指针或引用的静态类型可能与其绑定的动态类型不同。

## 15.10

> 回忆我们在8.1节进行的讨论，解释第284页中将 ifstream 传递给 Sales_data 的read 函数的程序是如何工作的。

`std::ifstream`是`std::istream`的派生类，所以`read`函数可以正常工作。

## 15.11

> 为你的 Quote 类体系添加一个名为 debug 的虚函数，令其分别显示每个类的数据成员。

[Quote.h](./ex15_03.h)

```c++
void Quote::debug() const {
    std::cout << "data member of this class\n"
                 << "bookNo = " << bookNo << " "
                 << "price = " << price << std::endl;
```

[Bulk_quote.h](./ex15_05.h)

```c++
void Bulk_quote::debug() const {
    std::cout << "data members of this class:\n"
        << "price = " << price << " "
        << "min_qty = " << min_qty << " "
        << "discount = " << discount << std::endl;
```

## 15.12

> 有必要将一个成员函数同时声明成 `override` 和 `final` 吗？为什么？

有必要。`override`的含义是此函数是对基类虚函数的重写，`final`的含义是阻止派生类重写当前虚函数，两个声明具有不同的作用。

## 15.13

> 给定下面的类，解释每个 print 函数的机理：
>
> ```c++
> class base {
> public:
> 	string name() { return basename;}
> 	virtual void print(ostream &os) { os << basename; }
> private:
> 	string basename;
> };
> class derived : public base {
> public:
> 	void print(ostream &os) { print(os); os << " " << i; }
> private:
> 	int i;
> };
> ```
>
> 在上述的代码中存在问题吗？如果有，你该如何修改它？

有问题，在派生类的`print`函数中调用`print`函数会导致递归调用，应该修改为：

`void print(ostream& os) override { base::print(os); os << " " << i; }`

## 15.14

> 给定上一题中的类以及下面这些对象，说明在运行时调用哪个函数：
>
> ```c++
> base bobj; 			base *bp1 = &bobj; 	base &br1 = bobj;
> derived dobj; 		base *bp2 = &dobj; 	base &br2 = dobj;
> (a) bobj.print();	(b)dobj.print();	(c)bp1->name();
> (d)bp2->name();		(e)br1.print();		(f)br2.print();
> ```

* (a) 编译时确定调用版本，调用基类的`print`函数。
* (b) 编译时确定调用版本，调用派生类的`print`函数。
* (c) 编译时确定调用基类的`name`函数。
* (d) 编译时确定调用基类的`name`函数。
* (e) 运行时确定调用基类的`print`函数。
* (f) 运行时确定调用派生类的`print`函数。

## 15.15

> 定义你自己的 Disc_quote 和 Bulk_quote。

[Disc_quote](./Disc_quote.h)

```c++
//
// Created by wangheng on 2020/5/9.
//

#ifndef CPP_PRIMER_DISC_QUOTE_H
#define CPP_PRIMER_DISC_QUOTE_H

#include "ex15_03.h"

class Disc_quote : public Quote {
public:
    Disc_quote() = default;
    Disc_quote(std::string& book, double p, std::size_t qty, double disc) :
        Quote(book, p), quantity(qty), discount(disc) {}

    double net_price(std::size_t) const override = 0;

protected:
    std::size_t quantity = 0;
    double discount = 0.0;
};

#endif //CPP_PRIMER_DISC_QUOTE_H

```

[Bulk_quote](./Bulk_quote.h)

```c++
//
// Created by wangheng on 2020/5/9.
//

#ifndef CPP_PRIMER_BULK_QUOTE_H
#define CPP_PRIMER_BULK_QUOTE_H

#include "Disc_quote.h"

class Bulk_quote : public Disc_quote {
    Bulk_quote() = default;
    Bulk_quote(std::string& book, double p, std::size_t qty, double disc) :
        Disc_quote(book, p, qty, disc) {}

    double net_price(std::size_t n) const override ;
};

double Bulk_quote::net_price(std::size_t n) const {
    if (n > quantity)
        return n * (1 - discount) * price;
    else
        return n * price;
}

#endif //CPP_PRIMER_BULK_QUOTE_H

```

## 15.16|[h](./Limit_quote.h)

> 改写你在15.2.2节练习中编写的数量受限的折扣策略，令其继承 Disc_quote。

```c++
//
// Created by wangheng on 2020/5/9.
//

#ifndef CPP_PRIMER_LIMIT_QUOTE_H
#define CPP_PRIMER_LIMIT_QUOTE_H

#include "Disc_quote.h"

class Limit_quote : public Disc_quote {
    Limit_quote() = default;
    Limit_quote(const std::string& book, double p, std::size_t qty, double disc) :
        Disc_quote(book, p, qty, disc) {}

    double net_price(std::size_t n) const override ;
};

double Limit_quote::net_price(std::size_t n) const {
    if (n <= quantity)
        return n * (1 - discount) * price;
    else
        return quantity * (1 - discount) * price + (n - quantity) * price;
}

#endif //CPP_PRIMER_LIMIT_QUOTE_H

```

## 15.17

> 尝试定义一个 Disc_quote 的对象，看看编译器给出的错误信息是什么？

```
error: cannot declare variable 'dq' to be of abstract type 'Disc_quote'
     Disc_quote dq("textbook", 10.1, 15, 0.2);
```

## 15.18

> 假设给定了第543页和第544页的类，同时已知每个对象的类型如注释所示，判断下面的哪些赋值语句是合法的。解释那些不合法的语句为什么不被允许：
>
> ```c++
> Base *p = &d1;  //d1 的类型是 Pub_Derv
> p = &d2;		//d2 的类型是 Priv_Derv
> p = &d3;		//d3 的类型是 Prot_Derv
> p = &dd1;		//dd1 的类型是 Derived_from_Public	
> p = &dd2;		//dd2 的类型是 Derived_from_Private
> p = &dd3;		//dd3 的类型是 Derived_from_Protected
> ```

* `Base *p = &d1;`合法
* `p = &d2;`不合法，因为`Priv_Derv`是私有继承自`Base`，只有公有继承时，用户代码才能使用派生类向基类的转换。
* `p = &d3;`不合法，理由如上。
* `p = &dd1;`合法
* `p = &dd2;`不合法
* `p = &dd3;`不合法

## 15.19

> 假设543页和544页的每个类都有如下形式的成员函数：
>
> ```c++
> void memfcn(Base &b) { b = *this; }
> ```
>
> 对于每个类，分别判断上面的函数是否合法。

合法：

* `Pub_Derv`
* `Prot_Derv`
* `Priv_derv`
* `Derived_from_Public`
* `Derived_from_Protected`

不合法：

* `Derived_from_Private`

## 15.20|[cpp](./ex15_20.cpp)

> 编写代码检验你对前面两题的回答是否正确。

```c++
//
// Created by wangheng on 2020/5/10.
//

#include <iostream>
#include <string>

class Base {
public:
    void pub_mem(); // public成员
protected:
    int prot_mem;   // protected成员
private:
    char priv_mem;  // private成员
};

struct Pub_Derv : public Base {
    void memfcn(Base& b) { b = *this; }
};

struct Prot_Derv : protected Base {
    void memfcn(Base& b) { b = *this; }
};

struct Priv_Derv : private Base {
    void memfcn(Base& b) { b = *this; }
};

struct Derived_from_Public : public Pub_Derv {
    void memfcn(Base& b) { b = *this; }
};

struct Derived_from_Protected: public Prot_Derv {
    void memfcn(Base& b) { b = *this; }
};

struct Derived_from_Private : public Priv_Derv {
    // Cannot cast 'const Derived_from_Private' to its private base class 'const Base'
    // 不能将派生类向其私有继承的基类转换
    // void memfcn(Base& b) { b = *this; }
};

int main()
{
    Pub_Derv d1;
    Base *p = &d1;

    Priv_Derv d2;
    //p = &d2;

    Prot_Derv d3;
    //p = &d3;

    Derived_from_Public dd1;
    p = &dd1;

    Derived_from_Private dd2;
    //p =& dd2;

    Derived_from_Protected dd3;
    //p = &dd3;


    return 0;
}
```

## 15.21

> 从下面这些一般性抽象概念中任选一个（或者选一个你自己的），将其对应的一组类型组织成一个继承体系：
>
> ```
> (a) 图形文件格式（如gif、tiff、jpeg、bmp）
> (b) 图形基元（如方格、圆、球、圆锥）
> (c) C++语言中的类型（如类、函数、成员函数）
> ```

声明定义一个`Shape`抽象基类，然后方格、圆、球、圆锥都可以继承自`Shape`。

## 15.22

> 对于你在上一题中选择的类，为其添加函数的虚函数及公有成员和受保护的成员。

## 15.23

> 假设第550页的 `D1` 类需要覆盖它继承而来的 `fcn` 函数，你应该如何对其进行修改？如果你修改之后 `fcn` 匹配了 `Base` 中的定义，则该节的那些调用语句将如何解析？

移除`int`参数。

## 15.24

> 哪种类需要虚析构函数？虚析构函数必须执行什么样的操作？

基类通常需要定义一个虚析构函数。定义了虚析构函数之后，当delete一个动态分配的对象的指针时将根据指针指向的实际的对象类型调用相应的析构函数，和虚函数的动态绑定同理。

## 15.25

> 我们为什么为 Disc_quote 定义一个默认构造函数？如果去掉该构造函数的话会对 Bulk_quote 的行为产生什么影响？

因为`Bulk_quote`继承自`Disc_quote`且其定义了一个默认构造函数，如果`Disc_quote`没有默认构造函数，那么`Bulk_quote`将无法完成默认构造。

## 15.26

> 定义 Quote 和 Bulk_quote 的拷贝控制成员，令其与合成的版本行为一致。为这些成员以及其他构造函数添加打印状态的语句，使得我们能够知道正在运行哪个程序。使用这些类编写程序，预测程序将创建和销毁哪些对象。重复实验，不断比较你的预测和实际输出结果是否相同，直到预测完全准确再结束。

[Bulk](./ex15_26.h)|[Disk_quote](./ex15_26_1.h)|[Bulk_quote](./ex15_26_2.h)|[test](./ex15_26.cpp)

## 15.27|[h](#./ex15_26_2.h)

> 重新定义你的 Bulk_quote 类，令其继承构造函数。

```c++
//
// Created by wangheng on 2020/6/5.
//

#ifndef CPP_PRIMER_EX15_27_H
#define CPP_PRIMER_EX15_27_H

#include <iostream>
#include "Disc_quote.h"

class Bulk_quote : public Disc_quote{
public:
    Bulk_quote() {
        std::cout << "default constructor" << std::endl;
    }

    using Disc_quote::Disc_quote;

    Bulk_quote(const Bulk_quote& bq) :
        Disc_quote(bq) {
        std::cout << "Bulk_quote: copy constructor" << std::endl;
    }

    Bulk_quote(Bulk_quote&& bq) : Disc_quote(std::move(bq)) {
        std::cout << "Bulk_quote: move constructor" << std::endl;
    }

    Bulk_quote& operator=(const Bulk_quote& rhs) {
        Disc_quote::operator=(rhs);
        std::cout << "Bulk_quote: copy =()" << std::endl;

        return *this;
    }

    Bulk_quote& operator=(Bulk_quote&& rhs) noexcept {
        Disc_quote::operator=(std::move(rhs));
        std::cout << "Bulk_quote: move =()" << std::endl;

        return *this;
    }

    double net_price(std::size_t n) const override {
        if (n < quantity)
            return n * price;
        else
            return n * (1 - discount) * price;
    }

    ~Bulk_quote() {
        std::cout << "destructor" << std::endl;
    }
};

#endif //CPP_PRIMER_EX15_27_H

```

## 15.28|[cpp](./ex15_28.cpp)

> 定义一个存放 Quote 对象的 vector，将 Bulk_quote 对象传入其中。计算 vector 中所有元素总的 net_price。

```c++
//
// Created by wangheng on 2020/6/6.
//

#include <iostream>
#include <vector>
#include <memory>
#include "ex15_26.h"
#include "ex15_26_1.h"
#include "ex15_26_2.h"

int main() {
    std::vector<Quote> ivec;
    ivec.push_back(Quote("123", 3.5));
    ivec.push_back(Bulk_quote("1234", 5.0, 10, 0.12));
    std::cout << ivec.back().net_price(10) << std::endl;

    return 0;
}
```

## 15.29|[cpp](./ex15_29.cpp)

> 再运行一次你的程序，这次传入 Quote 对象的 `shared_ptr` 。如果这次计算出的总额与之前的不一致，解释为什么;如果一直，也请说明原因。

使用智能指针导致了运行时多态，所以调用的是`Bulk_quote`的`net_price`函数。

```c++
//
// Created by wangheng on 2020/6/6.
//

#include <iostream>
#include <vector>
#include <memory>
#include "ex15_26.h"
#include "ex15_26_1.h"
#include "ex15_26_2.h"

int main() {
    std::vector<std::shared_ptr<Quote>> ivec;
    ivec.push_back(std::make_shared<Bulk_quote>("123", 5.0, 100, 0.12));
    std::cout << ivec.back()->net_price(110) << std::endl;

    return 0;
}
```

## 15.30

> 编写你自己的 Basket 类，用它计算上一个练习中交易记录的总价格。

```c++
//
// Created by wangheng on 2020/6/7.
//

#ifndef CPP_PRIMER_BASKET_H
#define CPP_PRIMER_BASKET_H

#include <memory>
#include <set>
#include "ex15_26.h"
#include "print_total.h"

class Basket{
public:
    void add_item(const Quote& sale) {
        items.insert(std::shared_ptr<Quote>(sale.clone()));
    }
    void add_item(Quote &&sale) {
        items.insert(std::shared_ptr<Quote>(std::move(sale).clone()));
    }

    double total_receipt(std::ostream& os) const {
        double sum = 0.0;
        for (auto iter = items.cbegin(); iter != items.cend(); iter = items.upper_bound(*iter)) {
            sum += print_total(os, **iter, items.count(*iter));
        }
        os << "Total sale: " << sum << std::endl;

        return sum;
    }

private:
    static bool compare(const std::shared_ptr<Quote> &lhs, const std::shared_ptr<Quote>& rhs) {
        return lhs->isbn() < rhs->isbn();
    }
    std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items{compare};
};

#endif //CPP_PRIMER_BASKET_H

```

```c++
//
// Created by wangheng on 2020/6/7.
//

#ifndef CPP_PRIMER_PRINT_TOTAL_H
#define CPP_PRIMER_PRINT_TOTAL_H

#include <iostream>
#include "ex15_26.h"

double print_total(std::ostream& os, const Quote &item, std::size_t n) {
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << std::endl;
    return ret;
}

#endif //CPP_PRIMER_PRINT_TOTAL_H

```

[print_total.h](./print_total.h)|[basket.h](./basket.h)|[test](./ex15_30.cpp) 

## 15.31

> 已知 `s1、s2、s3 `和 `s4` 都是 `string`，判断下面的表达式分别创建了什么样的对象：
>
> ```
> (a) Query(s1) | Query(s2) & ~Query(s3);
> (b) Query(s1) | (Query(s2) & ~Query(s3));
> (c) (Query(s1) & (Query(s2)) | (Query(s3) & Query(s4)));
> ```

- (a)按照运算符优先级，先`~Query(s3)`创建一个`NotQuery`对象，然后再和`Query(s2)`创建一个`AndQuery`对象，最后与`Query(s1)`创建一个`OrQuery`对象。即`(s1 | (s2 & ~(s3)))`
- (b) 和(a)的结果一样，`(s1 | (s2 & ~(s3)))`
- (c) 先创建两个`AndQuery`然后创建一个`OrQuery`，`((s1 & s2) | (s3 & s4))`

## 15.32

> 当一个 Query 类型的对象被拷贝、移动、赋值或销毁时，将分别发生什么？

- **拷贝**：当被拷贝时，合成的拷贝构造函数被调用。它将拷贝两个数据成员至新的对象。而在这种情况下，数据成员是一个智能指针，当拷贝时，相应的智能指针指向相同的地址，计数器增加1.
- **移动**：当移动时，合成的移动构造函数被调用。它将移动数据成员至新的对象。这时新对象的智能指针将会指向原对象的地址，而原对象的智能指针为 `nullptr`，新对象的智能指针的引用计数为 1.
- **赋值**：合成的赋值运算符被调用，结果和拷贝的相同的。
- **销毁**：合成的析构函数被调用。对象的智能指针的引用计数递减，当引用计数为 0 时，对象被销毁。

## 15.33

> 当一个 Query_base 类型的对象被拷贝、移动赋值或销毁时，将分别发生什么？

由合成的版本来控制。然而 `Query_base` 是一个抽象类，它的对象实际上是它的派生类对象。

## 15.34

> 针对图15.3构建的表达式：
>
> ```
> (a) 例举出在处理表达式的过程中执行的所有构造函数。
> (b) 例举出 cout << q 所调用的 rep。
> (c) 例举出 q.eval() 所调用的 eval。
> ```

- **a:** Query q = Query("fiery") & Query("bird") | Query("wind");

1. `Query::Query(const std::string& s)` where s == "fiery","bird" and "wind"
2. `WordQuery::WordQuery(const std::string& s)` where s == "fiery","bird" and "wind"
3. `AndQuery::AndQuery(const Query& left, const Query& right);`
4. `BinaryQuery(const Query&l, const Query& r, std::string s);`
5. `Query::Query(std::shared_ptr<Query_base> query)`
6. `OrQuery::OrQuery(const Query& left, const Query& right);`
7. `BinaryQuery(const Query&l, const Query& r, std::string s);`
8. `Query::Query(std::shared_ptr<Query_base> query)`

- **b:**

1. `query.rep()` inside the operator <<().
2. `q->rep()` inside the member function rep().
3. `OrQuery::rep()` which is inherited from `BinaryQuery`.
4. `Query::rep()` for `lhs` and `rhs`: for `rhs` which is a `WordQuery` : `WordQuery::rep()` where `query_word("wind")` is returned. For `lhs` which is an `AndQuery`.
5. `AndQuery::rep()` which is inherited from `BinaryQuery`.
6. `BinaryQuer::rep()`: for `rhs: WordQuery::rep()` where query_word("fiery") is returned. For `lhs: WordQuery::rep()` where query_word("bird" ) is returned.

- **c:**

1. `q.eval()`
2. `q->rep()`: where q is a pointer to `OrQuary`.
3. `QueryResult eval(const TextQuery& )const override`: is called but this one has not been defined yet.

## 15.35

> 实现`Query`类和`Query_base`类， 其中需要定义`rep`无需定义`eval`。

[Query](../TextQuery/Query.h)|[Query_base](../TextQuery/Query_base.h)

## 15.36

> 在构造函数和 rep 成员中添加打印语句，运行你的代码以检验你对本节第一个练习中(a)、(b)两小题的回答是否正确。

## 15.37

> 如果在派生类中含有 `shared_ptr<Query_base>` 类型的成员而非 Query 类型的成员，则你的类需要做出怎样的改变？

## 15.38

> 下面的声明合法吗？如果不合法，请解释原因;如果合法，请指出该声明的含义。
>
> ```
> BinaryQuery a = Query("fiery") & Query("bird");
> AndQuery b = Query("fiery") & Query("bird");
> OrQuery c = Query("fiery") & Query("bird");
> ```

1. 不合法。因为 `BinaryQuery` 是抽象类。
2. 不合法。& 操作返回的是一个 `Query` 对象。
3. 不合法。& 操作返回的是一个 `Query` 对象。

## 15.39

> 实现 Query 类和　Query_base 类，求图15.3中表达式的值并打印相关信息，验证你的程序是否正确。

[Query](../TextQuery/Query.cpp)|[Query_base](../TextQuery/Query_base.h)

## 15.40

> 在 `OrQuery` 的 `eval` 函数中，如果 `rhs` 成员返回的是空集将发生什么？

不会发生什么。代码如下：

```c++
std::shared_ptr<std::set<line_no>> ret_lines =
       std::make_shared<std::set<line_no>>(left.begin(), left.end());
```

如果 `rhs` 成员返回的是空集，在 set 当中不会添加什么。

## 15.41

> 重新实现你的类，这次使用指向 Query_base 的内置指针而非 `shared_ptr`。请注意，做出上述改动后你的类将不能再使用合成的拷贝控制成员。

## 15.42

> 从下面的几种改进中选择一种，设计并实现它:
>
> ```
> (a) 按句子查询并打印单词，而不再是按行打印。
> (b) 引入一个历史系统，用户可以按编号查阅之前的某个查询，并可以在其中添加内容或者将其余其他查询组合。
> (c) 允许用户对结果做出限制，比如从给定范围的行中跳出匹配的进行显示。
> ```



