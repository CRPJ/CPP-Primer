//
// Created by wangheng on 2020/5/7.
//

#include <iostream>
#include <algorithm>
#include <vector>

class IsEqual {
public:
    IsEqual(int v) :value(v) {}
    bool operator()(int elem) {
        return value == elem;
    }

private:
    int value;
};

int main() {
    std::vector<int> vec{3, 2, 1, 4, 3, 7};
    std::replace_if(vec.begin(), vec.end(), IsEqual(3), 5);
    for (int i : vec)
        std::cout << i << ' ';
    std::cout << std::endl;

    return 0;
}