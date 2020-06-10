//
// Created by wangheng on 2020/6/10.
//

#include <iostream>
#include <functional>

template<typename T>
int compare(const T& v1, const T& v2) {
    if (std::less<T>()(v1, v2)) return -1;
    if (std::less<T>()(v2, v1)) return 1;
    return 0;
}

int main() {
    std::cout << compare("hello", "world") << std::endl;

    return 0;
}