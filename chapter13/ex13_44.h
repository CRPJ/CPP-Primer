//
// Created by wangheng on 2020/4/26.
//

#ifndef CPP_PRIMER_EX13_44_H
#define CPP_PRIMER_EX13_44_H

#include <iostream>
#include <memory>
#include <cstring>
#include <algorithm>
#include <string>

class String {
    friend std::ostream& operator<<(std::ostream&, const String&);
    friend bool operator==(const String&, const String&);
    friend bool operator!=(const String&, const String&);
    friend bool operator<(const String&, const String&);

public:
    String() : elements(nullptr), cap(nullptr) {}
    String(const char*);
    String(const String&);
    String& operator=(const String&);
    String(String&&) noexcept ;
    String& operator=(String&&) noexcept ;
    ~String();
    const char& operator[](std::size_t) const ;
    char front() const { return *elements; }
    char back() const { return *(cap - 1);}
    const char *c_str() const ;
    std::size_t size() const { return cap - elements; }
    char *begin() const { return elements; }
    char *end() const { return cap; }
    char& operator[](const std::size_t n);

private:
    static std::allocator<char> alloc;
    std::pair<char*, char*> alloc_n_copy(const char*, const char*);
    void free();
    char *elements;
    char *cap;
};

std::allocator<char> String::alloc;

String::String(const char *pc) {
    auto newdata = alloc.allocate(std::strlen(pc));
    elements = newdata;
    auto len = std::strlen(pc);
    for (std::size_t i = 0; i < len; ++i)
        alloc.construct(newdata++, *pc++);
    cap = newdata;
    std::cout << "String(const char*)" << std::endl;
}

String::String(const String &s) {
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    cap = newdata.second;
    std::cout << "String(const String&)" << std::endl;
}

String& String::operator=(const String &s) {
    auto newdata = alloc_n_copy(s.begin(), s.end());
    free();
    elements = newdata.first;
    cap = newdata.second;
    std::cout << "operator=(const String&)" << std::endl;
    return *this;
}

String::String(String &&s) noexcept : elements(s.elements), cap(s.cap) {
    s.elements = s.cap = nullptr;
    std::cout << "String(String&&)" << std::endl;
}

String& String::operator=(String &&rhs) noexcept {
    if (this != &rhs) {
        free();
        elements = rhs.elements;
        cap = rhs.cap;
        rhs.elements = rhs.cap = nullptr;
    }
    return *this;
}

String::~String() { free(); }

void String::free() {
    if (elements) {
        std::for_each(begin(), end(), [](const char& c) {alloc.destroy(&c);});
        alloc.deallocate(begin(), size());
    }
}

const char* String::c_str() const {
    return elements;
}

const char& String::operator[](std::size_t i) const {
    return *(elements + i);
}

char& String::operator[](const std::size_t n) {
    return *(elements + n);
}

std::pair<char*, char*> String::alloc_n_copy(const char *b, const char *e) {
    auto data = alloc.allocate(e - b);
    return {data, std::uninitialized_copy(b, e, data)};
}

std::ostream& operator<<(std::ostream& os, const String& s) {
    os << s.c_str();
    return os;
}

bool operator==(const String& lhs, const String& rhs) {
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

bool operator!=(const String& lhs, const String& rhs) {
    return !(lhs == rhs);
}

bool operator<(const String& lhs, const String& rhs) {
    return std::string(lhs.c_str()) < std::string(rhs.c_str());
}

#endif //CPP_PRIMER_EX13_44_H
