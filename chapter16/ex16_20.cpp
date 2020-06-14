//
// Created by wh969 on 2020/6/13.
//
#include <iostream>
#include <vector>

template <typename T>
void print(const T &container) {
    for (auto iter = container.begin(); iter != container.end(); ++iter)
        std::cout << *iter << ' ';
}

int main() {
    std::vector<int> ivec =  {1,2,3,9};
    print(ivec);

    return 0;
}