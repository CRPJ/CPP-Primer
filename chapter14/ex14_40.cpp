//
// Created by wangheng on 2020/5/7.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

class ShorterString {
public:
    bool operator()(const std::string& s1, const std::string& s2) const {
        return s1.size() < s2.size();
    }
};

class BiggerEqual {
public:
    BiggerEqual(std::size_t n) : sz(n) {}
    bool operator()(const std::string& s) {
        return s.size() >= sz;
    }

private:
    std::size_t sz;
};

class Printer {
public:
    Printer(std::ostream& os = std::cout, std::string str = " ") :
        os(os), str(str) {}
    void operator()(const std::string& s) {
        os << s << str;
    }

private:
    std::ostream& os;
    std::string str;
};

std::string make_plural(std::size_t ctr, const std::string &word, const std::string& ending) {
    return (ctr > 1) ? word + ending : word;
}

// 将wors按字典顺序排序，删除重复单词
void elimDups(std::vector<std::string>& words) {
    std::sort(words.begin(), words.end());
    auto end_unique = std::unique(words.begin(), words.end());
    words.erase(end_unique, words.end());
}

void biggies(std::vector<std::string>& words, std::vector<std::string>::size_type sz) {
    elimDups(words);
    std::stable_sort(words.begin(), words.end(), ShorterString());
    auto wc = std::find_if(words.begin(), words.end(), BiggerEqual(sz));
    auto count = words.end() - wc;
    std::cout << count << " " << make_plural(count, "word", "s")
        << " of length " << sz << " or longer" << std::endl;
    std::for_each(wc, words.end(), Printer());
    std::cout << std::endl;
}

int main() {
    std::vector<std::string> words = {"an", "the", "good", "football", "bike", "Chinese"};
    biggies(words, 5);

    return 0;
}