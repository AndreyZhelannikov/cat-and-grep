#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define BBLK "\e[1;30m"
#define RESET "\e[0m"

//#define HBLK "\e[0;90m"
#define RED "\e[0;91m"
#define GREEN "\e[0;92m"
//#define HYEL "\e[0;93m"
#define BLUE "\e[0;94m"
//#define HMAG "\e[0;95m"
//#define HCYN "\e[0;96m"
//#define HWHT "\e[0;97m"

static const char *const s21_grep_flags[10] = {
    [0] = " -e ", [1] = " -i ", [2] = " -v ", [3] = " -c ", [4] = " -l ",
    [5] = " -n ", [6] = " -h ", [7] = " -s ", [8] = " -f ", [9] = " -o "};

void run_tests(void);

void run_testcase(Suite *testcase);

Suite *suite_base(void);
Suite *suite_e(void);
Suite *suite_i(void);
Suite *suite_v(void);
Suite *suite_c(void);
Suite *suite_l(void);
Suite *suite_n(void);
Suite *suite_h(void);
Suite *suite_s(void);
Suite *suite_f(void);
Suite *suite_o(void);
Suite *suite_combinations(void);