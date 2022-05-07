#include "s21_grep_test.h"

START_TEST(h_test1) {
    system("grep -h void v2 void > tmp1");
    system("./s21_grep -h void v2 void > tmp2");
    ck_assert(system("diff tmp1 tmp2") == 0);
}
END_TEST

Suite *suite_h(void) {
    Suite *s = suite_create("suite_h");
    TCase *tc = tcase_create("h_tc");

    tcase_add_test(tc, h_test1);

    suite_add_tcase(s, tc);
    return s;
}