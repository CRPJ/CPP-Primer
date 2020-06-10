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

