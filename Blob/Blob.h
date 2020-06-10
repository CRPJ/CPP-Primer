//
// Created by wangheng on 2020/6/10.
//

#ifndef BLOB_BLOB_H
#define BLOB_BLOB_H

#include <vector>
#include <initializer_list>
#include <memory>
#include <string>

template<typename > class BlobPtr;

template<typename T> class Blob{
    friend class BlobPtr<T>;
public:
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;
    // 构造函数
    Blob();
    Blob(std::initializer_list<T> il);
    // Blob中的元素数目
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    // 添加和删除元素
    void push_back(const T& t) { data->push_back(t); }
    // 移动版本
    void push_back(T&& t) { data->push_back(std::move(t)); }
    void pop_back();
    // 元素访问
    T& back();
    T& operator[](size_type i);
private:
    std::shared_ptr<std::vector<T>> data;
    // 若data[i]无效，则抛出msg
    void check(size_type i, const std::string& msg) const ;
};

template<typename T>
void Blob<T>::check(size_type i, const std::string &msg) const {
    if (i >= data->size())
        throw std::out_of_range(msg);
}

template<typename T>
T& Blob<T>::back() {
    return data->back();
}

template<typename T>
T& Blob<T>::operator[](size_type i) {
    return (*data)[i];
}

template<typename T>
void Blob<T>::pop_back() {
    data->pop_back();
}

template<typename T>
Blob<T>::Blob() : data(std::make_shared<std::vector<T>>()) {}

template<typename T>
Blob<T>::Blob(std::initializer_list<T> il) : data(std::make_shared<std::vector<T>>(il)) {}

#endif //BLOB_BLOB_H
