## Функция печати условного IP-адреса

Условность заключается в том, что количество элементов не обязательно должно быть равно 4-ём или 8-ми, а также каждый элемент не обязательно должен быть числом из диапазона 0..255. 

**Адрес может быть представлен в виде произвольного целочисленного типа**
Выводится побайтово в беззнаковом виде, начиная со старшего байта

**Адрес может быть представлен в виде строки**
Выводится как есть

**Адрес может быть представлен в виде контейнеров**
Выводится полное содержимое контейнера поэлементно

**Адрес может быть представлен в виде std::tuple при условии, что все типы одинаковы**
Выводится полное содержимое поэлементно

#### tuple

1. вызов функции print_tuple добавляя строку вывода ('\n')
```cpp
template <typename... Args>
typename std::enable_if<
    std::conjunction<std::is_same<Args, typename std::tuple_element<0, std::tuple<Args...>>::type>...>::value
>::type
print_ip(const std::tuple<Args...>& tuple) {
    print_tuple(tuple);
    std::cout << '\n';
}
```
Используется std::conjunction для проверки, что все типы в кортеже одинаковы:
```std::tuple_element<0, std::tuple<Args...>>::type:``` Получает тип первого элемента кортежа.
```std::is_same<Args, ...>:``` Проверяет, что каждый тип в кортеже совпадает с типом первого элемента.
```std::conjunction:``` Логический AND, возвращает true, если все проверки выполнены.

2. печать текущего элемента кортежа и вызов себя для следующего элемента (Index + 1)
```cpp
template <typename Tuple, size_t Index = 0>
typename std::enable_if<Index < std::tuple_size<Tuple>::value>::type
print_tuple(const Tuple& tuple) {
    if constexpr (Index > 0) {
        std::cout << '.';
    }
    std::cout << std::get<Index>(tuple);
    print_tuple<Tuple, Index + 1>(tuple);
}
```

3. завершение рекурсии.
print_tuple(const Tuple&) { }
