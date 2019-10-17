#include "library.h"
#include <string.h>
#include <stdio.h>

// INITIALIZING

int my_str_create(my_str_t *str, size_t buf_size) {
    str->capacity_m = buf_size;
    str->size_m = 0;
    str->data = (char *) malloc((buf_size + 1) * sizeof(char));
    if (str->data == NULL) {
        free(&(str->capacity_m));
        free(&(str->size_m));
        return -1;
    }
    return 0;
}

void my_str_free(my_str_t *str) {
    free(str->data);
    str->capacity_m = 0;
    str->size_m = 0;
}

int my_str_from_cstr(my_str_t *str, const char *cstr, size_t buf_size) {
    if (!str) return -2;
    if (!cstr) return -2;
    str->capacity_m = buf_size;
    str->size_m = buf_size;
    str->data = (char *) malloc((buf_size + 1));
    if (str->data == NULL) {
        str->capacity_m = buf_size;
        str->size_m = 0;
        return -2;
    }
    size_t i;
    for (i = 0; i <= buf_size; i++) {
        if (*(cstr + i) == '\0') {
            str->size_m = i;
            break;
        }
        *(str->data + i) = *(cstr + i);   //ul * size_t
    }
    if (i == buf_size && *(cstr + (buf_size + 1)) != '\0') {
        str->capacity_m = buf_size;
        str->size_m = 0;
        free(str->data);
        return -1;
    }
    return 0;
}


// MODIFICATION OF THE STRING
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
    char temp = str->data[str->size_m - 1];
    str->size_m--;
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
    str->size_m = 0;
}

int my_str_insert_c(my_str_t *str, char c, size_t pos)
//! Вставити символ у стрічку в заданій позиції, змістивши решту символів праворуч.
//! За потреби -- збільшує буфер.
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
{
    if (my_str_reserve(str, str->capacity_m + 1) == -1)
        return -1;
    if (pos >= str->size_m) return -2;
    memmove(str->data + pos + 1, str->data + pos, str->size_m - pos);
    str->size_m++;
    str->data[pos] = c;
    return 0;
}

int my_str_insert(my_str_t *str, const my_str_t *from, size_t pos)
//! Вставити стрічку в заданій позиції, змістивши решту символів праворуч.
//! За потреби -- збільшує буфер.
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
{
    if ((str == NULL) || (from == NULL)) return -1;
    if (my_str_reserve(str, str->capacity_m + from->size_m) == -1)
        return -2;
    if (pos > str->size_m) return -3;
    memmove(str->data + pos + from->size_m, str->data + pos, str->size_m - pos);
    memcpy(str->data + pos, from->data, from->size_m);
    str->size_m += from->size_m;
    return 0;
}

int my_str_insert_cstr(my_str_t *str, const char *from, size_t pos)
//! Вставити C-стрічку в заданій позиції, змістивши решту символів праворуч.
//! За потреби -- збільшує буфер.
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
{
    my_str_t tempStr;
    my_str_create(&tempStr, 0);
    my_str_from_cstr(&tempStr, from, 0);
    int ans = my_str_insert(str, &tempStr, pos);
    my_str_free(&tempStr);
    return ans;
}


int my_str_append(my_str_t *str, const my_str_t *from)
//! Додати стрічку в кінець.
//! За потреби -- збільшує буфер.
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
{
    return my_str_insert(str, from, str->size_m);
}

int my_str_append_cstr(my_str_t *str, const char *from)
//! Додати С-стрічку в кінець.
//! За потреби -- збільшує буфер.
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
{
    return my_str_insert_cstr(str, from, str->size_m);
}

int my_str_substr(const my_str_t *from, my_str_t *to, size_t beg, size_t end)
//! Скопіювати підстрічку, із beg включно, по end не включно ([beg, end)).
//! Якщо end за межами початкової стрічки -- це не помилка, копіювати всі
//! символи до кінця. beg має бути в її межах -- якщо beg>size, це помилка.
//! За потреби -- збільшує буфер.
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
{
    if (from == NULL) return -1;
    if (beg > from->size_m)
        return -2;
    memmove(to->data, from->data + beg, end - beg);
    my_str_reserve(to, end - beg);
    to->size_m = end -beg;
    return 0;

}

int my_str_substr_cstr(const my_str_t *from, char *to, size_t beg, size_t end)
//! C-string варіант my_str_substr().
//! Вважати, що в цільовій С-стрічці достатньо місц.
{
    if (from == NULL) return -1;
    if (beg > from->size_m)
        return -2;
    memmove(to, from->data + beg, end - beg);
    to[end - beg] = '\0';
    return 0;
}


// INPUT OUTPUT

size_t my_str_size(const my_str_t *str) {
    //! Повертає розмір стрічки
    if (str == NULL) {
        return 0;
    }
    return str->size_m;
}

size_t my_str_capacity(const my_str_t *str) {
    //! Повертає розмір буфера
    if (str == NULL) {
        return 0;
    }
    return str->capacity_m;
}


int my_str_empty(const my_str_t *str) {
    //! Повертає булеве значення, чи стрічка порожн
    if (str->size_m == 0) {
        return 1;
    }
    return 0;
}


int my_str_getc(const my_str_t *str, size_t index) {
    //! Повертає символ у вказаній позиції, або -1
    if (index > str->size_m - 1) {
        return -1;
    }
    return str->data[index];

}

int my_str_putc(my_str_t *str, size_t index, char c) {
    //! Записує символ у вказану позиції (заміняючи той, що там був),
    //! Повертає 0, якщо позиція в межах стрічки,
    //! Поветає -1, не змінюючи її вмісту, якщо ні.
    if (index > str->size_m - 1) {
        return -1;
    }
    str->data[index] = c;
    return 0;
}


const char *my_str_get_cstr(my_str_t *str) {
    //! Повернути вказівник на С-стрічку, еквівалентну str.
    str->data[str->size_m] = '\0';
    return str->data;
}