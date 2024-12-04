/*!
\file
\brief Файл, содержащий шаблонную функцию печати адресов, созданную с использованием механизма SFINAE

Данный файл содержит в себе набор функций для разных типов данных
*/

#include <type_traits>
#include <vector>
#include <list>
#include <tuple>
#include <string>
#include "utils.h"


/*!
Шаблонная функция обработки целочисленных значений
\param[in] value значение целого типа
*/
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

/*!
Шаблонная функция обработки строковых значений
\param[in] value значение строкового типа
*/
template <typename T>
typename std::enable_if<std::is_same<T, std::string>::value>::type
print_ip(const T& value) {
    std::cout << value << '\n';
}

/*!
Шаблонная функция обработки контейнеров
\param[in] value значение контейнерного типа
*/template <typename T>
typename std::enable_if<!std::is_same<T, std::string>::value && std::is_same<typename T::value_type, typename T::value_type>::value>::type
print_ip(const T& container) {
    print(container.begin(), container.end());
    std::cout << '\n';
}

/*!
Шаблонная функция обработки tuple - выход из рекурсии
\param[in] value значение типа tuple
*/
template <typename Tuple, size_t Index = 0>
typename std::enable_if<Index == std::tuple_size<Tuple>::value>::type
print_tuple(const Tuple&) { }

/*!
Шаблонная функция обработки tuple - вывод элементов (рекурсивно)
\param[in] value значение типа tuple
*/
template <typename Tuple, size_t Index = 0>
typename std::enable_if<Index < std::tuple_size<Tuple>::value>::type
print_tuple(const Tuple& tuple) {
    if constexpr (Index > 0) {
        std::cout << '.';
    }
    std::cout << std::get<Index>(tuple);
    print_tuple<Tuple, Index + 1>(tuple);
}

/*!
Шаблонная функция обработки tuple - начало работы, проверка условия, при котором все элементы должны быть одного типа
\param[in] value значение типа tuple
*/
template <typename... Args>
typename std::enable_if<std::conjunction<std::is_same<Args, typename std::tuple_element<0, std::tuple<Args...>>::type>...>::value>::type
print_ip(const std::tuple<Args...>& tuple) {
    print_tuple(tuple);
    std::cout << '\n';
}
