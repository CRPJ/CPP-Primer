//
// Created by wangheng on 2020/5/5.
//

#include "ex14_05.h"

std::istream& operator>>(std::istream& in, Book& book) {
    in >> book.no >> book.name >> book.author >> book.pubDate;
    return in;
}
std::ostream& operator<<(std::ostream& os, const Book& book) {
    os << book.no << ' ' << book.name << ' ' << book.author << ' ' << book.pubDate;
    return os;
}
bool operator==(const Book& lhs, const Book& rhs) {
    return lhs.no == rhs.no;
}
bool operator!=(const Book& lhs, const  Book& rhs) {
    return !(lhs.no == rhs.no);
}