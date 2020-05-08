//
// Created by wangheng on 2020/5/8.
//

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

int main() {
    bool flag = true;
    std::vector<int> vec{2,6,4,8};
    // 判断2是否能被容器内的所有元素整除
    auto count = std::count_if(vec.begin(), vec.end(),
            std::bind(std::equal_to<int>(), std::bind(std::modulus<int>(), std::placeholders::_1, 2), 0));
    if (count != vec.size())
        flag = false;
    std::cout << std::boolalpha << flag << std::endl;

    return 0;
}