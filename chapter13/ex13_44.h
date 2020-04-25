//
// Created by wangheng on 2020/4/26.
//

#ifndef CPP_PRIMER_EX13_44_H
#define CPP_PRIMER_EX13_44_H

#include <memory>

class String {
public:
    String() {}
    
private:
    std::pair<char*, char*> alloc_n_copy(const char*, const char*);
    void range_initializer(const char*, const char*);
    void free();
    char *elements;
    char *end;
    std::allocator<char> alloc;
};
#endif //CPP_PRIMER_EX13_44_H
