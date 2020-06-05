//
// Created by wangheng on 2020/6/5.
//

#include "ex15_26.h"
#include "ex15_26_1.h"
#include "ex15_26_2.h"

int main() {
    Quote quote1;
    Disk_quote disk1;
    Bulk_quote bulk1;
    Quote quote2("123", 2.3);
    Disk_quote disk2("1234", 3.4, 45, 0.23);
    Bulk_quote bulk2("12345", 4.5, 25, 0.13);
    Quote quote3(quote2);
    Disk_quote disk3(disk2);
    Bulk_quote bulk3(bulk2);
    quote3 = quote1;
    disk3 = disk1;
    bulk3 = bulk1;
    quote3 = std::move(quote2);
    disk3 = std::move(disk2);
    bulk3 = std::move(bulk2);
    Quote quote4(std::move(quote3));
    Disk_quote disk4(std::move(disk3));
    Bulk_quote bulk4(std::move(bulk3));

    return 0;
}