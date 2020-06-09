//
// Created by wangheng on 2020/6/7.
//

#ifndef QUERY_MAKE_PLURAL_H
#define QUERY_MAKE_PLURAL_H

#include <string>
inline
std::string make_plural(std::size_t ctr, const std::string& word, const std::string& ending)
{
    return (ctr == 1 || ctr == 0) ? word : word+ending;
}

#endif //QUERY_MAKE_PLURAL_H
