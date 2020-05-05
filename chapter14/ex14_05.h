//
// Created by wangheng on 2020/5/5.
//

#ifndef CPP_PRIMER_EX14_05_H
#define CPP_PRIMER_EX14_05_H

#include <iostream>
#include <string>

class Book {
    friend std::istream& operator>>(std::istream&, Book&);
    friend std::ostream& operator<<(std::ostream&, const Book&);
    friend bool operator==(const Book&, const Book&);
    friend bool operator!=(const Book&, const Book&);

public:
    Book() = default;
    Book(unsigned no, std::string name, std::string author, std::string pubDate) :
        no(no), name(name), author(author), pubDate(pubDate) {}
    Book(std::istream& in) {in >> *this;}

private:
    unsigned no;
    std::string name;
    std::string author;
    std::string pubDate;
};

std::istream& operator>>(std::istream&, Book&);
std::ostream& operator<<(std::ostream&, const Book&);
bool operator==(const Book&, const Book&);
bool operator!=(const Book&, const  Book&);

#endif //CPP_PRIMER_EX14_05_H
