//
// Created by wangheng on 2020/6/7.
//

#include <iostream>
#include "basket.h"
#include "ex15_26_2.h"

int main() {
    Basket basket;
    basket.add_item(Bulk_quote("1234", 4.5, 100, 0.2));
    basket.add_item(Quote("12321", 5.6));
    Bulk_quote item("1234", 4.5, 100, 0.2);
    basket.add_item(item);
    basket.total_receipt(std::cout);

    return 0;
}