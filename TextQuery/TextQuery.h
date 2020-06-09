//
// Created by wangheng on 2020/6/7.
//

#ifndef QUERY_TEXTQUERY_H
#define QUERY_TEXTQUERY_H

#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <map>
#include <set>
#include <sstream>
#include "QueryResult.h"

class TextQuery {
public:
    using line_no = std::vector<std::string>::size_type;
    explicit TextQuery(std::ifstream&);
    QueryResult query(const std::string&) const ;

private:
    std::shared_ptr<std::vector<std::string>> file;
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};


#endif //QUERY_TEXTQUERY_H
