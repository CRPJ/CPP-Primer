//
// Created by wangheng on 2020/6/10.
//

#include "ex16_14.h"
#include <iostream>

int main() {
    Screen<10, 10> screen('a');
    screen.move(4,5);
    std::cout << screen;
    screen.set('m');
    std::cout << screen.get() << std::endl;
    return 0;
}