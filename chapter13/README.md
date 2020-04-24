# 目录

| [13.1](#131)   | [13.2](#132)   | [13.3](#133)   | [13.4](#134)   | [13.5](#135)   | [13.6](#136)   |
| -------------- | -------------- | -------------- | -------------- | -------------- | -------------- |
| [13.7](#137)   | [13.8](#138)   | [13.9](#139)   | [13.10](#1310) | [13.11](#1311) | [13.12](#1312) |
| [13.13](#1313) | [13.14](#1314) | [13.15](#1315) | [13.16](#1316) | [13.17](#1317) | [13.18](#1318) |
| [13.19](#1319) | [13.20](#1320) | [13.21](#1321) | [13.22](#1322) | [13.23](#1323) | [13.24](#1324) |
| [13.25](#1325) | [13.26](#1326) | [13.27](#1327) | [13.28](#1328) | [13.29](#1329) | [13.30](#1330) |
| [13.31](#1331) | [13.32](#1332) | [13.33](#1333) | [13.34](#1334) | [13.35](#1335) | [13.36](#1336) |
| [13.37](#1337) | [13.38](#1338) | [13.39](#1339) | [13.40](#1340) | [13.41](#1341) | [13.42](#1342) |
| [13.43](#1343) | [13.44](#1344) | [13.45](#1345) | [13.46](#1346) | [13.47](#1347) | [13.48](#1348) |
| [13.49](#1349) | [13.50](#1350) | [13.51](#1351) | [13.52](#1352) | [13.53](#1353) | [13.54](#1354) |
| [13.55](#1355) | [13.56](#1356) | [13.57](#1357) | [13.58](#1358) |                |                |

## 13.1

> 拷贝构造函数是什么？什么时候使用它？

如果一个构造函数的第一个参数是自身类型的引用，且任何其他额外参数都有默认值，则此构造函数是拷贝构造函数。

拷贝构造函数通常在发生拷贝构造的时候使用，而拷贝构造发生的条件如下：

1. 使用“=”定义变量时
2. 将一个对象作为实参传递一个非引用类型的形参
3. 从一个返回类型为非引用类型的函数返回一个对象
4. 用花括号列表初始化一个数组中的元素或者一个聚合类中的成员

## 13.2

> 解释为什么下面的声明时非法的：
>
> ```c++
> Sales_data::Sales_data(Sales_data rhs);
> ```

拷贝构造函数的第一个参数必须是自身类型的引用。否则参数传递时需要调用拷贝构造函数将发生无限次循环调用。

## 13.3

> 当我们拷贝一个`StrBlob`时，会发生什么？拷贝一个`StrBlobPtr`呢？

```c++
void test()
{
    StrBlob sb1;
    cout << "reference count of sb1 is " << sb1.count() << endl;	// 1
    StrBlob sb2(sb1);
    cout << "reference count of sb1 is " << sb1.count() << endl;	// 2

    StrBlobPtr sbp1(sb1);
    cout << "reference count of sbp1 is " << sbp1.count() << endl;		// 2
    StrBlobPtr sbp2 (sbp1);
    cout << "reference count of sbp1 is " << sbp1.count() << endl;		// 2
}
```

拷贝`StrBlob`时，其`shared_ptr`成员的引用计数会增加。拷贝`StrBlobPtr`, 引用计数不变，`StrBlobPtr`用的是`weak_ptr`绑定`StrBlob`的`shared_ptr`不会增加引用计数。

## 13.4

> 假定Point是一个类型，它有一个public的拷贝构造函数，指出下面程序片段中哪些地方使用了拷贝构造函数。
>
> ```c++
> Point global;
> Point foo_bar(Point arg)	// 传参时使用了拷贝构造函数1
> {
>     Point local = arg, *heap = new Point(global);	// 使用了拷贝构造函数2，3
>     *heap = local;
>     Point pa[4] = {local, *heap};	// 使用了拷贝构造函数4,5
>     return *heap;	// 返回值时使用了拷贝构造函数6
> }
> ```



## 13.5

> 给定下面的类框架，编写一个拷贝构造函数，拷贝所有成员。你的拷贝构造函数应该动态分配一个新的string，并将对象拷贝到ps指向的位置，而不是拷贝ps本身：
>
> ```c++
> class HasPtr
> {
> public:
>    HasPtr(const std::string& s = std::string()) :
>     	ps(new std::string(s)), i(0) {}
>     	// 拷贝构造函数
>     	HasPtr(const HasPtr& hp) : ps(new std::string(*hp.ps)), i(hp.i) {}
> private:
>     	std::string *ps;
>     	int i;
> };
> ```

## 13.6

> 拷贝赋值运算符是什么？什么时候使用它？合成拷贝赋值运算符完成什么工作？什么时候会生成合成拷贝赋值运算符？

拷贝赋值运算符是重载“=”运算符，即为一个名为operator=的函数，其参数与其所在类的类型相同，返回一个指向其左侧运算对象的引用。

在发生赋值操作时使用。

合成拷贝赋值运算符的工作：将后侧运算对象的每歌非static成员赋予左边运算对象的对应成员。】

当类未定义自己的拷贝赋值运算符时，编译器会自动生成一个合成拷贝赋值运算符。

## 13.7

> 当我们将一个StrBlob赋值给另一个StrBlob时，会发生什么？赋值StrBlobPtr呢？

```c++
void test()
{
    StrBlob sb1;
    cout << "reference count of sb1 is " << sb1.count() << endl;	// 1
    StrBlob sb2 = sb1;
    cout << "reference count of sb1 is " << sb1.count() << endl;	// 2

    StrBlobPtr sbp1(sb1);
    cout << "reference count of sbp1 is " << sbp1.count() << endl;	// 2
    StrBlobPtr sbp2 = sbp1;
    cout << "reference count of sbp1 is " << sbp1.count() << endl;	// 2
}
// 会发生浅拷贝，所有的指针都指向同一块内存。与拷贝一样，赋值StrBlob时，shared_ptr的引用计数加1，赋值StrBlobPtr时，引用计数不变。
```

## 13.8

>为13.1.1节练习13.5中的HasPtr类编写赋值运算符。类似拷贝构造函数，你的赋值运算符应该讲对象拷贝到ps指向的位置。

```c++
HasPtr& operator=(const HasPtr& hp)
{
    ps = new std::string(*hp.ps);
    i = hp.i;
    return *this;
}
```

## 13.9

> 析构函数是什么？合成析构函数完成什么工作？什么时候回生成合成析构函数？

析构函数是类的一个成员，名字由波浪线接类名组成，没有返回值也没有参数。

对于某些类，合成析构函数被用来阻止该类型的自动销毁。如果不是这种情况，合成析构函数的函数体就为空。

当一个类没有定义自己的析构函数时，编译器会为它生成一个合成析构函数。

## 13.10

> 当一个StrBlob对象销毁时会发生什么？一个StrBlobPtr对象销毁时呢？

销毁StrBlob时，分别会执行vector、shared_ptr、string的析构函数，vector析构函数会销毁我们添加到vector中的元素，shared_ptr析构函数会递减StrBlob对象的引用计数。销毁一个StrBlobPtr时，string、weak_ptr的析构函数执行，但是不会更改weak_ptr绑定的shared_ptr的引用计数，所以指向的对象不一定被销毁。

## 13.11

> 为前面练习中的HasPtr类添加一个析构函数。

```c++
~HasPtr()
{
    delete ps;
}
```

## 13.12

>在下面的代码片段中会发生几次析构函数调用？
>
>```c++
>bool fun(const Sales_data *trans, Sales_data accum)
>{
>    Sales_data item1(*trans), item2(accum);
>    return item1.isbn() != item2.isbn();
>}
>```

会发生三次析构函数调用，item1和item2分别调用一次析构函数，形参accum也会调用一次析构函数，通过代码验证过。

## 13.13

> 理解拷贝控制成员和构造函数的一个好方法是定义一个简单的类，为该类定义这些成员，每个成员都打印出自己的名字：
>

> ```c++
> struct X {
>     X() { std::cout << "X()" << std::endl; }
>     X(const X& x) { std::cout << "X(const X&)" << std::endl; }
> };
> ```
>

> 给X添加拷贝赋值运算符和析构函数，并编写一个程序以不同的方式使用X的对象：将它们作为非引用和引用参数传递；动态分配它们；将它们存放于容器中；诸如此类。观察程序的输出，知道你确认理解了什么时候会使用拷贝控制成员，以及为什么会使用它们。当你观察程序时，记住编译器可以略过对拷贝构造函数的调用。
>

```c++
#include <iostream>
#include <vector>

struct X
{
    X() {std::cout << "X()" << std::endl;}
    X(const X& x) {std::cout << "X(const X&)" << std::endl;}
    X& operator=(const X& x);
    ~X() {std::cout << "~X()" << std::endl;}
};

X& X::operator=(const X& x) {
    std::cout << "operator=(const X&)" << std::endl;
    return *this;
}

void f(X& x1, X* x2)
{
    std::vector<X> xvec;
    xvec.push_back(x1);     // 调用拷贝构造函数，将x1拷贝到vector中
    /*
     * 解引用指针x2生成一个X匿名对象，此时要调用拷贝构造函数，然后将x2的值拷贝到xvec中,
     * 再次调用拷贝构造函数，拷贝结束后临时的匿名对象销毁调用析构函数。
     */
    xvec.push_back(*x2);
    // 销毁xvec，调用容器里面的两个元素的析构函数
    std::cout << "--------destructor in f---------" << std::endl;
}

void dynamicAllowcate()
{
    std::cout << "-------constructor--------" << std::endl;
    X x1;   // 默认构造函数
    X* x2 = new X();    // 默认构造函数构造匿名对象并用指针x2指向它
    X x3;   // 默认构造函数
    x3 = x1;    // 拷贝赋值运算符
    std::cout << "--------copy constructor--------" << std::endl;
    f(x1, x2);
    std::cout << "------destructor 1--------" << std::endl;
    delete x2;  // 销毁x2，x2指向的对象调用析构函数被销毁
    std::cout << "------destructor 2--------" << std::endl; // x1和x3调用析构函数
}

int main()
{
    dynamicAllowcate();
    return 0;
}
```

运行结果：

```c++
-------constructor--------
X()
X()
X()
operator=(const X&)
--------copy constructor--------
X(const X&)
X(const X&)
X(const X&)
~X()
--------destructor in f---------
~X()
~X()
------destructor 1--------
~X()
------destructor 2--------
~X()
~X()
```

## 13.14

> 假定numbered是一个类，它有一个默认构造函数，能为每个对象生成一个唯一的序号，保存在名为mysn的数据成员中。假定numbered使用合成的拷贝控制成员，并给定如下函数：
>
> ```c++
> void f(numbered s) { cout << s.mysn << endl; }
> ```
>
> 则下面代码输出什么内容？
>
> numbered a, b = a, c = b;
>
> f(a); f(b); f(c);

```c++
#include <iostream>
#include <cstdlib>

struct numbered
{
    int mysn;
    numbered() : mysn(std::rand()) {}
};

void f(numbered s)
{
    std::cout << s.mysn << std::endl;
}

int main()
{
    numbered a, b = a, c = b;
    f(a);
    f(b);
    f(c);
    return 0;
}
```

合成拷贝构造函数直接拷贝对应的成员的值，所以a,b,c的序号相同，运行结果如下：

```c++
41
41
41
```

## 13.15

> 假定numbered定义了一个拷贝构造函数，能生成一个新的序号。这会改变上一题中调用的输出结果吗？如果会改变，为什么？新的输出结果是什么？

```c++
#include <iostream>
#include <cstdlib>

struct numbered
{
    int mysn;
    numbered() : mysn(std::rand()) {}
    numbered(const numbered& n) { mysn = std::rand(); }
};

void f(numbered s)
{
    std::cout << s.mysn << std::endl;
}

int main()
{
    numbered a, b = a, c = b;
    f(a);
    f(b);
    f(c);
    return 0;
}
```

定义了新的拷贝构造函数能生成一个新的序号，所以在调用拷贝构造函数时每个新的对象会有独特的序号，所以函数调用时打印出的序号不同。运行结果如下：

```c++
26500
19169
15724
```

## 13.16

> 如果f中的参数时const numbered&，将会怎样？这会改变输出结果吗？如果会改变，为什么？新的输出结果是什么？

```c++
#include <iostream>
#include <cstdlib>

struct numbered
{
    int mysn;
    numbered() : mysn(std::rand()) {}
    numbered(const numbered& n) { mysn = std::rand(); }
};

void f(const numbered& s)
{
    std::cout << s.mysn << std::endl;
}

int main()
{
    numbered a, b = a, c = b;
    f(a);
    f(b);
    f(c);
    return 0;
}
```

如果f的参数是const numbered&，那么调用函数f时不会调用拷贝构造函数，所以会改变输出结果。在上一题中f函数的参数不是引用类型，所以再进行参数传递时会发生参数的拷贝，会调用拷贝构造函数，与是引用类型的参数结果不一样。运行结果是：

```c++
41
18467
6334
```



## 13.17

见[13.14](#1314)、[13.15](#1315)、[13.16](#1316)的答案。

## 13.18

> 定义一个Employee类，它包含雇员的姓名和唯一的雇员证号。为这个类定义默认构造函数，以及接受一个表示雇员姓名的string的构造函数。每个构造函数应该通过递增一个static数据成员来生成一个唯一的证号。

```c++
#include <iostream>
#include <string>

struct Employee
{
    std::string name;
    unsigned int id;
    static unsigned basicNumber;
    Employee() : name(std::string("null")), id(basicNumber++) {}
    Employee(std::string name) : name(name) { id = basicNumber++; }
};
unsigned Employee::basicNumber = 123456;

int main()
{
    Employee e1;
    Employee e2("Mike");
    Employee e3(e2);
    Employee e4;
    e4 = e2;
    std::cout << e1.name << '\t' << e1.id << std::endl;
    std::cout << e2.name << '\t' << e2.id << std::endl;
    std::cout << e3.name << '\t' << e3.id << std::endl;
    std::cout << e4.name << '\t' << e4.id << std::endl;

    return 0;
}
```

运行结果：

```c++
null    123456
Mike    123457
Mike    123457
Mike    123457
```

## 13.19

Employee类需要定义自己的拷贝控制成员，因为合成的拷贝构造函数和拷贝赋值运算符会直接将雇员证号拷贝过来，不能区分员工。所以应该自定义拷贝构造函数和拷贝赋值运算符。

```c++
#include <iostream>
#include <string>

struct Employee
{
    std::string name;
    unsigned int id;
    static unsigned basicNumber;
    Employee() : name(std::string("null")), id(basicNumber++) {}
    Employee(std::string name) : name(name) { id = basicNumber++; }
    Employee(const Employee& e) : name(e.name), id(basicNumber++) {}
    Employee& operator=(const Employee& e);
};
unsigned Employee::basicNumber = 123456;

Employee& Employee::operator=(const Employee& e)
{
    this->name = e.name;
    this->id = basicNumber++;
    return *this;
}

int main()
{
    Employee e1;
    Employee e2("Mike");
    Employee e3(e2);
    Employee e4;
    e4 = e2;
    std::cout << e1.name << '\t' << e1.id << std::endl;
    std::cout << e2.name << '\t' << e2.id << std::endl;
    std::cout << e3.name << '\t' << e3.id << std::endl;
    std::cout << e4.name << '\t' << e4.id << std::endl;

    return 0;
}
```

运行结果如下：

```c++
null    123456
Mike    123457
Mike    123458
Mike    123460
```

## 13.20

> 解释当我们拷贝、赋值或销毁TextQuery和QueryResult类对象时会发生什么？

拷贝时成员被复制，赋值时成员也相应被复制，销毁时对象的成员也被销毁。

## 13.21

> 你认为TextQuery和QueryResult类需要定义它们自己版本的拷贝控制成员吗？如果需要，为什么？如果不需要，为什么？实现你认为这两个类需要的拷贝控制操作。

不需要定义它们自己版本的拷贝控制成员，因为默认的合成拷贝控制成员足够完成满足所有的需求。

## 13.22

> 假定我们希望HasPtr的行为像一个值。即，对于对象所指向的string成员，每个对象都有一份自己的拷贝。我们将在下一节介绍拷贝控制成员的定义。但是，你已经学习了定义这些成员所需要的所有知识。在继续学习下一节之前，为HasPtr编写拷贝构造函数和拷贝赋值运算符。

```c++
//
// Created by wangheng on 2020/4/23.
//

#ifndef CPP_PRIMER_EX13_22_H
#define CPP_PRIMER_EX13_22_H

#include <string>
class HasPtr
{
public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) {}
    HasPtr(const HasPtr& hp) : ps(new std::string(*hp.ps)), i(hp.i) {}
    HasPtr& operator=(const HasPtr& hp) {
        auto newp = new std::string(*hp.ps);
        delete ps;  // ps在指向新的地址前要先销毁原来指向的内存，否则原来指向的内存将无法找到，内存泄漏
        ps = newp;
        i = hp.i;
        return *this;
    }
    ~HasPtr() {
        delete ps;
    }
private:
    std::string *ps;
    int i;
};

#endif //CPP_PRIMER_EX13_22_H

```

## 13.23

> 比较上一节联系中你编写的拷贝控制成员和这一节中的代码。确定你理解了你的代码和我们的代码之间的差异(如果有的话)。

## 13.24

> 如果本节中的`HasPtr`版本未定义析构函数，将会发生什么？如果未定义拷贝构造函数，将会发生什么？

如果没有定义析构函数，那么对象在析构时它的`ps`成员无法销毁，内存没法释放，造成内存泄漏。如果未定义拷贝构造函数，对象的副本和原来的对象的`ps`成员指向同一块内存，改变副本或者原对象任意一个的`ps`指向地址的值，都会改变另外一个对象的`ps`指向地址的值，即两者共享同一块底层数据。

## 13.25

> 假定希望定义`StrBlob`的类值版本，而且希望继续使用`shared_ptr`，这样我们的`StrBlob`类就仍能使用指向`vector`的`weak_ptr`了。你修改后的类将需要一个拷贝构造函数和一个拷贝赋值运算符，但不需要析构函数。解释拷贝构造函数和拷贝赋值运算符必须要做什么。解释为什么不需要析构函数。

拷贝构造函数和拷贝赋值运算符需要重新分配动态内存。因为`StrBlob`使用的是智能指针，当引用计数减为0时会自动销毁对象，释放内存，因此不需要析构函数。

## 13.26

> 对上一题中描述的`StrBlob`类，编写你自己的版本。

```c++
//
// Created by wangheng on 2020/4/23.
//

#ifndef CPP_PRIMER_EX13_26_H
#define CPP_PRIMER_EX13_26_H

#include <memory>
#include <vector>
#include <initializer_list>
#include <string>
#include <stdexcept>

class StrBlob
{
public:
    typedef std::vector<std::string>::size_type size_type;
    StrBlob();
    StrBlob(std::initializer_list<std::string> il);
    StrBlob(const StrBlob&);
    StrBlob& operator=(const StrBlob&);
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    // 添加和删除元素
    void push_back(const std::string &t) { data->push_back(t); }
    void pop_back();
    // 元素访问
    std::string &front();
    std::string &front() const;
    std::string &back();
    std::string &back() const;
private:
    std::shared_ptr<std::vector<std::string>> data;
    // 如果data[i]不合法，抛出异常
    void check(size_type i, const std::string &msg) const;
};

StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()) {}

StrBlob::StrBlob(std::initializer_list<std::string> il) :
        data(std::make_shared<std::vector<std::string>>(il)) {}

void StrBlob::check(size_type i, const std::string &msg) const {
    if (i >= data->size()) {
        throw std::out_of_range(msg);
    }
}

void StrBlob::pop_back() {
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

std::string& StrBlob::front() {
    check(0, "front on empty StrBlob");
    return data->front();
}

std::string& StrBlob::front() const {
    check(0, "front on empty StrBlob");
    return data->front();
}

std::string &StrBlob::back() {
    check(0, "back on empty StrBlob");
    return data->back();
}

std::string &StrBlob::back() const {
    check(0, "back on empty StrBlob");
    return data->back();
}

StrBlob::StrBlob(const StrBlob &rhs) :
    data(std::make_shared<std::vector<std::string>>(*rhs.data)) {}

StrBlob& StrBlob::operator=(const StrBlob &rhs) {
    data.reset(new std::vector<std::string>(*rhs.data));
    return *this;
}
#endif //CPP_PRIMER_EX13_26_H

```



## 13.27

## 13.28

## 13.29

## 13.30

## 13.31

## 13.32

## 13.33

## 13.34

## 13.35

## 13.36

## 13.37

## 13.38

## 13.39

## 13.40

## 13.41

## 13.42

## 13.43

## 13.44

## 13.45

## 13.46

## 13.47

## 13.48

## 13.49

## 13.50

## 13.51

## 13.52

## 13.53

## 13.54

## 13.55

## 13.56

## 13.57

## 13.58

