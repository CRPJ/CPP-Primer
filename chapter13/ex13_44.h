//
// Created by wangheng on 2020/4/26.
//

#ifndef CPP_PRIMER_EX13_44_H
#define CPP_PRIMER_EX13_44_H

#include <memory>
#include <cstring>
#include <algorithm>

class String {
public:
    String() : elements(nullptr), cap(nullptr) {}
    String(const char*);
    String(const String&);
    String& operator=(const String&);
    ~String();
    char operator[](std::size_t) const ;
    char front() const { return *elements; }
    char back() const { return *(cap - 1);}
    const char *c_str();
    std::size_t size() const { return cap - elements; }
    char *begin() const { return elements; }
    char *end() const { return cap; }

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

String::~String() { free(); }

void String::free() {
    if (elements) {
        std::for_each(begin(), end(), [](const char& c) {alloc.destroy(&c);});
        alloc.deallocate(begin(), size());
    }
}

const char* String::c_str() {
    return elements;
}

char String::operator[](std::size_t i) const {
    return *(elements+i);
}

std::pair<char*, char*> String::alloc_n_copy(const char *b, const char *e) {
    auto data = alloc.allocate(e - b);
    return {data, std::uninitialized_copy(b, e, data)};
}

#endif //CPP_PRIMER_EX13_44_H
