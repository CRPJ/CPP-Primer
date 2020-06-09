//
// Created by wangheng on 2020/6/8.
//

#include "Query.h"

Query::Query(const std::string &s) : q(new WordQuery(s)) {}