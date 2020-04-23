//
// Created by wangheng on 2020/4/23.
//

#include <iostream>
#include <memory>
#include <string>

int main() {
    std::allocator<std::string>::size_type n = 3;
    std::allocator<std::string> alloc;
    auto const p = alloc.allocate(n);
    auto q = p;
    std::string str;
    while (std::cin >> str && q != p + n) {
        alloc.construct(q++, str);
    }
    for (auto i = 0; i < n; ++i)
        std::cout << p[i] << std::endl;
    alloc.deallocate(p, n);
    return 0;
}