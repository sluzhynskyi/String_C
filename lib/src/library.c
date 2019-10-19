#include "library.h"
#include <string.h>
#include <stdio.h>

// INITIALIZING
//!===========================================================================
//! Створення та знищення стрічки.
//!===========================================================================


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

//!============================================================================
//! Інформація про стрічку
//!============================================================================
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

//!===========================================================================
//! Доступ до символів стрічки
//!===========================================================================


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

//!===========================================================================
//! Модифікації стрічки, що змінюють її розмір і можуть викликати реалокацію.
//!===========================================================================


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

//!===========================================================================
//! Маніпуляції розміром стрічки
//!===========================================================================
int my_str_reserve(my_str_t *str, size_t buf_size) {
    if (!str) return -1;
    if (buf_size <= str->capacity_m) return 0;
    char *temp = (char*)malloc((buf_size + 1)); // sizeof(char) = 1
    if (temp == NULL) return -1;
    for (size_t i = 0; i < str->size_m; i++) *(temp + i) = *(str->data + i);
    free(str->data);
    str->data = temp;
    str->capacity_m = buf_size;
    return 0;
}

int my_str_shrink_to_fit(my_str_t *str) {
    if (!str) return -1;
    str->capacity_m = str->size_m;
    return 0;
}

int my_str_resize(my_str_t *str, size_t new_size, char sym) {
    if (!str) return -1;

    if (new_size > str->capacity_m) {
        int echo = my_str_reserve(str, new_size);
        if (echo < 0) return -1;
        for (size_t i = str->size_m; i < str->capacity_m; i++) {
            *(str->data + i) = sym;
        }
    }
    if (new_size > str->size_m) {
        for (size_t i = str->size_m; i < new_size; i++) {
            *(str->data + i) = sym;
        }
    }
    str->size_m = new_size;
    return 0;
}

//!===========================================================================
//! Функції пошуку та порівняння
//!===========================================================================

size_t my_str_find(const my_str_t* str, const my_str_t* tofind, size_t from){
    //! Знаходить першу підстрічку в стрічці, повертає номер її
    //! початку або (size_t)(-1), якщо не знайдено.
    if (str->size_m <  tofind->size_m || str->size_m -1 < from) {
        return (size_t)(-1);
    }
    int search_index = 0;
    for (size_t i = from; i < str->size_m; i++ ){
        if (str->data[i] == tofind->data[search_index]){
            search_index++;
        }

        else if (str->data[i] != tofind->data[search_index]){
            search_index = 0;
        }

        if (tofind->size_m <= search_index){
            return i - search_index +1;
        }

    }
    return (size_t)(-1);
}


//! Поведінка має бути такою ж, як в strcmp.
int my_str_cmp(const my_str_t* str1, const my_str_t* str2) {
    //! Порівнює стрічки, повертає 0, якщо рівні (за вмістом!)
    //! -1 (або інше від'ємне значення), якщо перша менша,
    //! 1 (або інше додатне значення) -- якщо друга.

    if (str1->size_m > str2->size_m) {
        return 1;
    } else if (str1->size_m < str2->size_m) {
        return -1;
    }
    for (size_t i = 0; i < str1->size_m; ++i) {
        if (my_str_getc(str1, i) < my_str_getc(str2, i)) {
            return -1;
        } else if (my_str_getc(str1, i) > my_str_getc(str2, i)) {
            return 1;
        }

    }
    return 0;
}


int my_str_cmp_cstr(const my_str_t* str1, const char* cstr2){
    //! Порівнює стрічку із С-стрічкою,
    //! повертає 0, якщо рівні (за вмістом!)
    //! -1 , якщо перша менша,
    //! 1  -- якщо друга.

    size_t str2_size = 0;
    while (cstr2[str2_size] != '\0') {
        str2_size++;
    }

    if (str1->size_m > str2_size)
        return 1;
    else if (str1->size_m < str2_size)
        return -1;
    else {
        for (int i = 0; i < str1->size_m; ++i) {
            if (str1->data[i] > cstr2[i])
                return 1;
            else if (str1->data[i] < cstr2[i])
                return -1;
        }

    }
    return 0;
}


size_t my_str_find_c(const my_str_t* str, char tofind, size_t from){
    //! Знаходить перший символ в стрічці, повернути його номер
    //! або (size_t)(-1), якщо не знайдено.
    if (str->size_m < from ) {
        return (size_t)(-1);
    }
    for (size_t i = from; i < str->size_m; i++) {
        if (str->data[i] == tofind) {
            return i;
        }
    }
    return (size_t)(-1);
}




size_t my_str_find_if(const my_str_t* str, int (*predicat)(int)){
    //! Знаходить символ в стрічці, для якого передана функція повернула true,
    //! повернутає його номер або (size_t)(-1), якщо не знайдено
    for (size_t i = 0; i < str->size_m; i++) {
        if (predicat((int) str->data[i]))
            return i;
    }
    return (size_t) (-1);

}

//!===========================================================================
//! Ввід-вивід
//!===========================================================================

//! Прочитати стрічку із файлу. Читає цілий файл.
//! Не давайте читанню вийти за межі буфера! За потреби --
//! збільшуйте буфер.
//! Рекомендую скористатися fgets().
//! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.

int my_str_read_file(my_str_t* str, FILE* file) {
    //! Читає стрічку із файлу. Читає цілий файл.
    if (file == NULL){
        return -1;
    }
    while(!feof(file)) {
        if (fgets(str->data, 2, file)) {
            if (str->size_m == str->capacity_m)
                my_str_reserve(str, str->capacity_m * 2);
            ++str->size_m;
            continue;
        }
        else{
            return -1;
        }
    }
    fclose(file);
    return 0;
}
//

int my_str_read(my_str_t* str){
    //! Аналог my_str_read_file, із stdin.
    if (stdin == NULL) return -1;
    while(fgets(str->data, 2, stdin)) {
        if (str->size_m == str->capacity_m)
            my_str_reserve(str, str->capacity_m * 2);
        ++str->size_m;
    }
    return 0;
}

int my_str_write_file(const my_str_t* str, FILE* file){
    //! Записує стрічку в файл:
    //! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
    if (file == NULL) return -1;
    for (int i = 0; i < str->size_m; i++)
        fputc(str->data[i], file);
    return 0;

}
int my_str_write(const my_str_t *str) {
    if (str->size_m == 0)
        return -1;
    for (int i = 0; i < str->size_m; i++) {
        printf("%c", str->data[i]);
    }
    return 0;
}


int my_str_read_file_delim(my_str_t* str, FILE* file, char delimiter){
    //! На відміну від my_str_read_file(), яка читає до кінця файлу,
    //! читає по вказаний delimiter, за потреби
    //! збільшує стрічку.
    //! У випадку помилки повертає різні від'ємні числа, якщо все ОК -- 0.
    if (file == NULL) return -1;
    int curr_buf;
    while ((curr_buf = fgetc(file)) != delimiter && (curr_buf = fgetc(file)) != EOF){
        if(my_str_pushback(str, (char) curr_buf) != 0){
            return -1;
        }
    }
    return 0;
}

