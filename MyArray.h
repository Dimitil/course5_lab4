#ifndef MYARRAY_H
#define MYARRAY_H

#include <iostream>

template<typename T, size_t size>
class MyArray {
    T ar[size]{}; //как обеспечить инициализацию элементов базового типа по умолчанию нулем?
public:
    MyArray() = default;

    MyArray(const char* str) {
        for (size_t i = 0; i < size; i++) {
            ar[i] = str[i];
        }
    }

    MyArray(const int* iptr) {
        for(size_t i = 0; i<size; i++) {
            ar[i] = iptr[i];
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

MyArray(const char str[]) -> MyArray<char,  4>;                               // здесь не правильно !!!!!!!!!!!!!!!!!!!!!
MyArray(const int intp[]) -> MyArray<int, 3>;

#endif // MYARRAY_H
