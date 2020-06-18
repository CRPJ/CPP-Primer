# 目录

|  [16.01](#1601)   | [16.02](#1602cpp) |  [16.03](#1603)   | [16.04](#1604cpp) | [16.05](#1605cpp) | [16.06](#1606cpp) |
| :---------------: | :---------------: | :---------------: | :---------------: | :---------------: | :---------------: |
|  [16.07](#1607)   |  [16.08](#1608)   |  [16.09](#1609)   |  [16.10](#1610)   |  [16.11](#1611)   |  [16.12](#1612)   |
|  [16.13](#1613)   |  [16.14](#1614)   |  [16.15](#1615)   |  [16.16](#16.16)  |  [16.17](#1617)   |  [16.18](#1618)   |
| [16.19](#1619cpp) | [16.20](#1620cpp) | [16.21](#1621cpp) |                   |                   |                   |
|                   |                   |                   |                   |                   |                   |
|                   |                   |                   |                   |                   |                   |
|                   |                   |                   |                   |                   |                   |
|                   |                   |                   |                   |                   |                   |
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

> 