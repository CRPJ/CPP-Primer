//
// Created by wangheng on 2020/5/6.
//

#ifndef CPP_PRIMER_EX14_15_H
#define CPP_PRIMER_EX14_15_H

#include <iostream>
#include <string>

class Book {
    friend std::istream& operator>>(std::istream&, Book&);
    friend std::ostream& operator<<(std::ostream&, const Book&);
    friend bool operator==(const Book&, const Book&);
    friend bool operator!=(const Book&, const Book&);
    friend bool operator<(const Book&, const Book&);
    friend bool operator>(const Book&, const Book&);
    friend Book operator+(const Book&, const Book&);
    friend Book operator-(const Book&, const Book&);

public:
    Book() = default;
    Book(unsigned no, std::string name, std::string author, std::string pubDate, unsigned number) :
            no(no), name(name), author(author), pubDate(pubDate), number(number) {}
    Book(std::istream& in) {in >> *this;}
    Book& operator+=(const Book&);
    Book& operator-=(const Book&);

private:
    unsigned no;
    std::string name;
    std::string author;
    std::string pubDate;
    unsigned number = 0;
};

std::istream& operator>>(std::istream&, Book&);
std::ostream& operator<<(std::ostream&, const Book&);
bool operator==(const Book&, const Book&);
bool operator!=(const Book&, const  Book&);
bool operator<(const Book&, const Book&);
bool operator>(const Book&, const Book&);
Book operator+(const Book&, const Book&);
Book operator-(const Book&, const Book&);

#endif //CPP_PRIMER_EX14_15_H
