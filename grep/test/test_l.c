#include "s21_grep_test.h"

Suite *suite_l(void) {
    Suite *s = suite_create("suite_l");
    TCase *tc = tcase_create("l_tc");

    // tcase_add_test(tc, );

    suite_add_tcase(s, tc);
    return s;
}