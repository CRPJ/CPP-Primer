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
    StrBlobPtr begin() { return StrBlobPtr(*this); }
    StrBlobPtr end() {
        auto ret = StrBlobPtr(*this, data->size());
        return ret;
    }
private:
    std::shared_ptr<std::vector<std::string>> data;
    // 如果data[i]不合法，抛出异常
    void check(size_type i, const std::string &msg) const;
};

#endif //CPP_PRIMER_EX12_01_H
