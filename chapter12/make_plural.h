//
// Created by wangheng on 2020/4/24.
//

#ifndef CPP_PRIMER_MAKE_PLURAL_H
#define CPP_PRIMER_MAKE_PLURAL_H

#include <string>
inline
std::string make_plural(std::size_t ctr, const std::string& word, const std::string ending)
{
    return (ctr == 1) ? word : word+ending;
}

#endif //CPP_PRIMER_MAKE_PLURAL_H
