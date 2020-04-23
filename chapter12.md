# 目录

| [12.01](#1201) | [12.02](#1202)  | [12.03](#1203)  | [12.04](#1204)  | [12.05](#1205)  | [12.06](#1206)  |
| -------------- | --------------- | --------------- | --------------- | --------------- | --------------- |
| [12.07](#1207) | [12.08](#1208)  | [12.09](#1209)  | [12.10](#1210)  | [12.11](#1211)  | [12.12](#1212)  |
| [12.13](#1213) | [12.14](#12.14) | [12.15](#12.15) | [12.16](#12.16) | [12.17](#12.17) | [12.18](#12.18) |
| [12.19](#1219) | [12.20](#1220)  | [12.21](#1221)  | [12.22](#1222)  | [12.23](#1223)  | [12.24](#1224)  |
| [12.25](#1225) | [12.26](#1226)  | [12.27](#1228)  | [12.28](#1228)  | [12.29](#1229)  | [12.30](#1230)  |
| [12.31](#1231) | [12.32](#1232)  | [12.33](#1233)  |                 |                 |                 |

## <span id="12.01">12.01</span>

> 在此代码的结尾，`b1`和`b2`各包含多少个元素？
>
> ```c++
> Strblob b1;
> {
>     StrBlob b2 = {"a", "an", "the"};
>     b1 = b2;
>     b2.push_back("about");
> }
> ```

在代码的结尾`b2`被销毁，`b1`有四个元素。

`StrBlob`类的声明和实现：

`StrBlob.h`

```c++
//
// Created by wangheng on 2020/4/23.
//

#ifndef CPP_PRIMER_EX12_01_H
#define CPP_PRIMER_EX12_01_H

#include <memory>
#include <vector>
#include <initializer_list>
#include <string>

class StrBlob
{
public:
    typedef std::vector<std::string>::size_type size_type;
    StrBlob();
    StrBlob(std::initializer_list<std::string> il);
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    // 添加和删除元素
    void push_back(const std::string &t) { data->push_back(t); }
    void pop_back();
    // 元素访问
    std::string &front();
    std::string &front() const;
    std::string &back();
    std::string &back() const;
private:
    std::shared_ptr<std::vector<std::string>> data;
    // 如果data[i]不合法，抛出异常
    void check(size_type i, const std::string &msg) const;
};

#endif //CPP_PRIMER_EX12_01_H

```

`StrBlob.cpp`

```c++
//
// Created by wangheng on 2020/4/23.
//

#include "ex12_01.h"
#include <stdexcept>

StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()) {}

StrBlob::StrBlob(std::initializer_list<std::string> il) :
        data(std::make_shared<std::vector<std::string>>(il)) {}

void StrBlob::check(size_type i, const std::string &msg) const {
    if (i >= data->size()) {
        throw std::out_of_range(msg);
    }
}

void StrBlob::pop_back() {
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

std::string& StrBlob::front() {
    check(0, "front on empty StrBlob");
    return data->front();
}

std::string& StrBlob::front() const {
    check(0, "front on empty StrBlob");
    return data->front();
}

std::string &StrBlob::back() {
    check(0, "back on empty StrBlob");
    return data->back();
}

std::string &StrBlob::back() const {
    check(0, "back on empty StrBlob");
    return data->back();
}
```



## <span id="12.02">12.02</span>

> 编写你自己的`StrBlob`类，包含`const`版本的`front`和`back`。

见上一题

## <span id="12.03">12.03</span>

> `StrBlob`需要`const`版本的`push_back`和`pop_back`吗？如果需要，添加进去，否则，解释为什么不需要。

不需要，`const`成员函数只能是`const`对象调用，但是`const`对象不允许更改，所以不需要`push_back`和`pop_back`。

## <span id="12.04">12.04</span>

> 在我们的check函数中，没有检查i是否大于0。为什么可以忽略这个检查？

因为`check`是私有成员函数，只能被`StrBlob`的成员函数调用，不能被用户程序调用，我们可以很容易地保证传给`i`的值符合要求，不必进行检查。

## <span id="12.05">12.05</span>

> 我们未编写接受一个`initializer_list explicit`参数的构造函数。讨论这个设计策略的优点和缺点。

未编写接受一个`initializer_list`参数的显示构造函数，意味着可以进行列表项`StrBlob`的隐式转换。在需要`StrBlob`的地方可以用列表代替，使程序编写更加方便，但是列表中可能并非都是合法的值。

## <span id="12.06">12.06</span>

>  编写函数，返回一个动态分配的`int`的`vector`。将此`vector`传递给另一个函数，这个函数读取标准输入，将输入的值保存在`vector`元素中。再将`vector`传递给另一个函数，打印读入的值。记得在恰当的时刻`delete vector`。

```c++
//
// Created by wangheng on 2020/4/23.
//

#include <iostream>
#include <vector>

// 动态分配一个int的vector
std::vector<int>* construct_p(void) {
    return new std::vector<int>();
}

// 读入数据存入vector中
void read(std::vector<int>*& p) {
    int number;
    while (std::cin >> number) {
        p->push_back(number);
    }
}

// 打印vector中的值
void write(std::vector<int>*& p) {
    for (auto& iter : *p)
        std::cout << iter << '\t';
}

int main()
{
    std::vector<int>* p = construct_p();
    read(p);
    write(p);
    delete p;
    return 0;
}
```



## <span id="12.07">12.07</span>

> 重做上一题，这次试用`shared_ptr`而不是内置指针。

```c++
//
// Created by wangheng on 2020/4/23.
//

#include <iostream>
#include <memory>
#include <vector>

std::shared_ptr<std::vector<int>> construct_p(void) {
    return std::make_shared<std::vector<int>>();
}

void read(std::shared_ptr<std::vector<int>>& p) {
    int number;
    while (std::cin >> number) {
        p->push_back(number);
    }
}

void write(std::shared_ptr<std::vector<int>>& p) {
    for (auto& iter : *p)
        std::cout << iter << '\t';
}

int main()
{
    std::shared_ptr<std::vector<int>> sp = construct_p();
    read(sp);
    write(sp);
    return 0;
}
```



## <span id="12.08">12.08</span>

> 下面的函数是否有错误？如果有，解释错误原因。
>
> ```c++
> bool b() {
>     int* p = new int;
>     // ...
>     return p;
> }
> ```

依赖于内存分配成功与否返回`true`或`false`，但是用`new`分配动态内存失败会抛出异常，而不是返回空指针。应该使用`int* p = new(nothrow) int;`

## <span id="12.09">12.09</span>

> 解释下面代码执行的结果：
>
> ```c++
> int *q = new int(42), *r = new int(100);
> r = q;	// r原来管理的内存再无指针管理，造成内存泄漏。
> auto q2 = make_shared<int>(42), r2 = make_shared<int>(100);
> r2 = q2;	// 定义q2和r2时，二者的引用计数均为1，将q2赋值给r2，q2的引用计数加1变为2，r2的引用计数减1，r2指向的内存自动释放。
> 
> // 显然，使用智能指针管理动态内存可以不用手动释放内存，用内置指针管理动态内存极容易造成内存泄漏和空悬指针。
> ```

## <span id="12.10">12.10</span>

> 下面的代码调用了第413页中定义的`process`函数，解释此调用是否正确。如果不正确，应如何修改。
>
> ```c++
> shared_pre<int> p(new int(42));
> process(shared_ptr<int>(p));
> ```

正确。利用`p`创建一个临时的`shared_ptr`赋予`process`的参数`ptr`，`p`和`ptr`都指向相同的`int`对象，引用计数被置位2，`process`的调用结束后，`ptr`被销毁，引用计数减为1，此时只有唯一的`p`指向它。

## <span id="12.11">12.11</span>

> 如果我们像下面这样调用`process`，会发生什么？
>
> ```c++
> process(shared_ptr<int>(p.get()));
> ```

`get`函数返回一个内置指针，指向智能指针管理的对象。

`p.get()`返回一个内置指针，指向p所共享的int对象。利用此指针创建一个`shared_ptr`而不是用`p`创建一个`shared_ptr`，将不会形成正确的对象共享，会构造一个独立的智能指针。编译器认为`p`和`ptr`是两个地址（虽然它们相等）创建了两个不同的`shared_ptr`，而非共享同一个动态对象。这样二者的引用计数均为1。当`process`执行后，`ptr`的引用计数减为0，所管理的内存被释放，而此内存也是`p`管理的，p成为一个管理空悬指针的`shared_ptr`。

## <span id="12.12">12.12</span>

> `p`和`sp`的定义如下，对于接下来的对`process`的每个调用，如果合法，解释它做了什么，如果不合法，解释错误原因：
>
> ```c++
> auto p = new int();
> auto sp = shared_ptr<int>();
> (a)process(sp);		// 合法
> (b)process(new int());	// 不合法，process需要shared_ptr参数，不能将int*转换为一个shared_ptr
> (c)process(p);	// 不合法，不能将int*转换为shared_ptr
> (d)process(shared_ptr<int>(p));		//合法，利用p构造了一个shared_ptr
> ```
>
> 

## <span id="12.13">12.13</span>

> 如果执行下面的代码，会发生什么？
>
> ```c++
> auto sp = make_shared_ptr<int>();
> auto p = sp.get();	// get函数返回一个内置指针，指向sp管理的对象
> delete p;	// sp和p指向同一块内存，delete p之后，sp成为空悬指针
> ```

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

更倾向于while版本，因为do while至少要执行一次循环，while版本可以随时终止循环。

## <span id="12.30">12.30</span>

将所有类写在同一个文件里。

```c++
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <memory>

class QueryResult
{
    friend std::ostream& print(std::ostream&, const QueryResult&);

public:
    using line_no = std::vector<std::string>::size_type;
    QueryResult(std::string s,
                std::shared_ptr<std::set<line_no>> p,
                std::shared_ptr<std::vector<std::string>> f) :
                sought(s), lines(p), file(f) {}
private:
    std::string sought;
    std::shared_ptr<std::set<line_no>> lines;
    std::shared_ptr<std::vector<std::string>> file;
};
class TextQuery
{
public:
    using line_no = std::vector<std::string>::size_type;
    TextQuery(std::ifstream&);
    QueryResult query(const std::string&) const;

private:
    std::shared_ptr<std::vector<std::string>> file;
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

TextQuery::TextQuery(std::ifstream &is) : file(new std::vector<std::string>)
{
    std::string text;
    while (std::getline(is, text))
    {
        file->push_back(text);
        int n = file->size() - 1;
        std::istringstream line(text);
        std::string word;
        while (line >> word)
        {
            auto &lines = wm[word];
            if (!lines)
            {
                lines.reset(new std::set<line_no>);
            }
            lines->insert(n);
        }
    }
}

QueryResult
TextQuery::query(const std::string &sought) const {
    static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
    auto loc = wm.find(sought);
    if (loc == wm.end())
    {
        return QueryResult(sought, nodata, file);
    } else
    {
        return QueryResult(sought, loc->second, file);
    }
}

std::ostream &print(std::ostream& os, const QueryResult& qr)
{
    os << qr.sought << " occurs " << qr.lines->size() << " times." << std::endl;
    for (auto num : *qr.lines)
    {
        os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num) << std::endl;
    }
    return os;
}

int main()
{
    std::string filename = "E:\\code\\CLionProjects\\TextQuery\\test.txt";
    std::ifstream infile(filename);
    TextQuery source = TextQuery(infile);
    QueryResult result = source.query("a");
    print(std::cout, result);

    return 0;
}
```

将类和实现分开

QueryResult.h

```c++
//
// Created by wangheng on 2020/4/18.
//

#ifndef TEXTQUERY_QUERYRESULT_H
#define TEXTQUERY_QUERYRESULT_H
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <memory>

class QueryResult {
    friend std::ostream& print(std::ostream&, const QueryResult&);

public:
    using line_no = std::vector<std::string>::size_type;
    QueryResult(std::string s,
            std::shared_ptr<std::set<line_no>> p,
            std::shared_ptr<std::vector<std::string>> f) :
            sought(s), lines(p), file(f) {}
private:
    std::string sought;
    std::shared_ptr<std::set<line_no>> lines;
    std::shared_ptr<std::vector<std::string>> file;
};


#endif //TEXTQUERY_QUERYRESULT_H

```

QueryResult.cpp

```c++
//
// Created by wangheng on 2020/4/18.
//

#include "QueryResult.h"
#include "make_plural.h"

std::ostream& print(std::ostream& os, const QueryResult& qr)
{
    os << qr.sought << " occurs " << qr.lines->size() << " " <<
        make_plural(qr.lines->size(), "time", "s") << std::endl;
    for (auto num : *qr.lines)
    {
        os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num) << std::endl;
    }
    return os;
}
```

TextQuery.h

```c++
//
// Created by wangheng on 2020/4/18.
//

#ifndef TEXTQUERY_TEXTQUERY_H
#define TEXTQUERY_TEXTQUERY_H
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include "QueryResult.h"

class TextQuery {
public:
    using line_no = std::vector<std::string>::size_type;
    TextQuery(std::ifstream&);
    QueryResult query(const std::string&) const;

private:
    std::shared_ptr<std::vector<std::string>> file;
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};


#endif //TEXTQUERY_TEXTQUERY_H

```

TextQuery.cpp

```c++
//
// Created by wangheng on 2020/4/18.
//

#include "TextQuery.h"
TextQuery::TextQuery(std::ifstream &is) : file(new std::vector<std::string>) {
    std::string text;
    while (std::getline(is, text))
    {
        file->push_back(text);
        int n = file->size() - 1;
        std::istringstream line(text);
        std::string word;
        while (line >> word)
        {
            auto& lines = wm[word];
            if (!lines)
                lines.reset(new std::set<line_no>);
            lines->insert(n);
        }
    }
}

QueryResult TextQuery::query(const std::string &sought) const {
    static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
    auto loc = wm.find(sought);
    if(loc == wm.cend())
    {
        return QueryResult(sought, nodata, file);
    } else {
        return QueryResult(sought, loc->second, file);
    }
}
```

make_plural.h

```c++
//
// Created by wangheng on 2020/4/18.
//

#ifndef TEXTQUERY_MAKE_PLURAL_H
#define TEXTQUERY_MAKE_PLURAL_H
#include <string>
inline
std::string make_plural(std::size_t ctr, const std::string& word, const std::string ending)
{
    return (ctr == 1) ? word : word+ending;
}
#endif //TEXTQUERY_MAKE_PLURAL_H

```

main.cpp

```c++
#include <iostream>
#include "QueryResult.h"
#include "TextQuery.h"

int main()
{
    std::string filename = "E:\\code\\CLionProjects\\TextQuery\\test.txt";
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
```

## <span id="12.31">12.31</span>

vector允许元素重复，所以如果一个单词在某行中重复出现多次会导致重复计算，而set不会重复计数。所以当需要重复记录单词在某行中出现的次数的时候可以选择vector，但是在本题中要求不能重复计数，所以应该使用set。

## <span id="12.32">12.32</span>

## <span id="12.33">12.33</span>