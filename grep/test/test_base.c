#include "s21_grep_test.h"

START_TEST(base_test1) {
    system("grep void void > tmp1");
    system("./s21_grep void void > tmp2");
    ck_assert(system("diff tmp1 tmp2") == 0);
}
END_TEST

START_TEST(base_test2) {
    system("grep Lorem text > tmp1");
    system("./s21_grep Lorem text > tmp2");
    ck_assert(system("diff tmp1 tmp2") == 0);
}
END_TEST

Suite *suite_base(void) {
    Suite *s = suite_create("suite_base");
    TCase *tc = tcase_create("base_tc");

    tcase_add_test(tc, base_test1);
    tcase_add_test(tc, base_test2);

    suite_add_tcase(s, tc);
    return s;
}