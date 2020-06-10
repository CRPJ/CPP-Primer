#include <iostream>

template<typename T>
void print(const T& arr) {
    for (auto& item : arr)
        std::cout << item << ' ';
}

int main() {
    int arr[] = {2,3,5,7,9};
    print(arr);
    return 0;
}