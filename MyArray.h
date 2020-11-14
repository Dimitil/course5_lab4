#ifndef MYARRAY_H
#define MYARRAY_H

#include <iostream>

template<typename T, size_t size>
class MyArray {
    T ar[size]{};
public:
    MyArray() = default;

    MyArray(const T* t) {
        for(size_t i = 0; i<size; i++) {
            ar[i] = t[i];
        }
    }

    void print() const {
        for (size_t i = 0; i < size; i++) {
            std::cout << ar[i] << ' ';
        }
        std::cout<< '\n';
    }
};

constexpr size_t mystrlen(const char* s) {
    return *s ? 1 + mystrlen(s+1) : 0;
}


template<typename T, size_t size = 5> MyArray(const T(& ar)[size]) -> MyArray <T, size>;


#endif // MYARRAY_H
