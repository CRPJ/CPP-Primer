# 目录

| [12.01](#12.01) | [12.02](#12.02) | [12.03](#12.03) | [12.04](#12.04) | [12.05](#12.05) | [12.06](#12.06) |
| --------------- | --------------- | --------------- | --------------- | --------------- | --------------- |
| [12.07](#12.07) | [12.08](#12.08) | [12.09](#12.09) | [12.10](#12.10) | [12.11](#12.11) | [12.12](#12.12) |
| [12.13](#12.13) | [12.14](#12.14) | [12.15](#12.15) | [12.16](#12.16) | [12.17](#12.17) | [12.18](#12.18) |
| [12.19](#12.19) | [12.20](#12.20) | [12.21](#12.21) | [12.22](#12.22) | [12.23](#12.23) | [12.24](#12.24) |
| [12.25](#12.25) | [12.26](#12.26) | [12.27](#12.28) | [12.28](#12.28) | [12.29](#12.29) | [12.30](#12.30) |
| [12.31](#12.31) | [12.32](#12.32) | [12.33](#12.33) |                 |                 |                 |

## <span id="12.01">12.01</span>

## <span id="12.02">12.02</span>

## <span id="12.03">12.03</span>

## <span id="12.04">12.04</span>

## <span id="12.05">12.05</span>

## <span id="12.06">12.06</span>

## <span id="12.07">12.07</span>

## <span id="12.08">12.08</span>

## <span id="12.09">12.09</span>

## <span id="12.10">12.10</span>

## <span id="12.11">12.11</span>

## <span id="12.12">12.12</span>

## <span id="12.13">12.13</span>

## <span id="12.14">12.14</span>

## <span id="12.15">12.15</span>

## <span id="12.16">12.16</span>

## <span id="12.17">12.17</span>

## <span id="12.18">12.18</span>

## <span id="12.19">12.19</span>

## <span id="12.20">12.20</span>

## <span id="12.21">12.21</span>

## <span id="12.22">12.22</span>

## <span id="12.23">12.23</span>

## <span id="12.24">12.24</span>

## <span id="12.25">12.25</span>

## <span id="12.26">12.26</span>

## <span id="12.27">12.27</span>

> TextQuery和QueryResult类只使用了我们已经介绍过的语言和标准库特性。不要提前看后续章节内容，只用已经学到的知识对这两个类编写你自己的版本。

## <span id="12.28">12.28</span>

> 编写程序实现文本查询，不要定义类来管理数据。你的程序应该接受一个文件，并与用户交互来查询单词。使用vector、map和set容器来保存来自文件的数据并生成查询结果。

```c++
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <sstream>

int main()
{
    std::string filename = "E:\\code\\CLionProjects\\test\\test.txt";
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
                              " times." << std::endl;
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
```

## <span id="12.29">12.29</span>

## <span id="12.30">12.30</span>

## <span id="12.31">12.31</span>

## <span id="12.32">12.32</span>

## <span id="12.33">12.33</span>