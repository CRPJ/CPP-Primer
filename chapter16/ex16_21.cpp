#include <iostream>

class DebugDelete{
public:
    DebugDelete(std::ostream& s = std::cerr) : os(s) {}

    template<typename T>
    void operator() (T* p) const {
        os << "deleting unique_ptr" << std::endl;
        delete p;
    }

private:
    std::ostream &os;
};

int main() {
    int* pi = new int ();
    DebugDelete d;
    d(pi);

    auto* pd = new double ();
    DebugDelete()(pd);
    return 0;
}