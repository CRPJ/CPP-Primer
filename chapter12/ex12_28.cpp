//
// Created by wangheng on 2020/4/24.
//

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include "make_plural.h"

int main()
{
    std::string filename = "E:\\code\\CLionProjects\\CPP_Primer\\data\\test.txt";
    std::ifstream infile(filename);
    if (!infile.is_open())
    {
        std::cout << "failed to open" << std::endl;
    }
    else {
        // 读取文件的内容，每行作为content的一个元素
        std::string line;
        std::vector<std::string> content;
        while (std::getline(infile, line)) {
            content.push_back(line);
        }

        // 构建每个单词和相应出现的行数组成的set的map表
        std::map<std::string, std::set<int>> wordMapToLine;
        for (auto begin = content.cbegin(); begin != content.cend(); ++begin)
        {
            std::istringstream lineContent(*begin);
            std::string word;
            while (lineContent >> word)
            {
                wordMapToLine[word].insert(begin-content.cbegin()+1);
            }
        }

        // 查询相应的单词并且输出所在行的内容
        std::string queryWord;
        while (true) {
            std::cout << "请输入要查询的单词，退出请输入q:";
            std::cin >> queryWord;
            if (queryWord != "q") {
                if (wordMapToLine.find(queryWord) != wordMapToLine.cend()) {
                    std::cout << queryWord << " occurs " << wordMapToLine[queryWord].size() <<
                              " " << make_plural(wordMapToLine[queryWord].size(), "time", "s") << std::endl;
                    for (auto iter = wordMapToLine[queryWord].cbegin();
                         iter != wordMapToLine[queryWord].cend(); ++iter) {
                        std::cout << "(line " << *iter << ") " << content[*iter - 1] << std::endl;
                    }
                } else {
                    std::cout << "没有查到单词" << queryWord << std::endl;
                }
            } else {
                break;
            }
        }
    }

    return 0;
}