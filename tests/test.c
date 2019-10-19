#include "test.h"
#include "../lib/src/library.h"
#include<stdio.h>
#include<string.h>

int main() {
    tests();
    return 0;

}
void modification_block() {
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
}
void information_block(){
    int temp;
    temp = test_my_str_size();
    if (temp != 0)
        printf("test test_my_str_size() Failed : %d\n", temp);

    temp = test_my_str_capacity();
    if (temp != 0)
        printf("test test_my_str_capacity() Failed : %d\n", temp);

    temp = test_my_str_empty();
    if (temp != 0)
        printf("test test_my_str_empty() Failed : %d\n", temp);


}
void access_block(){
    int temp;
    temp = test_my_str_getc();
    if (temp != 0)
        printf("test test_my_str_getc() Failed : %d\n", temp);

    temp = test_my_str_putc();
    if (temp != 0)
        printf("test test_my_str_putc() Failed : %d\n", temp);
}
void search_block(){
    int temp;
    temp = test_my_str_find();
    if (temp != 0)
        printf("test test_my_str_find() Failed : %d\n", temp);

    temp = test_my_str_cmp();
    if (temp != 0)
        printf("test test_my_str_cmp() Failed : %d\n", temp);

    temp = test_my_str_cmp_cstr();
    if (temp != 0)
        printf("test test_my_str_cmp_cstr() Failed : %d\n", temp);

    temp = test_my_str_find_c();
    if (temp != 0)
        printf("test test_my_str_find_c() Failed : %d\n", temp);

    temp = test_my_str_find_if();
    if (temp != 0)
        printf("test test_my_str_find_if() Failed : %d\n", temp);


}
void input_block(){
    int temp;
    temp = test_my_str_read_file();
    if (temp != 0)
        printf("test test_my_str_read_file() Failed : %d\n", temp);

    temp = test_my_str_write_file();
    if (temp != 0)
        printf("test test_my_str_write_file() Failed : %d\n", temp);

    temp = test_my_str_read_file_delim();
    if (temp != 0)
        printf("test test_my_str_read_file_delim() Failed : %d\n", temp);


}

int tests() {
    modification_block();
    information_block();
    access_block();
//    search_block();
//    input_block();
    return 0;
}



//!============================================================================
//! Інформація про стрічку
//!============================================================================

int test_my_str_size() {
    my_str_t st_s;
    size_t bufsize = 6;
    my_str_create(&st_s, bufsize);
    int res = my_str_size(&st_s);
    my_str_free(&st_s);
    return res;
}

int test_my_str_capacity() {

    my_str_t st1;
    size_t bufsize = 6;
    my_str_create(&st1, bufsize);
    my_str_free(&st1);
    return 6 == my_str_capacity(&st1);
}

int test_my_str_empty() {
    my_str_t s;
    size_t bufsize = 6;
    my_str_create(&s, bufsize);
    int res = my_str_empty(&s); // empty
    my_str_free(&s);
    return !res ;
}

//!===========================================================================
//! Доступ до символів стрічки
//!===========================================================================

int test_my_str_getc() {
    my_str_t st_f1 = file1_example();
    size_t ind = 3;
    int res = my_str_getc(&st_f1, ind);
    if(res > 0)
        return 0;
}

int test_my_str_putc() {
    my_str_t st_f1 = file1_example();
    size_t ind = 3;
    char s = 'S';
    my_str_putc(&st_f1, ind, s);

    my_str_t st_exp;
    size_t bs_f1 = 20;
    my_str_create(&st_exp, bs_f1);
    st_exp.data = "Sirst text reading...";
    return st_exp.data == st_f1.data;
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

//!===========================================================================
//! Функції пошуку та порівняння
//!===========================================================================

int test_my_str_find(){
    my_str_t st_f1 = file1_example();
    my_str_t st_4;
    size_t bs_4 = 5;
    my_str_create(&st_4, bs_4);
    FILE *f4 = fopen("../files/text1.txt", "r");
    my_str_read_file(&st_4, f4);
    size_t from = 1;
    fclose(f4);
    int res = my_str_find(&st_f1,&st_4,from);
//    my_str_free(&st_f1);
    my_str_free(&st_4);
    return res  > 0;
}

int test_my_str_cmp() {
    FILE *f2 = fopen("../files/text2.txt", "r");
    FILE *f3 = fopen("../files/text3.txt", "r");
    my_str_t st_f2;
    my_str_t st_f3;
    size_t bs_f2 = 20;
    my_str_create(&st_f2, bs_f2);
    my_str_create(&st_f3, bs_f2);
    my_str_read_file(&st_f2, f2);
    my_str_read_file(&st_f3, f3);

    fclose(f2);
    fclose(f3);

    return my_str_cmp(&st_f2,&st_f3) == -1;
}

int test_my_str_cmp_cstr() {
    FILE *f3 = fopen("../files/text3.txt", "r");
    my_str_t st_f3;
    size_t bs_f2 = 20;
    my_str_create(&st_f3, bs_f2);
    my_str_read_file(&st_f3,f3);
    const char *c_str = "computer";
    return my_str_cmp_cstr(&st_f3,c_str) == 1;
}

int test_my_str_find_c(){
    my_str_t st_f1 = file1_example();
    char toFind = 'g';
    int res = my_str_find_c(&st_f1, toFind, 0);
//    my_str_free(&st_f1);
    return res > 0;

}

int test_my_str_find_if(){
    my_str_t st_f1 = file1_example();
    int res = my_str_find_if(&st_f1, &predicant_f);
//    my_str_free(&st_f1);

    return res >= 1;

}

//!===========================================================================
//! Ввід-вивід
//!===========================================================================

int test_my_str_read_file() {
    FILE *f1 = fopen("../files/text1.txt", "r");
    my_str_t st_f1;
    size_t bs_f1 = 20;
    my_str_create(&st_f1, bs_f1);
    int res = my_str_read_file(&st_f1, f1);
    my_str_free(&st_f1);
    return res>0;
}



int test_my_str_write_file(){
    my_str_t st_f5;
    size_t bs_f5 = 10;
    my_str_create(&st_f5, bs_f5);
    FILE *f5 = fopen("../files/text5.txt", "w");
    int res = my_str_write_file(&st_f5, f5);
    fclose(f5);
    my_str_free(&st_f5);
    return res > 0;

}



int test_my_str_read_file_delim(){
    my_str_t st_f6;
    size_t bs_f6 = 10;
    FILE *f6 = fopen("../files/text6.txt", "r");
    my_str_read_file(&st_f6, f6);
    int res = my_str_read_file_delim(&st_f6, f6, '!');
    my_str_free(&st_f6);
    return res>0;
}

my_str_t file1_example(){
    FILE *f1 = fopen("../files/text1.txt", "r");
    my_str_t st_f1;
    size_t bs_f1 = 20;
    my_str_create(&st_f1, bs_f1);
    my_str_read_file(&st_f1, f1);
    my_str_t st_ef1 = st_f1;
    my_str_free(&st_f1);
    return st_ef1;
}

int predicant_f(int g){
    if (g == 'g') return 1;
    else return 0;

}
