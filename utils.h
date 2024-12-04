/*!
\file
\brief Файл, содержащий вспомогательные функции

Данный файл содержит в себе функции, используемые в программе
*/

#include <iostream>


/*!
Шаблонная функция печати значений по итераторам
\param[in] begin Начальный итератор
\param[in] end Конечный итератор
*/
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