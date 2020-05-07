//
// Created by wangheng on 2020/5/7.
//

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>

class GetLength {
public:
    GetLength(std::size_t n) : sz(n) {}
    bool operator()(const std::string& s) {
        return s.size() == sz;
    }

private:
    std::size_t sz;
};

int main() {
    std::ifstream infile("C:\\Users\\wh969\\Desktop\\code\\CPP-Primer\\data\\ex14_38.txt", std::ios::in);
    std::vector<std::string> words;
    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream line_words(line);
        std::string word;
        while (line_words >> word)
            words.push_back(word);
    }

    // 对words按长度从小到大排序
    std::stable_sort(words.begin(), words.end(),
                     [] (const std::string& s1, const std::string& s2) {return s1.size() < s2.size();});

    // 计算words中最长的string的长度
    std::size_t maxLength = (words.end() - 1)->size();

    for (std::size_t i = 1; i <= maxLength; ++i) {
        auto number = std::count_if(words.begin(), words.end(), GetLength(i));
        std::cout << "Length " << i << ": " << number << std::endl;
        auto first = std::find_if(words.begin(), words.end(), GetLength(i));
        for (auto iter = first; iter != first + number; ++iter)
            std::cout << *iter << ' ';
        std::cout << std::endl;
    }

    return 0;
}