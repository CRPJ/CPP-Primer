//
// Created by wangheng on 2020/6/7.
//

#ifndef QUERY_ANDQUERY_H
#define QUERY_ANDQUERY_H

#include <memory>
#include <algorithm>
#include "BinaryQuery.h"
#include "QueryResult.h"
#include "TextQuery.h"
#include "Query_base.h"

class AndQuery : public BinaryQuery {
    friend Query operator&(const Query&, const Query&);

    AndQuery(const Query &l, const Query &r)
            : BinaryQuery(l, r, "&") {}

    // 具体的类，AndQuery继承了rep并且定义了其他纯虚函数
    QueryResult eval(const TextQuery&) const override;
};

inline Query operator&(const Query &lhs, const Query &rhs) {
    return Query(std::shared_ptr<Query_base>(new AndQuery(lhs, rhs)));
}

#endif //QUERY_ANDQUERY_H
