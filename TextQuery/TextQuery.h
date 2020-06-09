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
    // file保存查询的源文本内容，安行保存
    std::shared_ptr<std::vector<std::string>> file;
    // 将每个单词和对应出现的行号组成的set构成一个map，通过输入需要查询的单词可以得到对应出
    // 现的行号的set
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};


#endif //QUERY_TEXTQUERY_H
