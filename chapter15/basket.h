//
// Created by wangheng on 2020/6/7.
//

#ifndef CPP_PRIMER_BASKET_H
#define CPP_PRIMER_BASKET_H

#include <memory>
#include <set>
#include "ex15_26.h"
#include "print_total.h"

class Basket{
public:
    void add_item(const Quote& sale) {
        items.insert(std::shared_ptr<Quote>(sale.clone()));
    }
    void add_item(Quote &&sale) {
        items.insert(std::shared_ptr<Quote>(std::move(sale).clone()));
    }

    double total_receipt(std::ostream& os) const {
        double sum = 0.0;
        for (auto iter = items.cbegin(); iter != items.cend(); iter = items.upper_bound(*iter)) {
            sum += print_total(os, **iter, items.count(*iter));
        }
        os << "Total sale: " << sum << std::endl;

        return sum;
    }

private:
    static bool compare(const std::shared_ptr<Quote> &lhs, const std::shared_ptr<Quote>& rhs) {
        return lhs->isbn() < rhs->isbn();
    }
    std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items{compare};
};

#endif //CPP_PRIMER_BASKET_H
