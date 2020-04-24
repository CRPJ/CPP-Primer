//
// Created by wangheng on 2020/4/24.
//

#include <iostream>

int main() {
    std::cout << "How long do you want the string? ";
    std::size_t size{0};
    std::cin >> size;
    char *p = new char[size+1]();
    std::cin.ignore();
    std::cout << "input the string: ";
    std::cin.get(p, size + 1);  // 指定读入的字符数
    std::cout << p << std::endl;

    delete [] p;

    return 0;
}