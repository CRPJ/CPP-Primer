//
// Created by wangheng on 2020/4/25.
//

#include <iostream>
#include "ex13_42.h"

int main()
{
    std::string filename = "E:\\code\\CLionProjects\\CPP_Primer\\data\\test.txt";
    std::ifstream infile(filename);
    TextQuery source = TextQuery(infile);
    std::string sought;
    while (true) {
        std::cout << "请输入你要搜索的单词，或者输入'q'退出：";
        std::cin >> sought;
        if (sought == "q")
            break;
        else {
            QueryResult result = source.query(sought);
            print(std::cout, result);
        }
    }

    return 0;
}