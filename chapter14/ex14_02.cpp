//
// Created by wangheng on 2020/5/4.
//

#include "ex14_02.h"

Sales_data::Sales_data(std::istream &is) {
    is >> *this;
}

Sales_data& Sales_data::operator+=(const Sales_data &rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

std::istream& operator>>(std::istream& is, Sales_data& item) {
    double price = 0.0;
    is >> item.bookNo >> item.units_sold >> price;
    if (is) {
        item.revenue = price * item.units_sold;
    } else {
        item = Sales_data();
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, Sales_data& item) {
    os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.avg_price();
    return os;
}
//
// Created by wangheng on 2020/5/4.
//

#include "ex14_02.h"

Sales_data::Sales_data(std::istream &is) {
    is >> *this;
}

Sales_data& Sales_data::operator+=(const Sales_data &rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

std::istream& operator>>(std::istream& is, Sales_data& item) {
    double price = 0.0;
    is >> item.bookNo >> item.units_sold >> price;
    if (is) {
        item.revenue = price * item.units_sold;
    } else {
        item = Sales_data();
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, Sales_data& item) {
    os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.avg_price();
    return os;
}

Sales_data operator+(const Sales_data& lhs, const Sales_data& rhs) {
    Sales_data sum = lhs;
    sum += rhs;
    return sum;
}

int main() {
    Sales_data item1(std::cin);
    Sales_data item2("2", 3, 3.4);
    Sales_data sum = item1 + item2;
    std::cout << sum << std::endl;

    return 0;
}
Sales_data operator+(const Sales_data& lhs, const Sales_data& rhs) {
    Sales_data sum = lhs;
    sum += rhs;
    return sum;
}

int main() {
    Sales_data item1(std::cin);
    Sales_data item2("2", 3, 3.4);
    Sales_data sum = item1 + item2;
    std::cout << sum << std::endl;

    return 0;
}