//
// Created by wangheng on 2020/6/10.
//

#include <iostream>
#include <vector>
#include <list>
#include <string>

template<typename Iterator, typename Value>
Iterator find(Iterator begin, Iterator end, const Value& v) {
    for (; begin != end; ++begin) {
        if (*begin == v) break;
    }
    return begin;
}

int main() {
    std::vector<int> nums{1,2,3,4};
    std::cout << "2 occurs at index " << find(nums.begin(), nums.end(), 2) - nums.begin() + 1 << std::endl;
    std::list<int> l{2,3,4,5};
    auto p = find(l.begin(), l.end(), 5);
    std::cout << *p << std::endl;
    return 0;
}