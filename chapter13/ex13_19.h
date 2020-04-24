//
// Created by wangheng on 2020/4/24.
//

#ifndef CPP_PRIMER_EX13_19_H
#define CPP_PRIMER_EX13_19_H

#include <string>

class Employee {
public:
    Employee();
    Employee(std::string&);
    Employee(const Employee&) = delete ;
    Employee& operator=(const Employee&) = delete ;
    const int getId() const { return id; }

private:
    std::string name;
    int id;
    static int basicNumber;
};

int Employee::basicNumber = 0;
Employee::Employee() : name(std::string("null")), id(basicNumber++) {}
Employee::Employee(std::string &s) : name(s), id(basicNumber++) {}

#endif //CPP_PRIMER_EX13_19_H
