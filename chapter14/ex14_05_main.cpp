//
// Created by wangheng on 2020/5/5.
//

#include "ex14_05.h"

int main() {
    Book book1(123, "Journey to the West", "Chengen Wu", "Ming dynasty");
    Book book2(123, "西游记", "吴承恩", "明朝");
    std::cout << book1 << ' ' << book2 << std::endl;
    std::cout << std::boolalpha << (book1 == book2) << std::endl;
    Book book3(std::cin);
    std::cout << (book2 == book3) << std::endl;
    std::cout << (book2 < book3) << std::endl;

    return 0;
}