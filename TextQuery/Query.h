//
// Created by wangheng on 2020/6/8.
//

#ifndef QUERY_QUERY_H
#define QUERY_QUERY_H

#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include "Query_base.h"
#include "WordQuery.h"

class Query : public Query_base {
    friend Query operator~(const Query&);
    friend Query operator|(const Query&, const Query&);
    friend Query operator&(const Query&, const Query&);

public:
    explicit Query(const std::string& s);

    QueryResult eval(const TextQuery& text) const override {
        return q->eval(text);
    }

    std::string rep() const override {
        return q->rep();
    }

private:
    explicit Query(std::shared_ptr<Query_base> query) : q(std::move(query)) {}
    std::shared_ptr<Query_base> q;
};


#endif //QUERY_QUERY_H
