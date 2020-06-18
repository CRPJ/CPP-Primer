#ifndef CPP_PRIMER_UNIQUE_PTR_H
#define CPP_PRIMER_UNIQUE_PTR_H

#include "delete.h"
#include <iostream>

template<typename, typename > class UniquePointer;

template<typename T, typename D>
void swap(UniquePointer<T, D>& lhs, UniquePointer<T, D>& rhs);

template<typename T, typename D = cp5::Delete> class UniquePointer{
    friend void swap<T, D>(UniquePointer<T, D>& lhs, UniquePointer<T, D>& rhs);

public:
    // 禁止拷贝构造和拷贝赋值运算
    UniquePointer(const UniquePointer&) = delete ;
    UniquePointer& operator=(const UniquePointer&) = delete ;

    UniquePointer() = default;
    explicit UniquePointer(T *pointer) : ptr(pointer) {}

    UniquePointer(UniquePointer && other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    UniquePointer& operator=(UniquePointer &&rhs) noexcept;

    UniquePointer& operator=(std::nullptr_t n) noexcept ;

    T& operator*() const { return *ptr; }
    T* operator->() const { return &this->operator*(); }
    operator bool() const { return ptr!= nullptr; }

    T* get() const noexcept { return ptr; }

    void swap(UniquePointer& rhs) { ::swap(*this, rhs); }

    void reset() noexcept { deleter(ptr); ptr = nullptr; }
    void reset(T* p) noexcept { deleter(ptr); ptr = p; }

    T* release();

    ~UniquePointer() { deleter(ptr); }
private:
    T* ptr = nullptr;
    D deleter = D();
};

template<typename T, typename D>
inline void swap(UniquePointer<T, D>& lhs, UniquePointer<T, D>& rhs) {
    using std::move;
    swap(lhs.ptr, rhs.ptr);
    swap(lhs.deleter, rhs.deleter);
}

template<typename T, typename D>
inline UniquePointer<T, D>& UniquePointer<T, D>::operator=(UniquePointer&& rhs) noexcept {
    if (this->ptr != rhs.ptr) {
        deleter(ptr);
        ptr = nullptr;
        swap(*this, rhs);
    }
    return *this;
}

template<typename T, typename D>
inline UniquePointer<T, D>& UniquePointer<T, D>::operator=(std::nullptr_t n) noexcept {
    if (n == nullptr) {
        deleter(ptr);
        ptr = nullptr;
    }
    return *this;
}

template<typename T, typename D>
inline T* UniquePointer<T, D>::release() {
    T* ret = ptr;
    ptr = nullptr;
    return ret;
}

#endif //CPP_PRIMER_UNIQUE_PTR_H
