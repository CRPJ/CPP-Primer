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
