//
// Created by wangheng on 2020/4/23.
//

#include <iostream>
#include <vector>

// 动态分配一个int的vector
std::vector<int>* construct_p(void) {
    return new std::vector<int>();
}

// 读入数据存入vector中
void read(std::vector<int>*& p) {
    int number;
    while (std::cin >> number) {
        p->push_back(number);
    }
}

// 打印vector中的值
void write(std::vector<int>*& p) {
    for (auto& iter : *p)
        std::cout << iter << '\t';
}

int main()
{
    std::vector<int>* p = construct_p();
    read(p);
    write(p);
    delete p;
    return 0;
}