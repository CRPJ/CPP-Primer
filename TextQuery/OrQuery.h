//
// Created by wangheng on 2020/6/7.
//

#ifndef QUERY_ORQUERY_H
#define QUERY_ORQUERY_H

#include <memory>
#include "BinaryQuery.h"
#include "QueryResult.h"
#include "Query_base.h"

class OrQuery : public BinaryQuery {
    friend Query operator|(const Query&, const Query&);

    OrQuery(const Query& lhs, const Query& rhs) : BinaryQuery(lhs, rhs, "|") {}

    QueryResult eval(const TextQuery&) const override;
};

inline Query operator|(const Query& lhs, const Query& rhs) {
    return Query(std::shared_ptr<Query_base>(new OrQuery(lhs, rhs)));
}

#endif //QUERY_ORQUERY_H
