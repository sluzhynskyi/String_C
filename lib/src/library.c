#include "library.h"
#include <string.h>
#include <stdio.h>

int my_str_pushback(my_str_t *str, char c)
//! Додає символ в кінець.
//! Повертає 0, якщо успішно,
//! -1 -- якщо передано нульовий вказівник,
//! -2 -- помилка виділення додаткової пам'яті.
{
    if (str == NULL) return -1;
    if (my_str_reserve(str, str->capacity_m + 1) == -1)
        return -2;
    str->data[str->size_m] = c;
    str->size_m++;
    return 0;
}


int my_str_popback(my_str_t *str)
//! Викидає символ з кінця.
//! Повертає його, якщо успішно,
//! -1 -- якщо передано нульовий вказівник,
//! -2 -- якщо стрічка порожня.
{
    if (str == NULL) return -1;
    if (str->size_m == 0) return -2;
    char temp = str->data[str->size_m -1];
    str->size_m --;
    return temp;

}

int my_str_copy(const my_str_t *from, my_str_t *to, int reserve)
//! Копіює стрічку. Якщо reserve == true,
//! то із тим же розміром буферу, що й вихідна,
//! інакше -- із буфером мінімального достатнього розміру.
//! (Старий вміст стрічки перед тим звільняє, за потреби).
//! Повертає 0, якщо успішно, різні від'ємні числа для діагностики
//! проблеми некоректних аргументів.
{
    if (from == NULL) return -1;
    if (reserve)
        to->capacity_m = from->capacity_m;
    else
        to->capacity_m = from->size_m;
    memmove(to->data, from->data, from->size_m);
    to->size_m = from->size_m;
    return 0;
}

void my_str_clear(my_str_t *str)
//! Очищає стрічку -- робить її порожньою. Складність має бути О(1).
//! Уточнення (чомусь ця ф-ція викликала багато непорозумінь):
//! стрічка продовжує існувати, буфер той самий, того ж розміру, що був,
//! лише містить 0 символів -- єдине, що вона робить, це size_m = 0.
{

}

int my_str_insert_c(my_str_t *str, char c, size_t pos)
//! Вставити символ у стрічку в заданій позиції, змістивши решту символів праворуч.
//! За потреби -- збільшує буфер.
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
{
    return 0;
}

int my_str_insert(my_str_t *str, const my_str_t *from, size_t pos)
//! Вставити стрічку в заданій позиції, змістивши решту символів праворуч.
//! За потреби -- збільшує буфер.
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
{
    return 0;
}

int my_str_insert_cstr(my_str_t *str, const char *from, size_t pos)
//! Вставити C-стрічку в заданій позиції, змістивши решту символів праворуч.
//! За потреби -- збільшує буфер.
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
{
    return 0;
}

int my_str_append(my_str_t *str, const my_str_t *from)
//! Додати стрічку в кінець.
//! За потреби -- збільшує буфер.
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
{
    return 0;
}

int my_str_append_cstr(my_str_t *str, const char *from)
//! Додати С-стрічку в кінець.
//! За потреби -- збільшує буфер.
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
{
    return 0;
}

int my_str_substr(const my_str_t *from, my_str_t *to, size_t beg, size_t end)
//! Скопіювати підстрічку, із beg включно, по end не включно ([beg, end)).
//! Якщо end за межами початкової стрічки -- це не помилка, копіювати всі
//! символи до кінця. beg має бути в її межах -- якщо beg>size, це помилка.
//! За потреби -- збільшує буфер.
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
{
    return 0;
}

int my_str_substr_cstr(const my_str_t *from, char *to, size_t beg, size_t end)
//! C-string варіант my_str_substr().
//! Вважати, що в цільовій С-стрічці достатньо місц.
{
    return 0;
}