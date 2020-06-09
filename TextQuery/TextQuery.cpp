//
// Created by wangheng on 2020/6/7.
//

#include "TextQuery.h"

TextQuery::TextQuery(std::ifstream &is) :file(new std::vector<std::string>()) {
    std::string text;
    while (std::getline(is, text)) {
        file->push_back(text);
        line_no n = file->size() - 1;
        std::istringstream line(text);
        std::string word;
        while (line >> word) {
            auto &lines = wm[word];
            if (!lines)
                lines.reset(new std::set<line_no>);
            lines->insert(n);
        }
    }
}

QueryResult TextQuery::query(const std::string &sought) const {
    static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>());
    auto loc = wm.find(sought);
    if (loc == wm.cend()){
        return QueryResult(sought, nodata, file);
    } else {
        return QueryResult(sought, loc->second, file);
    }
}