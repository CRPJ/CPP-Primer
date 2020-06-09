//
// Created by wangheng on 2020/6/7.
//

#ifndef QUERY_QUERY_BASE_H
#define QUERY_QUERY_BASE_H

#include <string>
#include "TextQuery.h"
#include "QueryResult.h"

class Query_base{
    friend class Query;

protected:
    using line_no = TextQuery::line_no;
    virtual ~Query_base() = default;

private:
    // eval返回与当前Query匹配的QueryResult
    virtual QueryResult eval(const TextQuery&) const  = 0;
    // rep是表示查的一个string
    virtual std::string rep() const = 0;
};

#endif //QUERY_QUERY_BASE_H
