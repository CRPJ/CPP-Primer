#include <iostream>

template<typename T, unsigned N>
const T* begin(const T (&arr)[N]) {
    return arr;
}

template<typename T, unsigned N>
const T* end(T (&arr)[N]) {
    return arr + N;
}

int main() {
    int arr[] = {1,2,3};
    for(auto iter = begin(arr); iter != end(arr); ++iter)
        std::cout << *iter << ' ';
    return 0;
}