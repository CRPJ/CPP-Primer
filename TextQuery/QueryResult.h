//
// Created by wangheng on 2020/6/7.
//

#ifndef QUERY_QUERYRESULT_H
#define QUERY_QUERYRESULT_H

#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <memory>
#include "make_plural.h"

class QueryResult {
    friend std::ostream& print(std::ostream&, const QueryResult&);

public:
    using line_no = std::vector<std::string>::size_type ;

    QueryResult(std::string s,
            std::shared_ptr<std::set<line_no>> p,
            std::shared_ptr<std::vector<std::string>> f) :
            sought(std::move(s)), lines(std::move(p)), file(std::move(f)) {}

    std::set<line_no>::iterator begin();

    std::set<line_no>::iterator end();

    std::shared_ptr<std::vector<std::string>> getFile();

private:
    std::string sought;
    std::shared_ptr<std::set<line_no>> lines;
    std::shared_ptr<std::vector<std::string>> file;
};


#endif //QUERY_QUERYRESULT_H
