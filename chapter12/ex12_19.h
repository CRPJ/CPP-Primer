//
// Created by wangheng on 2020/4/23.
//

#ifndef CPP_PRIMER_EX12_19_H
#define CPP_PRIMER_EX12_19_H

#include <vector>
#include <memory>
#include <stdexcept>
#include <string>
#include <initializer_list>

class StrBlobPtr;

class StrBlob {
    friend bool operator==(const StrBlob&, const StrBlob&);
    friend bool operator!=(const StrBlob&, const StrBlob&);
    friend bool operator<(const StrBlob&, const StrBlob&);

public:
    friend class StrBlobPtr;
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
    StrBlobPtr begin();
    StrBlobPtr end();
    int count() { return data.use_count(); }
    std::string& operator[](std::size_t n);
    const std::string& operator[](std::size_t n) const ;

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

std::string& StrBlob::operator[](std::size_t n) {
    return (*data)[n];
}

const std::string& StrBlob::operator[](std::size_t n) const {
    return (*data)[n];
}

bool operator==(const StrBlob& lhs, const StrBlob& rhs) {
    return *lhs.data == *rhs.data;
}

bool operator!=(const StrBlob& lhs, const StrBlob& rhs) {
    return *lhs.data != *rhs.data;
}

bool operator<(const StrBlob& lhs, const StrBlob& rhs){
    return *lhs.data < *rhs.data;
}

class StrBlobPtr {
    friend bool operator==(const StrBlobPtr&, const StrBlobPtr&);
    friend bool operator!=(const StrBlobPtr&, const StrBlobPtr&);
    friend bool operator<(const StrBlobPtr&, const StrBlobPtr&);
public:
    using size_t = std::vector<std::string>::size_type;
    StrBlobPtr() : curr(0) {}
    // 使用StrBlob的引用避免拷贝
    StrBlobPtr(StrBlob& a, size_t sz = 0) : wptr(a.data), curr(sz) {}
    bool operator!=(const StrBlobPtr& p) { return p.curr != this->curr; }
    std::string &dref() const ;
    StrBlobPtr& incr();     // 递增前缀
    std::string& operator[](std::size_t n);
    const std::string& operator[](std::size_t n) const ;
    StrBlobPtr& operator++();   // 前置递增运算符
    StrBlobPtr operator++(int); // 后置递增运算符
    StrBlobPtr& operator--();   // 前置递减运算符
    StrBlobPtr operator--(int); // 后置递减运算符
private:
    // 若检查成功，check返回一个指向vector的shared_ptr
    std::shared_ptr<std::vector<std::string>>
        check(std::size_t, const std::string&) const;
    // 保存一个waek_ptr，意味着底层vector可能被销毁
    std::weak_ptr<std::vector<std::string>> wptr;
    size_t curr;   // 在数组中当前的位置
};

std::string& StrBlobPtr::dref() const {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

StrBlobPtr& StrBlobPtr::incr() {
    // 如果curr已经指向容器的尾后位置，就不能递增它
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

std::shared_ptr<std::vector<std::string>>
StrBlobPtr::check(std::size_t i, const std::string &msg) const {
    auto ret = wptr.lock();
    if (!ret)
        throw std::runtime_error("unbound StrBlobPtr");
    if (i >= ret->size())
        throw std::out_of_range(msg);
    return ret;
}

StrBlobPtr StrBlob::begin(){
    return StrBlobPtr(*this);
}

StrBlobPtr StrBlob::end(){
    auto ret = StrBlobPtr(*this, data->size());
    return ret;
}

std::string& StrBlobPtr::operator[](std::size_t n) {
    return (*wptr.lock())[n];
}

const std::string& StrBlobPtr::operator[](std::size_t n) const {
    return (*wptr.lock())[n];
}

StrBlobPtr& StrBlobPtr::operator++() {
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

StrBlobPtr StrBlobPtr::operator++(int) {
    StrBlobPtr ret = *this;
    ++*this;
    return ret;
}

StrBlobPtr& StrBlobPtr::operator--() {
    --curr;
    check(curr, "decrement past begin of StrBlobPtr");
    return *this;
}

StrBlobPtr StrBlobPtr::operator--(int) {
    StrBlobPtr ret = *this;
    --*this;
    return ret;
}

bool operator==(const StrBlobPtr& lhs, const StrBlobPtr& rhs) {
    return *lhs.wptr.lock() == *rhs.wptr.lock();
}

bool operator!=(const StrBlobPtr& lhs, const StrBlobPtr& rhs) {
    return *lhs.wptr.lock() != *rhs.wptr.lock();
}

bool operator<(const StrBlobPtr& lhs, const StrBlobPtr& rhs) {
    return *lhs.wptr.lock() < *rhs.wptr.lock();
}

#endif //CPP_PRIMER_EX12_19_H
