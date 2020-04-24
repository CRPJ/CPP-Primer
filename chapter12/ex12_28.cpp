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
        // ��ȡ�ļ������ݣ�ÿ����Ϊcontent��һ��Ԫ��
        std::string line;
        std::vector<std::string> content;
        while (std::getline(infile, line)) {
            content.push_back(line);
        }

        // ����ÿ�����ʺ���Ӧ���ֵ�������ɵ�set��map��
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

        // ��ѯ��Ӧ�ĵ��ʲ�����������е�����
        std::string queryWord;
        while (true) {
            std::cout << "������Ҫ��ѯ�ĵ��ʣ��˳�������q:";
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
                    std::cout << "û�в鵽����" << queryWord << std::endl;
                }
            } else {
                break;
            }
        }
    }

    return 0;
}