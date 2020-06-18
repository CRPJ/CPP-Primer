#include <iostream>
#include "shared_ptr.h"
#include "unique_ptr.h"

int main() {
    cp5::SharedPointer<int> ptr1(new int (10));
    cp5::SharedPointer<int> ptr2(ptr1);
    cp5::SharedPointer<int> ptr3(new int (9));
    cp5::SharedPointer<int> ptr4(ptr3);
    std::cout << ptr4.use_count() << std::endl;
    ptr3 = ptr2;
    std::cout << *ptr1 << ' ' << ptr2.use_count() << std::endl;
    std::cout << ptr4.use_count() << std::endl;

    UniquePointer<int> uptr1(new int (3));
    std::cout << *uptr1 << std::endl;

    return 0;
}