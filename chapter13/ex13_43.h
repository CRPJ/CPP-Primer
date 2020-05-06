//
// Created by wangheng on 2020/4/25.
//

#ifndef CPP_PRIMER_EX13_43_H
#define CPP_PRIMER_EX13_43_H

#include <iostream>
#include <memory>
#include <string>
#include <initializer_list>
#include <algorithm>

class StrVec {
    friend bool operator==(const StrVec&, const StrVec&);
    friend bool operator!=(const StrVec&, const StrVec&);
    friend bool operator<(const StrVec&, const StrVec&);
    friend std::ostream& operator<<(std::ostream&, const StrVec&);

public:
    StrVec() :  // allocator成员进行默认初始化
            elements(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(std::initializer_list<std::string> il);
    StrVec(const StrVec&);  // 拷贝构造函数
    StrVec& operator=(const StrVec&);   // 拷贝赋值运算符
    StrVec(StrVec&&) noexcept ;   // 移动构造函数
    StrVec& operator=(StrVec&&) noexcept ;    // 移动赋值运算符
    StrVec& operator=(std::initializer_list<std::string>);  // 赋值运算符
    ~StrVec();  // 析构函数
    void push_back(const std::string&);   // 拷贝元素
    std::size_t size() const { return first_free - elements; }
    std::size_t capacity() const { return cap - elements; }
    std::string *begin() const { return elements; }
    std::string *end() const { return first_free; }
    void reserve(std::size_t);
    void resize(std::size_t);
    std::string& operator[](const std::size_t n);
    const std::string& operator[](const std::size_t n) const ;

private:
    static std::allocator<std::string> alloc;   // 分配元素
    // 被添加元素的函数所使用
    void chk_n_alloc() {
        if (size() == capacity())
            reallocate();
    }
    // 工具函数，被拷贝构造函数、赋值运算符和析构函数使用
    std::pair<std::string*, std::string*> alloc_n_copy
            (const std::string*, const std::string*);
    void free();    // 销毁元素并释放内存
    void reallocate();  // 获得更多内存并拷贝已有元素
    std::string *elements;
    std::string *first_free;
    std::string *cap;

};

std::allocator<std::string> StrVec::alloc;

StrVec::StrVec(std::initializer_list<std::string> il) {
    auto newdata = alloc.allocate(il.size());
    elements = newdata;
    for (auto s : il)
        alloc.construct(newdata++, s);
    first_free = cap = newdata;
    std::cout << "StrVec(std::initializer_list<std::string>)" << std::endl;
}

StrVec::StrVec(const StrVec &sv) {
    // 调用alloc_n_copy分配空间以容纳与s中一样多的元素
    auto newdata = alloc_n_copy(sv.begin(), sv.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
    std::cout << "StrVec(const StrVec&)" << std::endl;
}

StrVec& StrVec::operator=(const StrVec &sv) {
    // 调用alloc_n_copy分配内存，大小与sv中元素一样多
    auto newdata = alloc_n_copy(sv.begin(), sv.end());
    free();
    elements = newdata.first;
    first_free = cap = newdata.second;
    std::cout << "operator=(const StrVec&)" << std::endl;
    return *this;
}

StrVec::StrVec(StrVec &&sv) noexcept :
        elements(sv.elements), first_free(sv.first_free), cap(sv.cap) {
    sv.elements = sv.first_free = sv.cap = nullptr;
    std::cout << "StrVec(StrVec&&)" << std::endl;
}

StrVec& StrVec::operator=(StrVec &&rhs) noexcept {
    if (this != &rhs) {
        free();
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    std::cout << "operator=(StrVec&&)" << std::endl;
    return *this;
}

StrVec& StrVec::operator=(std::initializer_list<std::string> il) {
    *this = StrVec(std::move(il));
    return *this;
}

StrVec::~StrVec() noexcept {
    free();
}

void StrVec::push_back(const std::string &s) {
    chk_n_alloc();  // 确保有空间容纳所有元素
    // 在first_free指向的元素中构造s的副本
    alloc.construct(first_free++, s);
}

std::pair<std::string*, std::string*>
StrVec::alloc_n_copy(const std::string *b, const std::string *e) {
    // 分配空间保存给定元素范围中的元素
    auto data = alloc.allocate(e - b);
    // 初始化并返回一个pair，该pair由data和uninitialized_copy的返回值构成
    return {data, std::uninitialized_copy(b, e, data)};
}

void StrVec::free() {
    // 不能传递给deallocate一个空指针，如果elements为0，函数什么也不做
    if (elements) {
        // 逆序销毁旧元素
        std::for_each(begin(), end(), [](std::string& rhs) {alloc.destroy(&rhs);});
        alloc.deallocate(elements, cap - elements);
    }
}

void StrVec::reallocate() {
    // 我们将分配当前大小两倍的内存空间
    auto newcapacity = size() ? 2 * size() : 1;
    auto first = alloc.allocate(newcapacity);
    // 移动元素
    auto last = std::uninitialized_copy(std::make_move_iterator(begin()),
                                        std::make_move_iterator(end()), first);
    free();
    elements = first;
    first_free = last;
    cap = elements + newcapacity;
}

void StrVec::reserve(std::size_t n) {
    if (capacity() < n) {
        auto newdata = alloc.allocate(n);
        auto dest = newdata;
        auto elem = elements;
        for (std::size_t i = 0; i != size(); ++i)
            alloc.construct(dest++, std::move(*elem++));
        free();
        elements = newdata;
        first_free = dest;
        cap = elements + n;
    }
}

void StrVec::resize(std::size_t n) {
    if (n < size()) {
        auto len = size() - n;
        for (std::size_t i = 0; i < len; ++i)
            alloc.destroy(--first_free);
    } else {
        reserve(n);
        auto len = n - size();
        for (std::size_t i = 0; i < len; ++i)
            alloc.construct(first_free++, std::string());
    }
}

std::string& StrVec::operator[](const std::size_t n) {
    return elements[n];
}

const std::string& StrVec::operator[](const std::size_t n) const {
    return elements[n];
}

bool operator==(const StrVec& lhs, const StrVec& rhs) {
    if (lhs.size() != rhs.size())
        return false;
    else {
        auto p = rhs.elements;
        for (auto iter = lhs.begin(); iter != lhs.end(); ++iter) {
            if (*iter != *p++)
                return false;
        }
    }
    return true;
}
bool operator!=(const StrVec& lhs, const StrVec& rhs) {
    return !(lhs == rhs);
}

bool operator<(const StrVec& lhs, const StrVec& rhs) {
    auto p = rhs.elements;
    for (auto iter = lhs.begin(); iter != lhs.end(); ++iter) {
        if (*iter < *p++)
            return true;
        else if (*iter > *p)
            return false;
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const StrVec& rhs) {
    for (auto iter = rhs.begin(); iter != rhs.end(); ++iter)
        os << *iter << ' ';
    return os;
}

#endif //CPP_PRIMER_EX13_43_H
