//
// Created by wangheng on 2020/6/7.
//

#ifndef QUERY_NOTQUERY_H
#define QUERY_NOTQUERY_H

#include "Query.h"
#include <memory>
#include <utility>
#include "Query_base.h"

class NotQuery : public Query_base {
    friend Query operator~(const Query&);

    explicit NotQuery(Query   q) : query(std::move(q)) {}

    std::string rep() const override {
        return "~(" + query.rep() + ")";
    }

    QueryResult eval(const TextQuery&) const override;

    Query query;
};

inline Query operator~(const Query &operand) {
    return Query(std::shared_ptr<Query_base>(new NotQuery(operand)));
}

#endif //QUERY_NOTQUERY_H
