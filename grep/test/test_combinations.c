#include "s21_grep_test.h"

Suite *suite_combinations(void) {
    Suite *s = suite_create("suite_combinations");
    TCase *tc = tcase_create("combinations_tc");

    // tcase_add_test(tc, );

    suite_add_tcase(s, tc);
    return s;
}