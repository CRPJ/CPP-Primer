//
// Created by wangheng on 2020/4/24.
//

#ifndef CPP_PRIMER_EX12_32_H
#define CPP_PRIMER_EX12_32_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <memory>
#include "make_plural.h"
#include "ex12_22.h"

class QueryResult
{
    friend std::ostream& print(std::ostream&, const QueryResult&);

public:
    using line_no = std::vector<std::string>::size_type;
    QueryResult(std::string s,
                std::shared_ptr<std::set<line_no>> p,
                StrBlob f) :
            sought(s), lines(p), file(f) {}
private:
    std::string sought;
    std::shared_ptr<std::set<line_no>> lines;
    StrBlob file;
};
class TextQuery
{
public:
    using line_no = std::vector<std::string>::size_type;
    TextQuery(std::ifstream&);
    QueryResult query(const std::string&) const;

private:
    StrBlob file;
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

TextQuery::TextQuery(std::ifstream &is) : file(StrBlob())
{
    std::string text;
    while (std::getline(is, text))
    {
        file.push_back(text);
        int n = file.size() - 1;
        std::istringstream line(text);
        std::string word;
        while (line >> word)
        {
            auto &lines = wm[word];
            if (!lines)
            {
                lines.reset(new std::set<line_no>);
            }
            lines->insert(n);
        }
    }
}

QueryResult
TextQuery::query(const std::string &sought) const {
    static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
    auto loc = wm.find(sought);
    if (loc == wm.end())
    {
        return QueryResult(sought, nodata, file);
    } else
    {
        return QueryResult(sought, loc->second, file);
    }
}

std::ostream &print(std::ostream& os, const QueryResult& qr)
{
    os << qr.sought << " occurs " << qr.lines->size() << " " <<
       make_plural(qr.lines->size(), "time", "s") << std::endl;

    for (auto num : *qr.lines) {
        os << "\t(line " << num + 1 << ") " << ConstStrBlobPtr(qr.file, num).dref() << std::endl;
    }
    return os;
}

#endif //CPP_PRIMER_EX12_32_H
