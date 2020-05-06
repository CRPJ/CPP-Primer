//
// Created by wangheng on 2020/5/6.
//

#include "ex14_15.h"

Book& Book::operator+=(const Book &rhs) {
    number += rhs.number;
    return *this;
}

Book& Book::operator-=(const Book &rhs) {
    number -= rhs.number;
    return *this;
}

std::istream& operator>>(std::istream& in, Book& book) {
    in >> book.no >> book.name >> book.author >> book.pubDate >> book.number;
    if (!in)
        book = Book();
    return in;
}
std::ostream& operator<<(std::ostream& os, const Book& book) {
    os << book.no << ' ' << book.name << ' ' << book.author << ' ' << book.pubDate << ' ' << book.number;
    return os;
}
bool operator==(const Book& lhs, const Book& rhs) {
    return lhs.no == rhs.no;
}
bool operator!=(const Book& lhs, const  Book& rhs) {
    return !(lhs.no == rhs.no);
}

bool operator<(const Book& lhs, const Book& rhs) {
    return lhs.no < rhs.no;
}
bool operator>(const Book&lhs, const Book& rhs) {
    return lhs.no > rhs.no;
}
Book operator+(const Book& lhs, const Book& rhs) {
    Book result = lhs;
    result += rhs;
    return result;
}
Book operator-(const Book& lhs, const Book& rhs) {
    Book result = lhs;
    result -= rhs;
    return result;
}