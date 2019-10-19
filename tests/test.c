#include "test.h"
#include "../lib/src/library.h"


int tests() {
    return 0;
}

//!===========================================================================
//! Модифікації стрічки, що змінюють її розмір і можуть викликати реалокацію.
//!===========================================================================

int test_my_str_pushback() {
    my_str_t str1;
    my_str_t str2;
    char c1 = 'm';
    char c2 = '!';

    my_str_create(&str1, 1);
    my_str_create(&str2, 1);

    my_str_from_cstr(&str1, "lore", 0);
    my_str_from_cstr(&str2, "hello word", 0);

    my_str_pushback(&str1, c1);
    my_str_pushback(&str2, c2);

    if (my_str_cmp_cstr(&str1, "lorem") != 0 ||
        my_str_cmp_cstr(&str2, "hello word!"))
        return -1;

    return 0;
}

int test_my_str_popback() {
    my_str_t str1;
    my_str_t str2;

    my_str_create(&str1, 1);
    my_str_create(&str2, 1);

    my_str_from_cstr(&str1, "lorem", 0);
    my_str_from_cstr(&str2, "hello word", 0);

    if (my_str_popback(&str1) != 'm' ||
        my_str_popback(&str2) != 'd')
        return -1;

    return 0;
}

int test_my_str_copy() {
    my_str_t str1; // from
    my_str_t str2; // to

    my_str_create(&str1, 1);
    my_str_create(&str2, 1);

    my_str_from_cstr(&str1, "lorem", 0);
    my_str_copy(&str1, &str2, 0);

    return my_str_cmp(&str1, &str2);
}

int test_my_str_clear() {
    return 0;
}

int test_my_str_insert_c() {
    return 0;
}

int test_my_str_insert() {
    return 0;
}

int test_my_str_insert_cstr() {
    return 0;
}

int test_my_str_append() {
    return 0;
}

int test_my_str_append_cstr() {
    return 0;
}

int test_my_str_substr() {
    return 0;
}

int test_my_str_substr_cstr() {
    return 0;
}