//
// Created by wangheng on 2020/4/23.
//

#include <iostream>
#include <memory>
#include <vector>

std::shared_ptr<std::vector<int>> construct_p(void) {
    return std::make_shared<std::vector<int>>();
}

void read(std::shared_ptr<std::vector<int>>& p) {
    int number;
    while (std::cin >> number) {
        p->push_back(number);
    }
}

void write(std::shared_ptr<std::vector<int>>& p) {
    for (auto& iter : *p)
        std::cout << iter << '\t';
}

int main()
{
    std::shared_ptr<std::vector<int>> sp = construct_p();
    read(sp);
    write(sp);
    return 0;
}