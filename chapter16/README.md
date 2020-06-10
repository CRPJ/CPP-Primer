# 目录

| [16.01](#1601) | [16.02](#1602cpp) | [16.03](#1603) | [16.04](#1604cpp) | [16.05](#1605cpp) | [16.06](#1606cpp) |
| :------------: | :---------------: | :------------: | :---------------: | :---------------: | :---------------: |
| [16.07](#1607) |  [16.08](#1608)   | [16.09](#1609) |                   |                   |                   |
|                |                   |                |                   |                   |                   |
|                |                   |                |                   |                   |                   |
|                |                   |                |                   |                   |                   |
|                |                   |                |                   |                   |                   |
|                |                   |                |                   |                   |                   |
|                |                   |                |                   |                   |                   |
|                |                   |                |                   |                   |                   |
|                |                   |                |                   |                   |                   |
|                |                   |                |                   |                   |                   |
|                |                   |                |                   |                   |                   |

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



