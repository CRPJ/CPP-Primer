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
public:
    friend class StrBlobPtr;
    typedef std::vector<std::string>::size_type size_type;
    StrBlob();
    StrBlob(std::initializer_list<std::string> il);
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    // ��Ӻ�ɾ��Ԫ��
    void push_back(const std::string &t) { data->push_back(t); }
    void pop_back();
    // Ԫ�ط���
    std::string &front();
    std::string &front() const;
    std::string &back();
    std::string &back() const;
    StrBlobPtr begin();
    StrBlobPtr end();
    int count() { return data.use_count(); }
private:
    std::shared_ptr<std::vector<std::string>> data;
    // ���data[i]���Ϸ����׳��쳣
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

class StrBlobPtr {
public:
    using size_t = std::vector<std::string>::size_type;
    StrBlobPtr() : curr(0) {}
    // ʹ��StrBlob�����ñ��⿽��
    StrBlobPtr(StrBlob& a, size_t sz = 0) : wptr(a.data), curr(sz) {}
    bool operator!=(const StrBlobPtr& p) { return p.curr != this->curr; }
    std::string &dref() const ;
    StrBlobPtr& incr();     // ����ǰ׺
private:
    // �����ɹ���check����һ��ָ��vector��shared_ptr
    std::shared_ptr<std::vector<std::string>>
        check(std::size_t, const std::string&) const;
    // ����һ��waek_ptr����ζ�ŵײ�vector���ܱ�����
    std::weak_ptr<std::vector<std::string>> wptr;
    size_t curr;   // �������е�ǰ��λ��
};

std::string& StrBlobPtr::dref() const {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

StrBlobPtr& StrBlobPtr::incr() {
    // ���curr�Ѿ�ָ��������β��λ�ã��Ͳ��ܵ�����
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

#endif //CPP_PRIMER_EX12_19_H
