#include "s21_grep_test.h"

START_TEST(n_test1) {
    system("grep -n void void v2 > tmp1");
    system("./s21_grep -n void void v2 > tmp2");
    ck_assert(system("diff tmp1 tmp2") == 0);
}
END_TEST

START_TEST(n_test2) {
    system("grep -n void v2 > tmp1");
    system("./s21_grep -n void v2 > tmp2");
    ck_assert(system("diff tmp1 tmp2") == 0);
}
END_TEST

START_TEST(n_test3) {
    system("grep -n void char > tmp1");
    system("./s21_grep -n void char > tmp2");
    ck_assert(system("diff tmp1 tmp2") == 0);
}
END_TEST

Suite *suite_n(void) {
    Suite *s = suite_create("suite_n");
    TCase *tc = tcase_create("n_tc");

    tcase_add_test(tc, n_test1);
    tcase_add_test(tc, n_test2);
    tcase_add_test(tc, n_test3);

    suite_add_tcase(s, tc);
    return s;
}