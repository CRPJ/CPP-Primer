//
// Created by wangheng on 2020/6/7.
//

#include "QueryResult.h"

std::ostream &print(std::ostream &os, const QueryResult &qr) {
    os << qr.sought << " occurs " << qr.lines->size() << " " <<
        make_plural(qr.lines->size(), "time", "s") << std::endl;
    for (auto num : *qr.lines)
        os << "\t(line " << num + 1 << ") " << (*(qr.file->begin() + num)) << std::endl;

    return os;
}

std::set<QueryResult::line_no>::iterator QueryResult::begin() {
    return lines->begin();
}

std::set<QueryResult::line_no>::iterator QueryResult::end() {
    return lines->end();
}

std::shared_ptr<std::vector<std::string>> QueryResult::getFile() {
    return file;
}