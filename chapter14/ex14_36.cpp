//
// Created by wangheng on 2020/5/7.
//

#include <iostream>
#include <string>
#include <vector>

class PrintString {
public:
    PrintString(std::istream& is = std::cin) : is(is) {}
    std::string operator()() const {
        std::string str;
        std::getline(is, str);
        return is ? str : std::string();
    }

private:
    std::istream& is;
};

int main() {
    PrintString printer;
    std::vector<std::string> sv;
    for (std::string temp; !(temp = printer()).empty(); )
        sv.push_back(temp);
    for (const auto &str : sv)
        std::cout << str << ' ';
    std::cout << std::endl;

    return 0;
}