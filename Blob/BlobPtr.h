//
// Created by wangheng on 2020/6/10.
//

#ifndef BLOB_BLOBPTR_H
#define BLOB_BLOBPTR_H

#include <memory>
#include <vector>
#include <string>
#include "Blob.h"

template<typename T> class BlobPtr{
public:
    BlobPtr() : curr(0) {}
    explicit BlobPtr(Blob<T>& a, std::size_t sz = 0) : wptr(a.data), curr(sz) {}
    T& operator*() const {
        auto p = check(curr, "dereference past end");
        return (*p)[curr];
    }
    // 递增和递减
    BlobPtr& operator++();
    BlobPtr& operator--();

private:
    // 若检查成功，check返回一个指向vector的shared_ptr
    std::shared_ptr<std::vector<T>>
        check(std::size_t, const std::string&) const ;
    // 保存一个weak_ptr，表示底层vector可能被销毁
    std::weak_ptr<std::vector<T>> wptr;
    std::size_t curr;   // 数组中的当前位置
};

template<typename T>
BlobPtr<T>& BlobPtr<T>::operator++() {
    check(curr, "increment past end of BlobPtr");
    ++curr;
    return *this;
}

template<typename T>
BlobPtr<T>& BlobPtr<T>::operator--() {
    --curr;
    check(curr, "decrement past begin of BlobPtr");
    return *this;
}

template<typename T>
std::shared_ptr<std::vector<T>>
        BlobPtr<T>::check(std::size_t n, const std::string &msg) const {
    auto ret = wptr.lock();
    if (!ret)
        throw std::runtime_error("unbound BlobPtr");
    if (n >= ret->size())
        throw std::out_of_range(msg);
    return ret;
}

#endif //BLOB_BLOBPTR_H
