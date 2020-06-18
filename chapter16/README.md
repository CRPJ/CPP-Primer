# 目录

|  [16.01](#1601)   | [16.02](#1602cpp) |  [16.03](#1603)   | [16.04](#1604cpp) | [16.05](#1605cpp) | [16.06](#1606cpp) |
| :---------------: | :---------------: | :---------------: | :---------------: | :---------------: | :---------------: |
|  [16.07](#1607)   |  [16.08](#1608)   |  [16.09](#1609)   |  [16.10](#1610)   |  [16.11](#1611)   |  [16.12](#1612)   |
|  [16.13](#1613)   |  [16.14](#1614)   |  [16.15](#1615)   |  [16.16](#16.16)  |  [16.17](#1617)   |  [16.18](#1618)   |
| [16.19](#1619cpp) | [16.20](#1620cpp) | [16.21](#1621cpp) |  [16.22](#1622)   |  [16.23](#1623)   |  [16.24](#1624)   |
|  [16.25](##1625)  |  [16.26](#1626)   |  [16.27](#1627)   |  [16.28](#1628)   |  [16.29](#1629)   |  [16.30](#1630)   |
|  [16.31](#1631)   |  [16.32](#1632)   |  [16.33](#1633)   |  [16.34](#1634)   |  [16.35](#1635)   |  [16.36](#1636)   |
|  [16.37](#1637)   |  [16.38](#1638)   |  [16.39](#1639)   |  [16.40](#1640)   |  [16.41](#1641)   |  [16.42](#1642)   |
|  [16.43](#1643)   |  [16.44](#1644)   |  [16.45](#1645)   |                   |                   |                   |
|                   |                   |                   |                   |                   |                   |
|                   |                   |                   |                   |                   |                   |
|                   |                   |                   |                   |                   |                   |
|                   |                   |                   |                   |                   |                   |

## 16.01

> 给出实例化的定义。

当编译器实例化一个模板时，它用实际的模板实参代替对应的模板参数来创建出模板的一个实例。

## 16.02|[cpp](ex16_02.cpp)

> 编写并测试你自己版本的 compare 函数。

```c++
//
// Created by wangheng on 2020/6/10.
//

#include <iostream>
#include <functional>

template<typename T>
int compare(const T& v1, const T& v2) {
    if (std::less<T>()(v1, v2)) return -1;
    if (std::less<T>()(v2, v1)) return 1;
    return 0;
}

int main() {
    std::cout << compare("hello", "world") << std::endl;

    return 0;
}
```

## 16.03

> 对两个 Sales_data 对象调用你的 compare 函数，观察编译器在实例化过程中如何处理错误。

`Sales_data`对象没有重载`<`运算符，所以使用`compare`函数时会报错，应该给其添加一个重载的`<`运算符。

## 16.04|[cpp](./ex16_04.cpp)

> 编写行为类似标准库 find 算法的模版。函数需要两个模版类型参数，一个表示函数的迭代器参数，另一个表示值的类型。使用你的函数在一个 vector 和一个list中查找给定值。

```c++
//
// Created by wangheng on 2020/6/10.
//

#include <iostream>
#include <vector>
#include <list>
#include <string>

template<typename Iterator, typename Value>
Iterator find(Iterator begin, Iterator end, const Value& v) {
    for (; begin != end; ++begin) {
        if (*begin == v) break;
    }
    return begin;
}

int main() {
    std::vector<int> nums{1,2,3,4};
    std::cout << "2 occurs at index " << find(nums.begin(), nums.end(), 2) - nums.begin() + 1 << std::endl;
    std::list<int> l{2,3,4,5};
    auto p = find(l.begin(), l.end(), 5);
    std::cout << *p << std::endl;
    return 0;
}
```

## 16.05|[cpp](./ex16_05.cpp)

> 为6.2.4节中的print函数编写模版版本，它接受一个数组的引用，能处理任意大小、任意元素类型的数组。

```c++
#include <iostream>

template<typename T>
void print(const T& arr) {
    for (auto& item : arr)
        std::cout << item << ' ';
}

int main() {
    int arr[] = {2,3,5,7,9};
    print(arr);
    return 0;
}
```

## 16.06|[cpp](./ex16_06.cpp)

> 你认为接受一个数组实参的标准库函数 begin 和 end 是如何工作的？定义你自己版本的 begin 和 end。

```c++
#include <iostream>

template<typename T, unsigned N>
const T* begin(const T (&arr)[N]) {
    return arr;
}

template<typename T, unsigned N>
const T* end(T (&arr)[N]) {
    return arr + N;
}

int main() {
    int arr[] = {1,2,3};
    for(auto iter = begin(arr); iter != end(arr); ++iter)
        std::cout << *iter << ' ';
    return 0;
}
```

## 16.07

> 编写一个 `constexpr` 模版，返回给定数组的大小。

```c++
template<typename T, typename N> constexpr
unsigned size(const T (&arr)[N])
{
	return N;
}
```

## 16.08

> 在第97页的“关键概念”中，我们注意到，C++程序员喜欢使用 != 而不喜欢 < 。解释这个习惯的原因。

因为大多数类只定义了 != 操作而没有定义 < 操作，使用 != 可以降低对要处理的类型的要求。

## 16.09

> 什么是函数模版，什么是类模版？

一个函数模版就是一个公式，可用来生成针对特定类型的函数版本，支持自动推断模板参数类型。类模版是用来生成类的蓝图的，与函数模版的不同之处是，编译器不能为类模版推断模版参数类型。如果我们已经多次看到，为了使用类模版，我们必须在模版名后的尖括号中提供额外信息。

## 16.10

> 当一个类模版被实例化时，会发生什么？

一个类模板的每个实例都形成一个独立的类。

## 16.11

> 下面 List 的定义是错误的。应如何修改它？
>
> ```c++
> template <typename elemType> class ListItem;
> template <typename elemType> class List {
> public:
> 	List<elemType>();
> 	List<elemType>(const List<elemType> &);
> 	List<elemType>& operator=(const List<elemType> &);
> 	~List();
> 	void insert(ListItem *ptr, elemType value);
> private:
> 	ListItem *front, *end;
> };
> ```

List类在类模板内应该简化模板类名的使用，但是`ListItem`类不应该省略模板参数

```c++
template<typename elemType> class ListItem;

template<typename elemType> class List{
public:
    List();
    List(const List&);
    List& operator=(const List&);
    ~List();
    void insert(ListItem<elemType>* ptr, elemType value);

private:
    ListItem<elemType> *front, *end;
};
```

## 16.12

> 编写你自己版本的 Blob 和 `BlobPtr` 模版，包含书中未定义的多个`const`成员。

[Blob](../Blob/Blob.h)|[BlobPtr](../Blob/BlobPtr.h)|[test](../Blob/main.cpp)

**Blob**

```c++
//
// Created by wangheng on 2020/6/10.
//

#ifndef BLOB_BLOB_H
#define BLOB_BLOB_H

#include <vector>
#include <initializer_list>
#include <memory>
#include <string>

template<typename > class BlobPtr;

template<typename T> class Blob{
    friend class BlobPtr<T>;
public:
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;
    // 构造函数
    Blob();
    Blob(std::initializer_list<T> il);
    // Blob中的元素数目
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    // 添加和删除元素
    void push_back(const T& t) { data->push_back(t); }
    // 移动版本
    void push_back(T&& t) { data->push_back(std::move(t)); }
    void pop_back();
    // 元素访问
    T& back();
    T& operator[](size_type i);
private:
    std::shared_ptr<std::vector<T>> data;
    // 若data[i]无效，则抛出msg
    void check(size_type i, const std::string& msg) const ;
};

template<typename T>
void Blob<T>::check(size_type i, const std::string &msg) const {
    if (i >= data->size())
        throw std::out_of_range(msg);
}

template<typename T>
T& Blob<T>::back() {
    return data->back();
}

template<typename T>
T& Blob<T>::operator[](size_type i) {
    return (*data)[i];
}

template<typename T>
void Blob<T>::pop_back() {
    data->pop_back();
}

template<typename T>
Blob<T>::Blob() : data(std::make_shared<std::vector<T>>()) {}

template<typename T>
Blob<T>::Blob(std::initializer_list<T> il) : data(std::make_shared<std::vector<T>>(il)) {}

#endif //BLOB_BLOB_H

```

**`BlobPtr`**

```c++
//
// Created by wangheng on 2020/6/10.
//

#ifndef BLOB_BLOBPTR_H
#define BLOB_BLOBPTR_H

#include <memory>
#include <vector>
#include <string>
#include "Blob.h"

template<typename T> class BlobPtr{
public:
    BlobPtr() : curr(0) {}
    explicit BlobPtr(Blob<T>& a, std::size_t sz = 0) : wptr(a.data), curr(sz) {}
    T& operator*() const {
        auto p = check(curr, "dereference past end");
        return (*p)[curr];
    }
    // 递增和递减
    BlobPtr& operator++();
    BlobPtr& operator--();

private:
    // 若检查成功，check返回一个指向vector的shared_ptr
    std::shared_ptr<std::vector<T>>
        check(std::size_t, const std::string&) const ;
    // 保存一个weak_ptr，表示底层vector可能被销毁
    std::weak_ptr<std::vector<T>> wptr;
    std::size_t curr;   // 数组中的当前位置
};

template<typename T>
BlobPtr<T>& BlobPtr<T>::operator++() {
    check(curr, "increment past end of BlobPtr");
    ++curr;
    return *this;
}

template<typename T>
BlobPtr<T>& BlobPtr<T>::operator--() {
    --curr;
    check(curr, "decrement past begin of BlobPtr");
    return *this;
}

template<typename T>
std::shared_ptr<std::vector<T>>
        BlobPtr<T>::check(std::size_t n, const std::string &msg) const {
    auto ret = wptr.lock();
    if (!ret)
        throw std::runtime_error("unbound BlobPtr");
    if (n >= ret->size())
        throw std::out_of_range(msg);
    return ret;
}

#endif //BLOB_BLOBPTR_H

```

## 16.13

> 解释你为 `BlobPtr` 的相等和关系运算符选择哪种类型的友好关系？

选择一一对应的关系。

## 16.14

> 编写 Screen 类模版，用非类型参数定义 Screen 的高和宽。

[Screen](./ex16_14.h)|[test](./ex16_14.cpp)

```c++
//
// Created by wangheng on 2020/6/10.
//

#ifndef CPP_PRIMER_EX16_14_H
#define CPP_PRIMER_EX16_14_H

#include <string>
#include <iostream>

template<unsigned H, unsigned W>
class Screen{
    // 从头打印到cursor所在的位置
    friend std::ostream& operator<<(std::ostream& os, const Screen<H, W> &c) {
        unsigned lines = c.cursor / c.width;
        int i;
        for (i = 0; i < lines; ++i) {
            os << c.contents.substr(i * c.width, c.width) << std::endl;
        }
        os << c.contents.substr(i*c.width, c.cursor - i * c.width) << std::endl;
        return os;
    }
    friend std::istream& operator>>(std::istream& is, const Screen &c) {
        char a;
        is >> a;
        c.contents = std::string(H * W, a);
        return is;
    }

public:
    typedef std::string::size_type pos;

    Screen() = default; // 因为有一个自定义的构造函数，所以默认构造函数必须显示声明，否则不会合成

    explicit Screen(char c) : contents(H*W, c) {}
    char get() const {
        return contents[cursor];
    }
    void set(char c) {
        contents[cursor] = c;
    }

    Screen& move(pos r, pos c);

private:
    pos cursor = 0;
    pos height = H, width = W;
    std::string contents;
};

template<unsigned H, unsigned W>
inline Screen<H, W>& Screen<H, W>::move(pos r, pos c) {
    pos row = r * width;
    cursor = row + c;
    return *this;
}

#endif //CPP_PRIMER_EX16_14_H
```

## 16.15

> 为你的 Screen 模版实现输入和输出运算符。Screen 类需要哪些友元（如果需要的话）来令输入和输出运算符正确工作？解释每个友元声明（如果有的话）为什么是必要的。

类的 operator<< 和 operator>> 应该是类的友元。

## 16.16

> 将 `StrVec `类重写为模版，命名为 `Vec`。

[Vec](../Vec/Vec.h)|[test](../Vec/main.cpp)

```c++
//
// Created by wangheng on 2020/6/10.
//

#ifndef CPP_PRIMER_VEC_H
#define CPP_PRIMER_VEC_H

#include <memory>
#include <initializer_list>
#include <iostream>

template<typename T> class Vec{
public:
    Vec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
    Vec(std::initializer_list<T> il);   // 使用初始化列表构造Vec
    Vec(const Vec&);    // 拷贝构造函数
    Vec& operator=(const Vec&); // 拷贝赋值运算符
    Vec(Vec &&) noexcept ;    // 移动构造函数
    Vec& operator=(Vec&&) noexcept ;  // 移动赋值运算符
    ~Vec(); // 析构函数

    void push_back(const T&);
    std::size_t size() const { return first_free - elements; }
    std::size_t capacity() const { return cap - elements; }
    T* begin() const { return elements; }
    T* end() const { return first_free; }
    void reserve(std::size_t);
    T back() const { return *(first_free -1); }
    T front() const { return *elements; }

private:
    static std::allocator<T> alloc; // 分配元素
    T* elements;    // 第一个元素指针
    T* first_free;  // 第一个未构造元素的指针
    T* cap; // 尾后指针

    // 被添加元素的函数使用
    void check_n_alloc() {
        if (size() == capacity())
            reallocate();
    }
    void free();    // 销毁元素并释放内存

    void reallocate();  // 容量不够时，重新分配内存

    std::pair<T*, T*> alloc_n_copy(const T*, const T*);
};

template<typename T>
std::allocator<T> Vec<T>::alloc;

template<typename T>
Vec<T>::Vec(std::initializer_list<T> il) {
    auto data = alloc.allocate(il.size());
    elements = data;
    for (auto s : il)
        alloc.construct(data++, s);
    first_free = cap = data;
    std::cout << "Vec<T>::Vec(std::initializer<T>)" << std::endl;
}

template<typename T>
Vec<T>::Vec(const Vec& v) {
    if (this != &v) {
        auto newData = alloc_n_copy(v.begin(), v.end());
        elements = newData.first;
        first_free = cap = newData.second;
    }
    std::cout << "Vec<T>::Vec(const Vec&)" << std::endl;
}

template<typename T>
Vec<T>& Vec<T>::operator=(const Vec<T> &rhs) {
    if (this != &rhs) {
        auto newData = alloc_n_copy(rhs.begin(), rhs.end());
        free(); // 释放=左边对象原来的内存
        elements = newData.first;
        first_free = cap = newData.second;
    }
    std::cout << "Vec<T>& Vec<T>::operator=(const Vec&)" << std::endl;
    return *this;
}

template<typename T>
Vec<T>::Vec(Vec<T> &&v) noexcept {
    elements = v.elements;
    first_free = v.first_free;
    cap = v.cap;
    v.elements = v.first_free = v.cap = nullptr;
    std::cout << "Vec<T>::Vec(Vec<T>&& v)" << std::endl;
}

template<typename T>
Vec<T>& Vec<T>::operator=(Vec<T> &&rhs) noexcept {
    if (this != &rhs) {
        free();
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    std::cout << "Vec<T>& Vec<T>::operator=(Vec<T>&&)" << std::endl;
    return *this;
}

template<typename T>
Vec<T>::~Vec() {
    free();
    elements = first_free = cap = nullptr;
    std::cout << "Vec<T>::~Vec()" << std::endl;
}

template<typename T>
void Vec<T>::reallocate() {
    auto newCapacity = size() ? 2 * size() : 1;
    auto first = alloc.allocate(newCapacity);
    // 移动元素
    auto last = std::uninitialized_copy(std::make_move_iterator(begin()),
            std::make_move_iterator(end()), first);
    free();
    elements = first;
    first_free = last;
    cap = elements + newCapacity;
}

template<typename T>
void Vec<T>::free() {
    // 不能传递给deallocate一一个空指针，如果elements为空指针，函数什么也不做
    if (elements) {
        // 逆序销毁旧元素
        for (auto  p = first_free; p != elements; )
            alloc.destroy(--p);
        alloc.deallocate(elements, cap - elements);
    }
}

template<typename T>
std::pair<T*, T*> Vec<T>::alloc_n_copy(const T *b, const T *e) {
    // 分配空间保存给定元素范围的元素
    auto data =  alloc.allocate(e - b);
    // 初始化并返回一个pair，该pair由data和uninitialized_copy的返回值构成
    return {data, std::uninitialized_copy(b, e, data)};
}

template<typename T>
void Vec<T>::reserve(std::size_t n) {
    if (capacity() < n) {
        auto newData = alloc.allocate(n);
        auto first = newData;
        for (auto iter = begin(); iter != end(); ++iter)
            alloc.construct(newData++, *iter);
        free();
        elements = first;
        first_free = newData;
        cap = elements + n;
    }
}

template<typename T>
void Vec<T>::push_back(const T &value) {
    check_n_alloc();
    alloc.construct(first_free++, value);
}

#endif //CPP_PRIMER_VEC_H

```

## 16.17

> 声明为 typename 的类型参数和声明为 class 的类型参数有什么不同（如果有的话）？什么时候必须使用typename？

`typename`和`class`没有什么不同。当我们希望通知编译器一个名字类型时，必须使用关键字`typename`，而不能使用`class`。

## 16.18

> 解释下面每个函数模版声明并指出它们是否非法。更正你发现的每个错误。
>
> ```c++
> (a) template <typename T, U, typename V> void f1(T, U, V);
> (b) template <typename T> T f2(int &T);
> (c) inline template <typename T> T foo(T, unsigned int *);
> (d) template <typename T> f4(T, T);
> (e) typedef char Ctype;
> 	template <typename Ctype> Ctype f5(Ctype a);
> ```

* (a)非法。应该为`template <typename T, typename U, typename V> void f1(T, U, V)`
* (b)非法。应该为`template<typename T> T f2(int &t)`
* (c)非法。应该为`template<typename T> inline T foo(T, unsigned int *);`
* (d)非法，没有返回值，应该为`template <typename T> T f4(T, T)`
* (e)非法，`typedef char Ctype`被隐藏了

## 16.19|[cpp](./ex16_19.cpp)

> 编写函数，接受一个容器的引用，打印容器中的元素。使用容器的 size_type 和 size成员来控制打印元素的循环。

```c++
#include <iostream>
#include <vector>

template <typename T>
void print(const T& container) {
    typename T::size_type i;
    typename T::size_type len = container.size();
    for (i = 0; i < len; ++i)
        std::cout << container[i] << ' ';
}

int main() {
    std::vector<int> ivec{1,2,3,4};
    print(ivec);

    return 0;
}
```

## 16.20|[cpp](./ex16_20.cpp)

> 重写上一题的函数，使用begin 和 end 返回的迭代器来控制循环。

```c++
//
// Created by wh969 on 2020/6/13.
//
#include <iostream>
#include <vector>

template <typename T>
void print(const T &container) {
    for (auto iter = container.begin(); iter != container.end(); ++iter)
        std::cout << *iter << ' ';
}

int main() {
    std::vector<int> ivec =  {1,2,3,9};
    print(ivec);

    return 0;
}
```

## 16.21|[cpp](./ex16_21.cpp)

> 编写你自己的`DebugDelete`版本

```c++
#include <iostream>

class DebugDelete{
public:
    DebugDelete(std::ostream& s = std::cerr) : os(s) {}

    template<typename T>
    void operator() (T* p) const {
        os << "deleting unique_ptr" << std::endl;
        delete p;
    }

private:
    std::ostream &os;
};

int main() {
    int* pi = new int ();
    DebugDelete d;
    d(pi);

    auto* pd = new double ();
    DebugDelete()(pd);
    return 0;
}
```

## 16.22

> 修改12.3节中你的 TextQuery 程序，令 shared_ptr 成员使用 DebugDelete 作为它们的删除器。

## 16.23

> 预测在你的查询主程序中何时会执行调用运算符。如果你的预测和实际不符，确认你理解了原因。

`shared_ptr`引用计数减少到0时会执行删除器`DebugDelete`的调用用算符。

## 16.24

> 为你的 Blob 模版添加一个构造函数，它接受两个迭代器。

```c++
template<typename T>	// for class
template<typename It>	// for this member
Blob<T>::Blob(It b, It e) {
    data(std::make_shared<std::vector<T>>(b, e));
}
```

## 16.25

> 解释下面这些声明的含义。
>
> ```c++
> extern template class vector<string>;
> template class vector<Sales_data>;
> ```

第一个是模板声明，在其他源文件中已经有实例化的模板了，第二个是模板定义，在此源文件中实例化一个类模板。

## 16.26

> 假设 NoDefault 是一个没有默认构造函数的类，我们可以显式实例化 vector<NoDefault>吗？如果不可以，解释为什么。

不可以，如

`std::vector<NODefault> vec(10)`会使用`NoDefault`的默认构造函数，但是它没有默认构造函数。

## 16.27

> 对下面每条带标签的语句，解释发生了什么样的实例化（如果有的话）。如果一个模版被实例化，解释为什么;如果未实例化，解释为什么没有。
>
> ```c++
> template <typename T> class Stack {	};
> void f1(Stack<char>); 		//(a)
> class Exercise {
> 	Stack<double> &rds;		//(b)
> 	Stack<int> si;			//(c)
> };
> int main() {
> 	Stack<char> *sc;		//(d)
> 	f1(*sc);				//(e)
> 	int iObj = sizeof(Stack<string>);	//(f)
> }
> ```

(a)、(b)、(c)、(f)都发生了实例化，(d)、(e)没有实例化。

## 16.28

> 编写你自己版本的 shared_ptr 和 unique_ptr。

[shared_ptr](./shared_ptr.h)|[unique_ptr](./unique_ptr.h)

```c++
#ifndef CPP_PRIMER_SHARED_PTR_H
#define CPP_PRIMER_SHARED_PTR_H

#include <functional>
#include "delete.h"

namespace cp5{
    template<typename T> class SharedPointer;

    template<typename T>
    void swap(SharedPointer<T>& lhs, SharedPointer<T>& rhs) {
        using std::swap;
        swap(lhs.ptr, rhs.ptr);
        swap(lhs.ref_count, rhs.ref_count);
        swap(lhs.delter, rhs.deleter);
    }

    template<typename T> class SharedPointer{
    public:
        SharedPointer() : ptr(nullptr), ref_count(new std::size_t (1)), deleter(cp5::Delete{}) {}

        explicit SharedPointer(T* raw_ptr) :
        ptr(raw_ptr), ref_count(new std::size_t (1)), deleter(cp5::Delete{}) {}

        SharedPointer(SharedPointer const &other) :
        ptr(other.ptr),  ref_count(other.ref_count), deleter(other.deleter){
            ++*ref_count;
        }

        SharedPointer& operator=(SharedPointer const &rhs) {
            if (this != &rhs) {
                ++*rhs.ref_count;
                decrement_and_destroy();
                ptr = rhs.ptr;
                ref_count = rhs.ref_count;
                deleter = rhs.deleter;
            }
            return *this;
        }

        SharedPointer(SharedPointer &&other) noexcept :
        ptr(other.ptr), ref_count(other.ref_count), deleter(std::move(other.deleter)) {
            other.ptr = nullptr;
            other.ref_count = nullptr;
        }

        SharedPointer& operator=(SharedPointer &&rhs) noexcept {
            cp5::swap(*this, rhs);
            rhs.decrement_and_destroy();
            return *this;
        }

        explicit operator bool() const {
            return ptr != nullptr;
        }

        T& operator* () const {
            return *ptr;
        }

        T* operator->() const {
            return ptr;
        }

        std::size_t use_count() const {
            return *ref_count;
        }

        T* get() const {
            return ptr;
        }

        bool unique() const {
            return 1 == *ref_count;
        }

        void swap(SharedPointer& rhs) {
            cp5::swap(*this, rhs);
        }

        void reset(T* pointer) {
            if (ptr != pointer) {
                decrement_and_destroy();
                ptr = pointer;
                ref_count = new std::size_t (1);
            }
        }

        void reset(T* pointer, const std::function<void(T*)> &d) {
            reset(pointer);
            deleter = d;
        }

        ~SharedPointer() {
            decrement_and_destroy();
        }

    private:
        T* ptr;
        std::size_t *ref_count;
        std::function<void(T*)> deleter;

        void decrement_and_destroy() {
            if (ptr && 0 == --*ref_count) {
                delete ref_count;
                deleter(ptr);
            } else if(!ptr)
                delete ref_count;
            ref_count = nullptr;
            ptr = nullptr;
        }
    };
}

#endif //CPP_PRIMER_SHARED_PTR_H

```

unique_ptr

```c++
#ifndef CPP_PRIMER_UNIQUE_PTR_H
#define CPP_PRIMER_UNIQUE_PTR_H

#include "delete.h"
#include <iostream>

template<typename, typename > class UniquePointer;

template<typename T, typename D>
void swap(UniquePointer<T, D>& lhs, UniquePointer<T, D>& rhs);

template<typename T, typename D = cp5::Delete> class UniquePointer{
    friend void swap<T, D>(UniquePointer<T, D>& lhs, UniquePointer<T, D>& rhs);

public:
    // 禁止拷贝构造和拷贝赋值运算
    UniquePointer(const UniquePointer&) = delete ;
    UniquePointer& operator=(const UniquePointer&) = delete ;

    UniquePointer() = default;
    explicit UniquePointer(T *pointer) : ptr(pointer) {}

    UniquePointer(UniquePointer && other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    UniquePointer& operator=(UniquePointer &&rhs) noexcept;

    UniquePointer& operator=(std::nullptr_t n) noexcept ;

    T& operator*() const { return *ptr; }
    T* operator->() const { return &this->operator*(); }
    operator bool() const { return ptr!= nullptr; }

    T* get() const noexcept { return ptr; }

    void swap(UniquePointer& rhs) { ::swap(*this, rhs); }

    void reset() noexcept { deleter(ptr); ptr = nullptr; }
    void reset(T* p) noexcept { deleter(ptr); ptr = p; }

    T* release();

    ~UniquePointer() { deleter(ptr); }
private:
    T* ptr = nullptr;
    D deleter = D();
};

template<typename T, typename D>
inline void swap(UniquePointer<T, D>& lhs, UniquePointer<T, D>& rhs) {
    using std::move;
    swap(lhs.ptr, rhs.ptr);
    swap(lhs.deleter, rhs.deleter);
}

template<typename T, typename D>
inline UniquePointer<T, D>& UniquePointer<T, D>::operator=(UniquePointer&& rhs) noexcept {
    if (this->ptr != rhs.ptr) {
        deleter(ptr);
        ptr = nullptr;
        swap(*this, rhs);
    }
    return *this;
}

template<typename T, typename D>
inline UniquePointer<T, D>& UniquePointer<T, D>::operator=(std::nullptr_t n) noexcept {
    if (n == nullptr) {
        deleter(ptr);
        ptr = nullptr;
    }
    return *this;
}

template<typename T, typename D>
inline T* UniquePointer<T, D>::release() {
    T* ret = ptr;
    ptr = nullptr;
    return ret;
}

#endif //CPP_PRIMER_UNIQUE_PTR_H
```

## 16.29

> 修改你的 Blob 类，用你自己的 shared_ptr 代替标准库中的版本。

## 16.30

> 重新运行你的一些程序，验证你的 shared_ptr 类和修改后的 Blob 类。（注意：实现 weak_ptr 类型超出了本书范围，因此你不能将BlobPtr类与你修改后的Blob一起使用。）

## 16.31

> 如果我们将 DebugDelete 与 unique_ptr 一起使用，解释编译器将删除器处理为内联形式的可能方式。

`shared_ptr`是运行时绑定删除器，而`unique_ptr`则是编译时绑定删除器。`unique_ptr`有两个模板参数，一个是所管理的对象类型，一个是删除器类型。因此，删除器类型是`unique_ptr`类型的一部分，在编译时就可知道，删除器可直接保存在`unique_ptr`对象中。通过这种方式，`unique_ptr`避免了间接调用删除器的运行时开销，而编译器还可以将自定义的删除器，如`DebugDelete`编译为内联形式。

## 16.32

> 在模版实参推断过程中发生了什么？

对于一个函数模板，当我们调用它时，编译器会利用调用中的函数实参来推断其模板参数，这些模板实参实例化出的版本与我们的函数调用应该是最匹配的版本，这个过程就成为模板实参推断。

## 16.33

> 指出在模版实参推断过程中允许对函数实参进行的两种类型转换。

在模板实参推断过程中，如果函数形参的类型使用了模板类型参数，则只允许进行两种类型转换。

1. const转换：可以将一个非const对象的引用（或指针）传递给一个const对象（或指针）形参。
2. 数组或函数到指针的转换：如果函数形参不是引用类型，则可以对数组或函数类型的实参应用正常的指针转换。一个数组实参可以转换为一个指向其首元素的指针。类似的，一个函数实参可以转换为一个该函数类型的指针。

## 16.34

> 对下面的代码解释每个调用是否合法。如果合法，T 的类型是什么？如果不合法，为什么？
>
> ```c++
> template <class T> int compare(const T&, const T&);
> (a) compare("hi", "world");
> (b) compare("bye", "dad");
> ```

* (a)不合法。`compare(const char[3], const char[6])`，两个实参类型不一致。
* (b)合法。`compare(const char[4], const char[4])`。

## 16.35

> 下面调用中哪些是错误的（如果有的话）？如果调用合法，T 的类型是什么？如果调用不合法，问题何在？
>
> ```c++
> template <typename T> T calc(T, int);
> tempalte <typename T> T fcn(T, T);
> double d; float f; char c;
> (a) calc(c, 'c'); 
> (b) calc(d, f);
> (c) fcn(c, 'c');
> (d) fcn(d, f);
> ```

* (a)合法，类型为char
* (b)合法，类型为double
* (c)合法，类型为char
* (d)不合法，从实参d推断T为double，从实参f推断T为float，不一致。

## 16.36

> 进行下面的调用会发生什么：
>
> ```c++
> template <typename T> f1(T, T);
> template <typename T1, typename T2) f2(T1, T2);
> int i = 0, j = 42, *p1 = &i, *p2 = &j;
> const int *cp1 = &i, *cp2 = &j;
> (a) f1(p1, p2);
> (b) f2(p1, p2);
> (c) f1(cp1, cp2);
> (d) f2(cp1, cp2);
> (e) f1(p1, cp1);
> (f) f2(p1, cp1);
> ```

* (a)`f1(int*, int*)`，T类型推断为int*
* (b)`f2(int*, int*)`，T1类型推断为`int*`, T2类型推断为`int*`
* (c)调用合法，T被推断为const int*
* (d)调用合法，T1和T2都被推断为const int*
* (e)调用非法，T被推断为`int*`或者是`const int*`，不能匹配调用
* (f)调用合法，T1被推断为`int*`，T2被推断为`const int*`

## 16.37

> 标准库 max 函数有两个参数，它返回实参中的较大者。此函数有一个模版类型参数。你能在调用 max 时传递给它一个 int 和一个 double 吗？如果可以，如何做？如果不可以，为什么？

可以用一个int和一个double调用max，显示指定模板实参即可，例如：`auto m = max<double>(1, 2.0);`

## 16.38

> 当我们调用 make_shared 时，必须提供一个显示模版实参。解释为什么需要显式模版实参以及它是如果使用的。

在调用`make_shared`时，有时不给出参数，表示进行值初始化。有时给出的参数与维护的动态对象的类型不直接关联，如`make_shared<string>(10, '9')`创建值“9999999999”的。因此，编译器无法从参数推断出模板实参，就需要显示显示指定模板实参。

## 16.39

> 对16.1.1节 中的原始版本的 compare 函数，使用一个显式模版实参，使得可以向函数传递两个字符串字面量。

compare<string>(“hello”, “world)

## 16.40

> 下面的函数是否合法？如果不合法，为什么？如果合法，对可以传递的实参类型有什么限制（如果有的话）？返回类型是什么？
>
> ```c++
> template <typename It>
> auto fcn3(It beg, It end) -> decltype(*beg + 0)
> {
> 	//处理序列
> 	return *beg;
> }
> ```

1. 合法，该类型必须支持“+”
2. *beg + 0是右值，因此fcn3的返回类型被推断为元素类型的常量引用。

## 16.41

> 编写一个新的 sum 版本，它返回类型保证足够大，足以容纳加法结果。

```c++
template <typename T>
auto sum(T lhs, T rhs) -> decltype(lhs + rhs) {
    return lhs + rhs;
}
```

## 14.42

> 对下面每个调用，确定 T 和 val 的类型：
>
> ```c++
> template <typename T> void g(T&& val);
> int i = 0; const int ci = i;
> (a) g(i);
> (b) g(ci);
> (c) g(i * ci);
> ```

* (a)T类型为int&，函数参数val类型为int& &&，即为int&
* (b)T类型为const int&，函数参数val类型为const int& &&，即为const int&
* (c)T类型为int，函数参数val类型为int&&

## 14.43

> 使用上一题定义的函数，如果我们调用g(i = ci),g 的模版参数将是什么？

i = ci返回的是左值，因此T推断的类型为int&，val经过引用折叠被确定为int&

## 14.44

> 使用与第一题中相同的三个调用，如果 g 的函数参数声明为 T（而不是T&&），确定T的类型。如果g的函数参数是 const T&呢？

当声明为T时，模板参数对g(i)推断为int，对g(ci)推断为int，对g(i * ci)推断为int，如果g 的函数参数是const T&，模板参数对g(i)推断为int，对g(ci)推断为int，对g(i * ci)推断为int

## 14.45

> 如果下面的模版，如果我们对一个像42这样的字面常量调用g，解释会发生什么？如果我们对一个int 类型的变量调用g 呢？
>
> ```c++
> template <typename T> void g(T&& val) { vector<T> v; }
> ```

当使用42这样的字面值常量调用g时，T 被推断为int，编译运行正常。

如果对一个int类型的变量调用g时，T被推断为int&， 编译错误，无法创建vector<int&>，无法为其分配内存。