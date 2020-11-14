#ifndef PRINT_AND_SUM_H
#define PRINT_AND_SUM_H

#include <iostream>
#include <vector>
#include <stack>
#include <queue>

template <typename T>
void print(const T& cont) {
    if constexpr (std::is_pointer<
                                  std::decay_t<
                                               decltype(*std::begin(cont))
                                                                          >
                                                                           >() ) {
        for(auto &el : cont) {
            std::cout << *el << ' ';
        }
    }
    else {
        for(auto &el : cont) {
            std::cout << el << ' ';
        }
    }
    std::cout << '\n';
}

template<typename F, typename S>
auto sum(const F& f, const S& s) {
    if constexpr (std::is_same< std::vector<S>, F>()) {
        std::vector<S> vs = f;
        for (auto &el : vs) {
            el += s;
        }
        return vs;
    }
    else {
        return f + s;
    }
}

template<typename F>        //fixed
void adapter_print(F &f) {
    if constexpr (std::is_same <std::stack<typename F::value_type, typename F::container_type>, F> () ||
                  std::is_same <std::priority_queue<typename F::value_type, typename F::container_type>, F> () ) {
        if constexpr ( std::is_pointer <typename F::value_type> ()) {
            while(!f.empty()) {
                std::cout << *f.top() << ' ';
                f.pop();
            }
        }
        else {
            while (!f.empty()) {
                std::cout << f.top() << ' ';
                f.pop();
            }
        }
    }
    else if constexpr (( std::is_same <std::queue<typename F::value_type, typename F::container_type>, F> ())) {
        if constexpr ( std::is_pointer <typename F::value_type> ()) {
            while (!f.empty()) {
                std::cout << *f.front() << ' ';
                f.pop();
            }
        }
        else {
            while (!f.empty()) {
                std::cout << f.front() << ' ';
                f.pop();
            }
        }
    }
    else {
        std::cerr << "ERROR TYPE";
    }
    std::cout<< '\n';
}


#endif // PRINT_AND_SUM_H
