#include "test.h"
#include "../lib/src/library.h"



int tests() {
    int temp = 0;
    temp += test_my_str_pushback();
    printf("test 1 output : %d\n", test_my_str_pushback());
    temp += test_my_str_popback();
    printf("test 2 output: %d\n", test_my_str_popback());
    temp += test_my_str_copy();
    printf("test 3 output: %d\n", test_my_str_copy());
    temp += test_my_str_clear();
    printf("test 4 output: %d\n", test_my_str_clear());
    temp += test_my_str_insert_c();
    printf("test 5 output: %d\n", test_my_str_insert_c());
    temp += test_my_str_insert();
    printf("test 6 output: %d\n", test_my_str_insert());
    temp += test_my_str_insert_cstr();
    printf("test 7 output: %d\n", test_my_str_insert_cstr());

    return temp;
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


    printf("str is: %c, %c\n",str1.data[0], str1.data[1]);
    if (my_str_cmp_cstr(&str1, "lorem") != 0 ||
        my_str_cmp_cstr(&str2, "hello word!"))
        return -1;
    my_str_free(&str1);
    my_str_free(&str2);
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
    my_str_free(&str1);
    my_str_free(&str2);
    return 0;
}

int test_my_str_copy() {
    my_str_t str1; // from
    my_str_t str2; // to

    my_str_create(&str1, 1);
    my_str_create(&str2, 1);

    my_str_from_cstr(&str1, "lorem", 0);
    my_str_copy(&str1, &str2, 0);

    int res = my_str_cmp(&str1, &str2);

    my_str_free(&str1);
    my_str_free(&str2);
    return res;
}

int test_my_str_clear() {
    my_str_t str1;

    my_str_create(&str1, 1);
    my_str_from_cstr(&str1, "lorem", 0);

    my_str_clear(&str1);

    if (str1.size_m != 0)
        return -1;
    my_str_free(&str1);
    return 0;
}

int test_my_str_insert_c() {
    my_str_t str1;

    my_str_create(&str1, 1);
    my_str_from_cstr(&str1, "WW", 0);

    my_str_insert_c(&str1, 'O',1);

    if (my_str_cmp_cstr(&str1, "WOW") != 0)
        return -1;
    my_str_free(&str1);
    return 0;
}

int test_my_str_insert() {
    my_str_t str1;
    my_str_t str2;

    my_str_create(&str1, 1);
    my_str_create(&str2, 1);

    my_str_from_cstr(&str1, "lorem", 0);
    my_str_from_cstr(&str2, " hello word ", 0);
    my_str_insert(&str1, &str2, 2);

    if (my_str_cmp_cstr(&str1, "lo hello word rem") != 0)
        return -1;
    return 0;
}

int test_my_str_insert_cstr() {
    my_str_t str1;

    my_str_create(&str1, 1);
    my_str_from_cstr(&str1, "WW", 0);

    my_str_insert_cstr(&str1, " oooooo ", 1);

    if (my_str_cmp_cstr(&str1, "W oooooo W") != 0)
        return -1;
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