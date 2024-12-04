#include <type_traits>
#include <vector>
#include <list>
#include <tuple>
#include <string>
#include "utils.h"


// 1. целые числа
template <typename T>
typename std::enable_if<std::is_integral<T>::value>::type
print_ip(const T& value) {
    constexpr size_t parts = sizeof(T);
    T temp = value;

    std::vector<T> segments;

    for (size_t i = 0; i < parts; ++i) {
        segments.push_back(temp & 0xFF);
        temp >>= 8;
    }

    print(segments.rbegin(), segments.rend());

    std::cout << '\n';
}

// 2. строки
template <typename T>
typename std::enable_if<std::is_same<T, std::string>::value>::type
print_ip(const T& value) {
    std::cout << value << '\n';
}

// 3. контейнеры
template <typename T>
typename std::enable_if<!std::is_same<T, std::string>::value && std::is_same<typename T::value_type, typename T::value_type>::value>::type
print_ip(const T& container) {
    print(container.begin(), container.end());
    std::cout << '\n';
}

// 4. tuple
template <typename Tuple, size_t Index = 0>
typename std::enable_if<Index == std::tuple_size<Tuple>::value>::type
print_tuple(const Tuple&) { }

template <typename Tuple, size_t Index = 0>
typename std::enable_if<Index < std::tuple_size<Tuple>::value>::type
print_tuple(const Tuple& tuple) {
    if constexpr (Index > 0) {
        std::cout << '.';
    }
    std::cout << std::get<Index>(tuple);
    print_tuple<Tuple, Index + 1>(tuple);
}

template <typename... Args>
typename std::enable_if<std::conjunction<std::is_same<Args, typename std::tuple_element<0, std::tuple<Args...>>::type>...>::value>::type
print_ip(const std::tuple<Args...>& tuple) {
    print_tuple(tuple);
    std::cout << '\n';
}
