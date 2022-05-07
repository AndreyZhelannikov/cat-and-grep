#include "s21_grep_test.h"

Suite *suite_h(void) {
    Suite *s = suite_create("suite_h");
    TCase *tc = tcase_create("h_tc");

    // tcase_add_test(tc, );

    suite_add_tcase(s, tc);
    return s;
}