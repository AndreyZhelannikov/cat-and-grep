#include "s21_grep_test.h"

START_TEST(v_test1) {
    system("grep -c void void > tmp1");
    system("./s21_grep -c void void > tmp2");
    ck_assert(system("diff tmp1 tmp2") == 0);
}
END_TEST

START_TEST(v_test2) {
    system("grep -c -i void void > tmp1");
    system("./s21_grep -c -i void void > tmp2");
    ck_assert(system("diff tmp1 tmp2") == 0);
}
END_TEST

Suite *suite_c(void) {
    Suite *s = suite_create("suite_c");
    TCase *tc = tcase_create("c_tc");

    tcase_add_test(tc, v_test1);
    tcase_add_test(tc, v_test2);

    suite_add_tcase(s, tc);
    return s;
}