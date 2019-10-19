#ifndef STRING_C_TEST_H
#define STRING_C_TEST_H

int tests();

//!============================================================================
//! Інформація про стрічку
//!============================================================================

int test_my_str_size();

int test_my_str_from_cstr();

int test_my_str_capacity();

int test_my_str_create();

int test_my_str_empty();

//!===========================================================================
//! Доступ до символів стрічки
//!===========================================================================

int test_my_str_getc();

int test_my_str_putc();

int test_my_str_get_cstr();

//!===========================================================================
//! Модифікації стрічки, що змінюють її розмір і можуть викликати реалокацію.
//!===========================================================================

int test_my_str_pushback();

int test_my_str_popback();

int test_my_str_copy();

int test_my_str_insert_c();

int test_my_str_insert();

int test_my_str_insert_cstr();

int test_my_str_append();

int test_my_str_append_cstr();

int test_my_str_substr();

int test_my_str_substr_cstr();

//!===========================================================================
//! Маніпуляції розміром стрічки
//!===========================================================================


int test_my_str_reserve();

int test_my_str_shrink_to_fit();

int test_my_str_resize();

//!===========================================================================
//! Функції пошуку та порівняння
//!===========================================================================

int test_my_str_find();

int test_my_str_cmp();

int test_my_str_cmp_cstr();

int test_my_str_find_c();

int test_my_str_find_if();

//!===========================================================================
//! Ввід-вивід
//!===========================================================================

int test_my_str_read_file();

int test_my_str_write_file();

int test_my_str_read_file_delim();

#endif STRING_C_TEST_H