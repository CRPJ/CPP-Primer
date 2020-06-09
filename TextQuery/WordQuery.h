//
// Created by wangheng on 2020/6/7.
//

#ifndef QUERY_WORDQUERY_H
#define QUERY_WORDQUERY_H

#include <string>
#include <utility>
#include "Query_base.h"
#include "QueryResult.h"
#include "TextQuery.h"

class WordQuery : public Query_base {
    friend class Query;

    explicit WordQuery(std::string  s) : query_word(std::move(s)) {}

    QueryResult eval(const TextQuery& t) const override {
        return t.query(query_word);
    }

    std::string rep() const override {
        return query_word;
    }

    std::string query_word;
};


#endif //QUERY_WORDQUERY_H
