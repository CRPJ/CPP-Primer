//
// Created by wangheng on 2020/4/23.
//

#ifndef CPP_PRIMER_EX12_22_H
#define CPP_PRIMER_EX12_22_H

#include <vector>
#include <memory>
#include <stdexcept>
#include <string>
#include <initializer_list>

class ConstStrBlobPtr;

class StrBlob {
public:
    friend class ConstStrBlobPtr;
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
    ConstStrBlobPtr begin();
    ConstStrBlobPtr end();
    ConstStrBlobPtr cbegin() const ;
    ConstStrBlobPtr cend() const ;
private:
    std::shared_ptr<std::vector<std::string>> data;
    // 如果data[i]不合法，抛出异常
    void check(size_type i, const std::string &msg) const;
};

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

class ConstStrBlobPtr {
public:
    using size_t = std::vector<std::string>::size_type;
    ConstStrBlobPtr() : curr(0) {}
    // 使用StrBlob的引用避免拷贝
    ConstStrBlobPtr(StrBlob& a, size_t sz = 0) : wptr(a.data), curr(sz) {}
    ConstStrBlobPtr(const StrBlob& a, size_t sz = 0) : wptr(a.data), curr(sz) {}
    bool operator!=(const ConstStrBlobPtr& p) { return p.curr != curr; }
    std::string &dref() const ;
    ConstStrBlobPtr& incr();     // 递增前缀

    // ConstStrBlobPtr数据成员指向const vector，不能更改，所以返回值应该是const类型
    const std::string& operator*() const ;
    const std::string* operator->() const ;
private:
    // 若检查成功，check返回一个指向vector的shared_ptr
    std::shared_ptr<std::vector<std::string>>
    check(std::size_t, const std::string&) const;
    // 保存一个waek_ptr，意味着底层vector可能被销毁
    std::weak_ptr<std::vector<std::string>> wptr;
    size_t curr;   // 在数组中当前的位置
};

std::string& ConstStrBlobPtr::dref() const {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

ConstStrBlobPtr& ConstStrBlobPtr::incr() {
    // 如果curr已经指向容器的尾后位置，就不能递增它
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

std::shared_ptr<std::vector<std::string>>
ConstStrBlobPtr::check(std::size_t i, const std::string &msg) const {
    auto ret = wptr.lock();
    if (!ret)
        throw std::runtime_error("unbound StrBlobPtr");
    if (i >= ret->size())
        throw std::out_of_range(msg);
    return ret;
}

ConstStrBlobPtr StrBlob::begin() {
    return ConstStrBlobPtr(*this);
}

ConstStrBlobPtr StrBlob::end() {
    auto ret = ConstStrBlobPtr(*this, data->size());
    return ret;
}

ConstStrBlobPtr StrBlob::cbegin() const {
    return ConstStrBlobPtr(*this);
}

ConstStrBlobPtr StrBlob::cend() const {
    auto ret = ConstStrBlobPtr(*this, data->size());
    return ret;
}

const std::string& ConstStrBlobPtr::operator*() const {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

const std::string* ConstStrBlobPtr::operator->() const {
    return &this->operator*();
}

#endif //CPP_PRIMER_EX12_22_H
