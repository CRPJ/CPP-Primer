//
// Created by wangheng on 2020/6/7.
//

#ifndef QUERY_BINARYQUERY_H
#define QUERY_BINARYQUERY_H

#include <string>
#include <utility>
#include "Query.h"
#include "Query_base.h"

class BinaryQuery : public Query_base {
protected:
    BinaryQuery(Query  l, Query  r, std::string  s) :
        lhs(std::move(l)), rhs(std::move(r)), opSym(std::move(s)) {}

    std::string rep() const override {
        return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")";
    }

    Query lhs, rhs;     // 左侧和右侧的运算对象
    std::string opSym;  // 运算符的名称
};


#endif //QUERY_BINARYQUERY_H
