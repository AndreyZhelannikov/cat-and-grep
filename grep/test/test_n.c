#include "s21_grep_test.h"

Suite *suite_n(void) {
    Suite *s = suite_create("suite_n");
    TCase *tc = tcase_create("n_tc");

    // tcase_add_test(tc, );

    suite_add_tcase(s, tc);
    return s;
}