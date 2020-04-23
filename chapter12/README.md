# 目录

| [12.01](#1201) | [12.02](#1202) | [12.03](#1203) | [12.04](#1204) | [12.05](#1205) | [12.06](#1206) |
| -------------- | -------------- | -------------- | -------------- | -------------- | -------------- |
| [12.07](#1207) | [12.08](#1208) | [12.09](#1209) | [12.10](#1210) | [12.11](#1211) | [12.12](#1212) |
| [12.13](#1213) | [12.14](#1214) | [12.15](#1215) | [12.16](#1216) | [12.17](#1217) | [12.18](#1218) |
| [12.19](#1219) | [12.20](#1220) | [12.21](#1221) | [12.22](#1222) | [12.23](#1223) | [12.24](#1224) |
| [12.25](#1225) | [12.26](#1226) | [12.27](#1228) | [12.28](#1228) | [12.29](#1229) | [12.30](#1230) |
| [12.31](#1231) | [12.32](#1232) | [12.33](#1233) |                |                |                |

## <span id="12.01">12.01</span>

> 在此代码的结尾，`b1`和`b2`各包含多少个元素？
>
> ```c++
> Strblob b1;
> {
>     StrBlob b2 = {"a", "an", "the"};
>     b1 = b2;
>     b2.push_back("about");
> }
> ```

在代码的结尾`b2`被销毁，`b1`有四个元素。

`StrBlob`类的声明和实现：

`StrBlob.h`

```c++
//
// Created by wangheng on 2020/4/23.
//

#ifndef CPP_PRIMER_EX12_01_H
#define CPP_PRIMER_EX12_01_H

#include <memory>
#include <vector>
#include <initializer_list>
#include <string>

class StrBlob
{
public:
    typedef std::vector<std::string>::size_type size_type;
    StrBlob();
    StrBlob(std::initializer_list<std::string> il);
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

#endif //CPP_PRIMER_EX12_01_H

```

`StrBlob.cpp`

```c++
//
// Created by wangheng on 2020/4/23.
//

#include "ex12_01.h"
#include <stdexcept>

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
```



## <span id="12.02">12.02</span>

> 编写你自己的`StrBlob`类，包含`const`版本的`front`和`back`。

见上一题

## <span id="12.03">12.03</span>

> `StrBlob`需要`const`版本的`push_back`和`pop_back`吗？如果需要，添加进去，否则，解释为什么不需要。

不需要，`const`成员函数只能是`const`对象调用，但是`const`对象不允许更改，所以不需要`push_back`和`pop_back`。

## <span id="12.04">12.04</span>

> 在我们的check函数中，没有检查i是否大于0。为什么可以忽略这个检查？

因为`check`是私有成员函数，只能被`StrBlob`的成员函数调用，不能被用户程序调用，我们可以很容易地保证传给`i`的值符合要求，不必进行检查。

## <span id="12.05">12.05</span>

> 我们未编写接受一个`initializer_list explicit`参数的构造函数。讨论这个设计策略的优点和缺点。

未编写接受一个`initializer_list`参数的显示构造函数，意味着可以进行列表项`StrBlob`的隐式转换。在需要`StrBlob`的地方可以用列表代替，使程序编写更加方便，但是列表中可能并非都是合法的值。

## <span id="12.06">12.06</span>

>  编写函数，返回一个动态分配的`int`的`vector`。将此`vector`传递给另一个函数，这个函数读取标准输入，将输入的值保存在`vector`元素中。再将`vector`传递给另一个函数，打印读入的值。记得在恰当的时刻`delete vector`。

```c++
//
// Created by wangheng on 2020/4/23.
//

#include <iostream>
#include <vector>

// 动态分配一个int的vector
std::vector<int>* construct_p(void) {
    return new std::vector<int>();
}

// 读入数据存入vector中
void read(std::vector<int>*& p) {
    int number;
    while (std::cin >> number) {
        p->push_back(number);
    }
}

// 打印vector中的值
void write(std::vector<int>*& p) {
    for (auto& iter : *p)
        std::cout << iter << '\t';
}

int main()
{
    std::vector<int>* p = construct_p();
    read(p);
    write(p);
    delete p;
    return 0;
}
```



## <span id="12.07">12.07</span>

> 重做上一题，这次试用`shared_ptr`而不是内置指针。

```c++
//
// Created by wangheng on 2020/4/23.
//

#include <iostream>
#include <memory>
#include <vector>

std::shared_ptr<std::vector<int>> construct_p(void) {
    return std::make_shared<std::vector<int>>();
}

void read(std::shared_ptr<std::vector<int>>& p) {
    int number;
    while (std::cin >> number) {
        p->push_back(number);
    }
}

void write(std::shared_ptr<std::vector<int>>& p) {
    for (auto& iter : *p)
        std::cout << iter << '\t';
}

int main()
{
    std::shared_ptr<std::vector<int>> sp = construct_p();
    read(sp);
    write(sp);
    return 0;
}
```



## <span id="12.08">12.08</span>

> 下面的函数是否有错误？如果有，解释错误原因。
>
> ```c++
> bool b() {
>     int* p = new int;
>     // ...
>     return p;
> }
> ```

依赖于内存分配成功与否返回`true`或`false`，但是用`new`分配动态内存失败会抛出异常，而不是返回空指针。应该使用`int* p = new(nothrow) int;`

## <span id="12.09">12.09</span>

> 解释下面代码执行的结果：
>
> ```c++
> int *q = new int(42), *r = new int(100);
> r = q;	// r原来管理的内存再无指针管理，造成内存泄漏。
> auto q2 = make_shared<int>(42), r2 = make_shared<int>(100);
> r2 = q2;	// 定义q2和r2时，二者的引用计数均为1，将q2赋值给r2，q2的引用计数加1变为2，r2的引用计数减1，r2指向的内存自动释放。
> 
> // 显然，使用智能指针管理动态内存可以不用手动释放内存，用内置指针管理动态内存极容易造成内存泄漏和空悬指针。
> ```

## <span id="12.10">12.10</span>

> 下面的代码调用了第413页中定义的`process`函数，解释此调用是否正确。如果不正确，应如何修改。
>
> ```c++
> shared_pre<int> p(new int(42));
> process(shared_ptr<int>(p));
> ```

正确。利用`p`创建一个临时的`shared_ptr`赋予`process`的参数`ptr`，`p`和`ptr`都指向相同的`int`对象，引用计数被置位2，`process`的调用结束后，`ptr`被销毁，引用计数减为1，此时只有唯一的`p`指向它。

## <span id="12.11">12.11</span>

> 如果我们像下面这样调用`process`，会发生什么？
>
> ```c++
> process(shared_ptr<int>(p.get()));
> ```

`get`函数返回一个内置指针，指向智能指针管理的对象。

`p.get()`返回一个内置指针，指向p所共享的int对象。利用此指针创建一个`shared_ptr`而不是用`p`创建一个`shared_ptr`，将不会形成正确的对象共享，会构造一个独立的智能指针。编译器认为`p`和`ptr`是两个地址（虽然它们相等）创建了两个不同的`shared_ptr`，而非共享同一个动态对象。这样二者的引用计数均为1。当`process`执行后，`ptr`的引用计数减为0，所管理的内存被释放，而此内存也是`p`管理的，p成为一个管理空悬指针的`shared_ptr`。

## <span id="12.12">12.12</span>

> `p`和`sp`的定义如下，对于接下来的对`process`的每个调用，如果合法，解释它做了什么，如果不合法，解释错误原因：
>
> ```c++
> auto p = new int();
> auto sp = shared_ptr<int>();
> (a)process(sp);		// 合法
> (b)process(new int());	// 不合法，process需要shared_ptr参数，不能将int*转换为一个shared_ptr
> (c)process(p);	// 不合法，不能将int*转换为shared_ptr
> (d)process(shared_ptr<int>(p));		//合法，利用p构造了一个shared_ptr
> ```
>
> 

## <span id="12.13">12.13</span>

> 如果执行下面的代码，会发生什么？
>
> ```c++
> auto sp = make_shared_ptr<int>();
> auto p = sp.get();	// get函数返回一个内置指针，指向sp管理的对象
> delete p;	// sp和p指向同一块内存，delete p之后，sp成为空悬指针
> ```

## <span id="12.14">12.14</span>

> 编写你自己版本的用`shared_ptr`管理`connection`的函数。

```c++
//
// Created by wangheng on 2020/4/23.
//

#include <iostream>
#include <memory>
#include <string>

struct connection
{
    std::string ip;
    int port;
    connection(std::string i, int p) : ip(i), port(p) {}
};

struct destination
{
    std::string ip;
    int port;
    destination(std::string i, int p) : ip(i), port(p) {}
};

connection connect(destination* pDest) {
    std::shared_ptr<connection> pConn(new connection(pDest->ip, pDest->port));
    std::cout << "creating connection(" << pConn.use_count() << ")" << std::endl;
    return *pConn;
}

void disconnect(connection connect) {
    std::cout << "connection close(" << connect.ip << ":" << connect.port << ")" << std::endl;
}

void end_connect(connection* pConn) {
    disconnect(*pConn);
}

void f(destination& d) {
    connection conn  = connect(&d);
    std::shared_ptr<connection> p(&conn, end_connect);
    std::cout << "connecting now(" << p.use_count() << ")" << std::endl;
}

int main() {
    destination dest("220.181.111", 10086);
    f(dest);

    return 0;
}
```



## <span id="12.15">12.15</span>

> 重写第一题中的程序，用`lambda`代替`end_connection`函数。

```c++
//
// Created by wangheng on 2020/4/23.
//

#include <iostream>
#include <memory>
#include <string>

struct connection
{
    std::string ip;
    int port;
    connection(std::string i, int p) : ip(i), port(p) {}
};

struct destination
{
    std::string ip;
    int port;
    destination(std::string i, int p) : ip(i), port(p) {}
};

connection connect(destination* pDest) {
    std::shared_ptr<connection> pConn(new connection(pDest->ip, pDest->port));
    std::cout << "creating connection(" << pConn.use_count() << ")" << std::endl;
    return *pConn;
}

void disconnect(connection connect) {
    std::cout << "connection close(" << connect.ip << ":" << connect.port << ")" << std::endl;
}

void f(destination& d) {
    connection conn  = connect(&d);
    std::shared_ptr<connection> p(&conn, [] (connection* Pconn) {disconnect(*Pconn);});
    std::cout << "connecting now(" << p.use_count() << ")" << std::endl;
}

int main() {
    destination dest("220.181.111", 10086);
    f(dest);

    return 0;
}
```



## <span id="12.16">12.16</span>

> 如果你试图拷贝或赋值`unique_ptr`，编译器并不总是能给出易于理解的错误信息。编写包含这种错误的程序，观察编译器如何诊断这种错误。

```c++
//
// Created by wangheng on 2020/4/23.
//

#include <iostream>
#include <memory>

int main() {
    std::unique_ptr<int> up(new int(3));
    auto uq = up;
    return 0;
}
```

`unique_ptr(const unique_ptr&) = delete`可以看到`unique_ptr`的拷贝构造函数是删除的，所以不能拷贝或者赋值`unique_ptr`。

## <span id="12.17">12.17</span>

> 下面的`unique_ptr`声明中，哪些是合法的，哪些可能导致后续的程序错误？解释每个错误的问题在哪里。
>
> ```c++
> int ix = 1024, *pi = &ix, *pi2 = new int(2048);
> typedef unique_ptr<int> IntP;
> (a)IntP p0(ix);		// 无法将int转换为指针
> (b)IntP p1(pi);		// 合法，但是用普通指针初始化p1，当p1毁时会释放内存，pi变成一个空悬指针
> (c)IntP p2(pi2);	// 合法，也可能使pi2变成空悬指针
> (d)IntP p3(&ix);	// 不合法，当p3被销毁时，它试图释放一个栈空间的对象。
> (e)Intp p4(new int(2048));	// 合法
> (f)IntP p5(p2.get());	// 但是会造成两个unique_ptr指向相同的地址，其中一个销毁，另一个变成空悬指针
> ```

## <span id="12.18">12.18</span>

> `shared_ptr`为什么没有`release`成员？

`release`成员的作用是放弃控制权并返回指针，因为在某一时刻只能有一个`unique_ptr`指向某个对象，`unique_ptr`不能被赋值，所以要用`release`成员将一个`unique_ptr`指针的所有权传递给另一个`unique_ptr`。而`shared_ptr`允许有多个`shared_ptr`指向同一个对象，因此不需要`release`成员。

## <span id="12.19">12.19</span>

> 定义你自己版本的`StrBlobPtr`，更新`StrBlob`类，加入恰当的`friend`声明及`begin`和`end`成员。

```c++
//
// Created by wangheng on 2020/4/23.
//

#ifndef CPP_PRIMER_EX12_19_H
#define CPP_PRIMER_EX12_19_H

#include <vector>
#include <memory>
#include <stdexcept>
#include <string>
#include <initializer_list>

class StrBlobPtr;

class StrBlob {
public:
    friend class StrBlobPtr;
    typedef std::vector<std::string>::size_type size_type;
    StrBlob();
    StrBlob(std::initializer_list<std::string> il);
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
    StrBlobPtr begin();
    StrBlobPtr end();
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

class StrBlobPtr {
public:
    using size_t = std::vector<std::string>::size_type;
    StrBlobPtr() : curr(0) {}
    // 使用StrBlob的引用避免拷贝
    StrBlobPtr(StrBlob& a, size_t sz = 0) : wptr(a.data), curr(sz) {}
    std::string &dref() const ;
    StrBlobPtr& incr();     // 递增前缀
private:
    // 若检查成功，check返回一个指向vector的shared_ptr
    std::shared_ptr<std::vector<std::string>>
        check(std::size_t, const std::string&) const;
    // 保存一个waek_ptr，意味着底层vector可能被销毁
    std::weak_ptr<std::vector<std::string>> wptr;
    size_t curr;   // 在数组中当前的位置
};

std::string& StrBlobPtr::dref() const {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

StrBlobPtr& StrBlobPtr::incr() {
    // 如果curr已经指向容器的尾后位置，就不能递增它
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

std::shared_ptr<std::vector<std::string>>
StrBlobPtr::check(std::size_t i, const std::string &msg) const {
    auto ret = wptr.lock();
    if (!ret)
        throw std::runtime_error("unbound StrBlobPtr");
    if (i >= ret->size())
        throw std::out_of_range(msg);
    return ret;
}

StrBlobPtr StrBlob::begin() {
    return StrBlobPtr(*this);
}

StrBlobPtr StrBlob::end() {
    auto ret = StrBlobPtr(*this, data->size());
    return ret;
}

#endif //CPP_PRIMER_EX12_19_H
```



## <span id="12.20">12.20</span>

> 编写程序，逐行读入一个输入文件，将内容存入一个`StrBlob`中，用一个`StrBlobPtr`打印出`StrBlob`中的每个元素。

```c++
//
// Created by wangheng on 2020/4/23.
//

#include "ex12_19.h"
#include <iostream>

int main() {
    StrBlob blob;
    std::string str;
    while (std::cin >> str) {
        if (str == "q")
            break;
        blob.push_back(str);
    }
    for (StrBlobPtr sp = blob.begin(); sp != blob.end(); sp.incr()) {
        std::cout << sp.dref() << std::endl;
    }

    return 0;
}
```

## <span id="12.21">12.21</span>

> 也可以这样编写`StrBlobPtr`的`deref`成员。
>
> ```c++
> std::string& deref() const
> {
>     return (*check(curr, "dereference past end"))[curr];
> }
> ```
>
> 你认为那个版本好？为什么？

原来的版本好，因为原来的版本虽然代码行数多，但是更加易懂。

## <span id="12.22">12.22</span>

> 为了能让`StrBlobPtr`使用`const StrBlobPtr`，你觉得应该如何修改？定义一个名为`ConsStrBlobPtr`的类，使其能够指向`consr StrBlob`。

给`ConstStrBlobPtr`类添加一个接受`const StrBlob`的构造函数，然后添加`const`版本的`cbegin`和`cend`函数即可。

`ConstStrBlobPtr.h`

```c++
//
// Created by wangheng on 2020/4/23.
//

#ifndef CPP_PRIMER_EX12_22_H
#define CPP_PRIMER_EX12_22_H

#include <vector>
#include <memory>
#include <stdexcept>
#include <string>
#include <initializer_list>

class ConstStrBlobPtr;

class StrBlob {
public:
    friend class ConstStrBlobPtr;
    typedef std::vector<std::string>::size_type size_type;
    StrBlob();
    StrBlob(std::initializer_list<std::string> il);
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
    ConstStrBlobPtr begin();
    ConstStrBlobPtr end();
    ConstStrBlobPtr cbegin() const ;
    ConstStrBlobPtr cend() const ;
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

class ConstStrBlobPtr {
public:
    using size_t = std::vector<std::string>::size_type;
    ConstStrBlobPtr() : curr(0) {}
    // 使用StrBlob的引用避免拷贝
    ConstStrBlobPtr(StrBlob& a, size_t sz = 0) : wptr(a.data), curr(sz) {}
    ConstStrBlobPtr(const StrBlob& a, size_t sz = 0) : wptr(a.data), curr(sz) {}
    bool operator!=(const ConstStrBlobPtr& p) { return p.curr != curr; }
    std::string &dref() const ;
    ConstStrBlobPtr& incr();     // 递增前缀
private:
    // 若检查成功，check返回一个指向vector的shared_ptr
    std::shared_ptr<std::vector<std::string>>
    check(std::size_t, const std::string&) const;
    // 保存一个waek_ptr，意味着底层vector可能被销毁
    std::weak_ptr<std::vector<std::string>> wptr;
    size_t curr;   // 在数组中当前的位置
};

std::string& ConstStrBlobPtr::dref() const {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

ConstStrBlobPtr& ConstStrBlobPtr::incr() {
    // 如果curr已经指向容器的尾后位置，就不能递增它
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

std::shared_ptr<std::vector<std::string>>
ConstStrBlobPtr::check(std::size_t i, const std::string &msg) const {
    auto ret = wptr.lock();
    if (!ret)
        throw std::runtime_error("unbound StrBlobPtr");
    if (i >= ret->size())
        throw std::out_of_range(msg);
    return ret;
}

ConstStrBlobPtr StrBlob::begin() {
    return ConstStrBlobPtr(*this);
}

ConstStrBlobPtr StrBlob::end() {
    auto ret = ConstStrBlobPtr(*this, data->size());
    return ret;
}

ConstStrBlobPtr StrBlob::cbegin() const {
    return ConstStrBlobPtr(*this);
}

ConstStrBlobPtr StrBlob::cend() const {
    auto ret = ConstStrBlobPtr(*this, data->size());
    return ret;
}

#endif //CPP_PRIMER_EX12_22_H

```

`ex12_22.cpp`

```c++
//
// Created by wangheng on 2020/4/23.
//

#include <iostream>
#include "ex12_22.h"

int main() {
    const StrBlob blob = {"the", "hello"};
    ConstStrBlobPtr blobptr(blob);
    for (auto iter = blob.cbegin(); iter != blob.cend(); iter.incr())
        std::cout << iter.dref() << std::endl;

    return 0;
}
```



## <span id="12.23">12.23</span>

> 编写一个程序，连接两个字符串常量，将结果保存在一个动态分配的`char`数组中。重写这个程序，连接两个标准库`string`对象。

连接两个字符串常量。

```c++

```

连接两个`string`对象。

```c++

```



## <span id="12.24">12.24</span>

> 编写一个程序，从标准输入读入一个字符串，存入一个动态分配的字符串数组中。描述你的程序如何处理变长输入。测试你的程序，输入一个超出你分配的数组长度的字符串。

```c++

```



## <span id="12.25">12.25</span>

> 给定下面的`new`表达式，你应该如何释放`pa`？
>
> `int *pa = new int[10];`

`delete [] pa;`

## <span id="12.26">12.26</span>

> 用`allocator`重写第427页中的程序。

```c++
//
// Created by wangheng on 2020/4/23.
//

#include <iostream>
#include <memory>
#include <string>

int main() {
    std::allocator<std::string>::size_type n = 3;
    std::allocator<std::string> alloc;
    auto const p = alloc.allocate(n);
    auto q = p;
    std::string str;
    while (std::cin >> str && q != p + n) {
        alloc.construct(q++, str);
    }
    for (auto i = 0; i < n; ++i)
        std::cout << p[i] << std::endl;
    alloc.deallocate(p, n);
    return 0;
}
```



## <span id="12.27">12.27</span>

> TextQuery和QueryResult类只使用了我们已经介绍过的语言和标准库特性。不要提前看后续章节内容，只用已经学到的知识对这两个类编写你自己的版本。

## <span id="12.28">12.28</span>

> 编写程序实现文本查询，不要定义类来管理数据。你的程序应该接受一个文件，并与用户交互来查询单词。使用vector、map和set容器来保存来自文件的数据并生成查询结果。

```c++
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <sstream>

int main()
{
    std::string filename = "E:\\code\\CLionProjects\\test\\test.txt";
    std::ifstream infile(filename);
    if (!infile.is_open())
    {
        std::cout << "failed to open" << std::endl;
    }
    else {
        // 读取文件的内容，每行作为content的一个元素
        std::string line;
        std::vector<std::string> content;
        while (std::getline(infile, line)) {
            content.push_back(line);
        }

        // 构建每个单词和相应出现的行数组成的set的map表
        std::map<std::string, std::set<int>> wordMapToLine;
        for (auto begin = content.cbegin(); begin != content.cend(); ++begin)
        {
            std::istringstream lineContent(*begin);
            std::string word;
            while (lineContent >> word)
            {
                wordMapToLine[word].insert(begin-content.cbegin()+1);
            }
        }

        // 查询相应的单词并且输出所在行的内容
        std::string queryWord;
        while (true) {
            std::cout << "请输入要查询的单词，退出请输入q:";
            std::cin >> queryWord;
            if (queryWord != "q") {
                if (wordMapToLine.find(queryWord) != wordMapToLine.cend()) {
                    std::cout << queryWord << " occurs " << wordMapToLine[queryWord].size() <<
                              " times." << std::endl;
                    for (auto iter = wordMapToLine[queryWord].cbegin();
                         iter != wordMapToLine[queryWord].cend(); ++iter) {
                        std::cout << "(line " << *iter << ") " << content[*iter - 1] << std::endl;
                    }
                } else {
                    std::cout << "没有查到单词" << queryWord << std::endl;
                }
            } else {
                break;
            }
        }
    }

    return 0;
}
```

## <span id="12.29">12.29</span>

更倾向于while版本，因为do while至少要执行一次循环，while版本可以随时终止循环。

## <span id="12.30">12.30</span>

将所有类写在同一个文件里。

```c++
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <memory>

class QueryResult
{
    friend std::ostream& print(std::ostream&, const QueryResult&);

public:
    using line_no = std::vector<std::string>::size_type;
    QueryResult(std::string s,
                std::shared_ptr<std::set<line_no>> p,
                std::shared_ptr<std::vector<std::string>> f) :
                sought(s), lines(p), file(f) {}
private:
    std::string sought;
    std::shared_ptr<std::set<line_no>> lines;
    std::shared_ptr<std::vector<std::string>> file;
};
class TextQuery
{
public:
    using line_no = std::vector<std::string>::size_type;
    TextQuery(std::ifstream&);
    QueryResult query(const std::string&) const;

private:
    std::shared_ptr<std::vector<std::string>> file;
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

TextQuery::TextQuery(std::ifstream &is) : file(new std::vector<std::string>)
{
    std::string text;
    while (std::getline(is, text))
    {
        file->push_back(text);
        int n = file->size() - 1;
        std::istringstream line(text);
        std::string word;
        while (line >> word)
        {
            auto &lines = wm[word];
            if (!lines)
            {
                lines.reset(new std::set<line_no>);
            }
            lines->insert(n);
        }
    }
}

QueryResult
TextQuery::query(const std::string &sought) const {
    static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
    auto loc = wm.find(sought);
    if (loc == wm.end())
    {
        return QueryResult(sought, nodata, file);
    } else
    {
        return QueryResult(sought, loc->second, file);
    }
}

std::ostream &print(std::ostream& os, const QueryResult& qr)
{
    os << qr.sought << " occurs " << qr.lines->size() << " times." << std::endl;
    for (auto num : *qr.lines)
    {
        os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num) << std::endl;
    }
    return os;
}

int main()
{
    std::string filename = "E:\\code\\CLionProjects\\TextQuery\\test.txt";
    std::ifstream infile(filename);
    TextQuery source = TextQuery(infile);
    QueryResult result = source.query("a");
    print(std::cout, result);

    return 0;
}
```

将类和实现分开

QueryResult.h

```c++
//
// Created by wangheng on 2020/4/18.
//

#ifndef TEXTQUERY_QUERYRESULT_H
#define TEXTQUERY_QUERYRESULT_H
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <memory>

class QueryResult {
    friend std::ostream& print(std::ostream&, const QueryResult&);

public:
    using line_no = std::vector<std::string>::size_type;
    QueryResult(std::string s,
            std::shared_ptr<std::set<line_no>> p,
            std::shared_ptr<std::vector<std::string>> f) :
            sought(s), lines(p), file(f) {}
private:
    std::string sought;
    std::shared_ptr<std::set<line_no>> lines;
    std::shared_ptr<std::vector<std::string>> file;
};


#endif //TEXTQUERY_QUERYRESULT_H

```

QueryResult.cpp

```c++
//
// Created by wangheng on 2020/4/18.
//

#include "QueryResult.h"
#include "make_plural.h"

std::ostream& print(std::ostream& os, const QueryResult& qr)
{
    os << qr.sought << " occurs " << qr.lines->size() << " " <<
        make_plural(qr.lines->size(), "time", "s") << std::endl;
    for (auto num : *qr.lines)
    {
        os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num) << std::endl;
    }
    return os;
}
```

TextQuery.h

```c++
//
// Created by wangheng on 2020/4/18.
//

#ifndef TEXTQUERY_TEXTQUERY_H
#define TEXTQUERY_TEXTQUERY_H
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include "QueryResult.h"

class TextQuery {
public:
    using line_no = std::vector<std::string>::size_type;
    TextQuery(std::ifstream&);
    QueryResult query(const std::string&) const;

private:
    std::shared_ptr<std::vector<std::string>> file;
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};


#endif //TEXTQUERY_TEXTQUERY_H

```

TextQuery.cpp

```c++
//
// Created by wangheng on 2020/4/18.
//

#include "TextQuery.h"
TextQuery::TextQuery(std::ifstream &is) : file(new std::vector<std::string>) {
    std::string text;
    while (std::getline(is, text))
    {
        file->push_back(text);
        int n = file->size() - 1;
        std::istringstream line(text);
        std::string word;
        while (line >> word)
        {
            auto& lines = wm[word];
            if (!lines)
                lines.reset(new std::set<line_no>);
            lines->insert(n);
        }
    }
}

QueryResult TextQuery::query(const std::string &sought) const {
    static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
    auto loc = wm.find(sought);
    if(loc == wm.cend())
    {
        return QueryResult(sought, nodata, file);
    } else {
        return QueryResult(sought, loc->second, file);
    }
}
```

make_plural.h

```c++
//
// Created by wangheng on 2020/4/18.
//

#ifndef TEXTQUERY_MAKE_PLURAL_H
#define TEXTQUERY_MAKE_PLURAL_H
#include <string>
inline
std::string make_plural(std::size_t ctr, const std::string& word, const std::string ending)
{
    return (ctr == 1) ? word : word+ending;
}
#endif //TEXTQUERY_MAKE_PLURAL_H

```

main.cpp

```c++
#include <iostream>
#include "QueryResult.h"
#include "TextQuery.h"

int main()
{
    std::string filename = "E:\\code\\CLionProjects\\TextQuery\\test.txt";
    std::ifstream infile(filename);
    TextQuery source = TextQuery(infile);
    std::string sought;
    while (true) {
        std::cout << "请输入你要搜索的单词，或者输入'q'退出：";
        std::cin >> sought;
        if (sought == "q")
            break;
        else {
            QueryResult result = source.query(sought);
            print(std::cout, result);
        }
    }

    return 0;
}
```

## <span id="12.31">12.31</span>

vector允许元素重复，所以如果一个单词在某行中重复出现多次会导致重复计算，而set不会重复计数。所以当需要重复记录单词在某行中出现的次数的时候可以选择vector，但是在本题中要求不能重复计数，所以应该使用set。

## <span id="12.32">12.32</span>

## <span id="12.33">12.33</span>