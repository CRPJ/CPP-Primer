//
// Created by wangheng on 2020/5/7.
//

#include <iostream>
#include <string>

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
    std::cout << printer() << std::endl;

    return 0;
}