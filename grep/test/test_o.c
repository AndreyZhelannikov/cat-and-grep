#include "s21_grep_test.h"

Suite *suite_o(void) {
    Suite *s = suite_create("suite_o");
    TCase *tc = tcase_create("o_tc");

    // tcase_add_test(tc, );

    suite_add_tcase(s, tc);
    return s;
}