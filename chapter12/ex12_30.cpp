//
// Created by wangheng on 2020/4/24.
//

#include <iostream>
#include "ex12_30.h"

int main()
{
    std::string filename = "E:\\code\\CLionProjects\\CPP_Primer\\data\\test.txt";
    std::ifstream infile(filename);
    TextQuery source = TextQuery(infile);
    std::string sought;
    while (true) {
        std::cout << "��������Ҫ�����ĵ��ʣ���������'q'�˳���";
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