#include <iostream>

template <typename Iterator>
void print(Iterator begin, Iterator end) {
    if (begin == end) {
        return;
    }

    std::cout << *begin;
    ++begin;

    while (begin != end) {
        std::cout << '.' << *begin;
        ++begin;
    }
}