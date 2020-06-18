#ifndef CPP_PRIMER_DELETE_H
#define CPP_PRIMER_DELETE_H

namespace cp5{
    struct Delete{
        template<typename T>
        void operator()(T* p) {
            delete p;
        }
    };
}

#endif //CPP_PRIMER_DELETE_H
