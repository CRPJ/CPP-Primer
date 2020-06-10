#include <iostream>
#include "Blob.h"
#include "BlobPtr.h"

int main() {
    Blob<std::string> blob({"hello", "world", "good"});
    BlobPtr<std::string> ptr(blob);
    std::cout << *ptr << std::endl;
    ++ptr;
    std::cout << *ptr << std::endl;
    return 0;
}