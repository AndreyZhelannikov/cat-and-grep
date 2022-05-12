#ifndef SRC_GREP_TEST_S21_GREP_TEST_H_
#define SRC_GREP_TEST_S21_GREP_TEST_H_
#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESET "\e[0m"
#define RED "\e[0;91m"
#define GREEN "\e[0;92m"
#define BLUE "\e[0;94m"

static const char *const s21_grep_flags[10] = {
    [0] = " -e ", [1] = " -i ", [2] = " -v ", [3] = " -c ", [4] = " -l ",
    [5] = " -n ", [6] = " -h ", [7] = " -s ", [8] = " -f ", [9] = " -o "};

void run_tests(void);

void run_testcase(Suite *testcase);

Suite *suite_combinations(void);

void pretty_print(char *grep, char *s21_grep, int val, int _i);
void get_flags(char *flags, int _i, char *e_pattern, char *search_pattern, char *f_file);

#endif  // SRC_GREP_TEST_S21_GREP_TEST_H_
