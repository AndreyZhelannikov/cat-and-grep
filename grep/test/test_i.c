#include "s21_grep_test.h"

START_TEST(i_test1) {
    system("grep -i void void > tmp1");
    system("./s21_grep -i void void > tmp2");
    ck_assert(system("diff tmp1 tmp2") == 0);
}
END_TEST

Suite *suite_i(void) {
    Suite *s = suite_create("suite_i");
    TCase *tc = tcase_create("i_tc");

    tcase_add_test(tc, i_test1);

    suite_add_tcase(s, tc);
    return s;
}