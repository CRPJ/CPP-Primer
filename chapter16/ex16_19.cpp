//
// Created by wh969 on 2020/6/13.
//
#include <iostream>
#include <vector>

template <typename T>
void print(const T& container) {
    typename T::size_type i;
    typename T::size_type len = container.size();
    for (i = 0; i < len; ++i)
        std::cout << container[i] << ' ';
}

int main() {
    std::vector<int> ivec{1,2,3,4};
    print(ivec);

    return 0;
}