//
// Created by wangheng on 2020/5/8.
//

#include <iostream>
#include <map>
#include <functional>
#include <string>

int add(int i, int j) { return i + j; }
auto mod = [](int i, int j) { return i % j; };
struct Div {int operator()(int i, int j) { return i / j; }};

auto binops = std::map<std::string, std::function<int(int, int)>> {
        {"+", add},                         // function pointer
        {"-", std::minus<int>()},       //library functor
        {"/", Div()},                   // user-defined functor
        {"*", [](int i, int j) { return i * j; }},   //unnamed lambda
        {"%", mod}                          // named lambda
};

int main() {
    while (std::cout << "Please enter as: num operator num: \n", true) {
        int lhs, rhs;
        std::string op;
        std::cin >> lhs >> op >> rhs;
        std::cout << binops[op](lhs, rhs) << std::endl;
    }
    return 0;
}