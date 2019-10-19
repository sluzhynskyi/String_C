#include "test.h"
#include "../lib/src/library.h"
#include<stdio.h>
#include<string.h>

int main() {
    int res = tests();
    return 0;

}

int tests() {
    int temp;

    temp = test_my_str_pushback();
    if (temp != 0)
        printf("test test_my_str_pushback() Failed : %d\n", temp);


    temp = test_my_str_popback();
    if (temp != 0)
        printf("test test_my_str_popback() Failed : %d\n", temp);


    temp = test_my_str_copy();
    if (temp != 0)
        printf("test test_my_str_copy() Failed : %d\n", temp);


    temp = test_my_str_clear();
    if (temp != 0)
        printf("test test_my_str_clear() Failed : %d\n", temp);


    temp = test_my_str_insert_c();
    if (temp != 0)
        printf("test test_my_str_insert_c() Failed : %d\n", temp);

    temp = test_my_str_insert();
    if (temp != 0)
        printf("test test_my_str_insert() Failed : %d\n", temp);


    temp = test_my_str_insert_cstr();
    if (temp != 0)
        printf("test test_my_str_insert_cstr() Failed : %d\n", temp);

    temp = test_my_str_append();
    if (temp != 0)
        printf("test test_my_str_append() Failed : %d\n", temp);

    temp = test_my_str_append_cstr();
    if (temp != 0)
        printf("test test_my_str_append_cstr() Failed : %d\n", temp);

    temp = test_my_str_substr();
    if (temp != 0)
        printf("test test_my_str_substr() Failed : %d\n", temp);

    temp = test_my_str_substr_cstr();
    if (temp != 0)
        printf("test test_my_str_substr_cstr() Failed : %d\n", temp);

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
    my_str_from_cstr(&str2, "hello world", 0);

    my_str_pushback(&str1, c1);
    my_str_pushback(&str2, c2);


    if (my_str_cmp_cstr(&str1, "lorem") != 0 ||
        my_str_cmp_cstr(&str2, "hello world!"))
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
    my_str_from_cstr(&str2, "hello world", 0);

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

    my_str_insert_c(&str1, 'O', 1);

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
    my_str_from_cstr(&str2, " hello world ", 0);
    my_str_insert(&str1, &str2, 2);
    int res = 0;
    if (my_str_cmp_cstr(&str1, "lo hello world rem") != 0)
        res = -1;
    my_str_free(&str1);
    my_str_free(&str2);
    return res;
}

int test_my_str_insert_cstr() {
    my_str_t str1;

    my_str_create(&str1, 1);
    my_str_from_cstr(&str1, "WW", 0);

    my_str_insert_cstr(&str1, " oooooo ", 1);
    int res = 0;
    if (my_str_cmp_cstr(&str1, "W oooooo W") != 0)
        res = -1;
    my_str_free(&str1);
    return res;
}

int test_my_str_append() {
    my_str_t str1;
    my_str_t str2;

    my_str_create(&str1, 1);
    my_str_create(&str2, 1);

    my_str_from_cstr(&str1, "Hello world", 0);
    my_str_from_cstr(&str2, "!!!!!!", 0);
    my_str_append(&str1, &str2);

    int res = 0;
    if (my_str_cmp_cstr(&str1, "Hello world!!!!!!") != 0)
        res = -1;
    my_str_free(&str1);
    my_str_free(&str2);
    return res;
}

int test_my_str_append_cstr() {
    my_str_t str1;

    my_str_create(&str1, 1);
    my_str_from_cstr(&str1, "Hello World", 0);

    my_str_append_cstr(&str1, "!!!!!!!");

    int res = 0;
    if (my_str_cmp_cstr(&str1, "Hello World!!!!!!!") != 0)
        res = -1;
    my_str_free(&str1);
    return res;
}

int test_my_str_substr() {
    my_str_t str1;
    my_str_t str2;

    my_str_create(&str1, 1);
    my_str_create(&str2, 1);

    my_str_from_cstr(&str1, "Hello World!!!!!", 0);
    my_str_substr(&str1, &str2, 6, 11);

    int res = 0;
    if (my_str_cmp_cstr(&str2, "World") != 0)
        res = -1;
    my_str_free(&str1);
    my_str_free(&str2);
    return res;
}

int test_my_str_substr_cstr() {
    my_str_t str1;
    char c[10];

    my_str_create(&str1, 1);

    my_str_from_cstr(&str1, "Hello World!!!!!", 0);
    my_str_substr_cstr(&str1, c, 6, 11);
    int res = 0;
    if (strcmp(c, "World") != 0)
        res = -1;
    my_str_free(&str1);
    return res;
}