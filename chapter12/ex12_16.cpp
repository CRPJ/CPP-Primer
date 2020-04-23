//
// Created by wangheng on 2020/4/23.
//

#include <iostream>
#include <memory>

int main() {
    std::unique_ptr<int> up(new int(3));
    auto uq = up;
    return 0;
}