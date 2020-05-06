//
// Created by wangheng on 2020/5/6.
//

#include "ex14_15.h"

Book::Book(const Book &rhs) :
    no(rhs.no), name(rhs.name), author(rhs.author), pubDate(rhs.pubDate), number(rhs.number) {
    std::cout << "Book(const Book&)" << std::endl;
}

Book::Book(Book &&rhs) noexcept :
    no(rhs.no), name(rhs.name), author(rhs.author), pubDate(rhs.pubDate), number(rhs.number) {
    std::cout << "Book(Book &&)" << std::endl;
}

Book& Book::operator+=(const Book &rhs) {
    number += rhs.number;
    return *this;
}

Book& Book::operator-=(const Book &rhs) {
    number -= rhs.number;
    return *this;
}

Book& Book::operator=(const Book &rhs) {
    no = rhs.no;
    name = rhs.name;
    author = rhs.author;
    pubDate = rhs.pubDate;
    number = rhs.number;
    std::cout << "Book::operator=(const Book&)" << std::endl;
    return *this;
}
Book& Book::operator=(Book &&rhs) noexcept {
    no = std::move(rhs.no);
    name = std::move(rhs.name);
    author = std::move(rhs.author);
    pubDate = std::move(rhs.pubDate);
    number = std::move(rhs.number);
    std::cout << "Book::operator=(Book &&)" << std::endl;
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