#include "s21_grep_test.h"

START_TEST(v_test1) {
    system("grep -v Lorem text > tmp1");
    system("./s21_grep -v Lorem text > tmp2");
    ck_assert(system("diff tmp1 tmp2") == 0);
}
END_TEST

Suite *suite_v(void) {
    Suite *s = suite_create("suite_v");
    TCase *tc = tcase_create("v_tc");

    tcase_add_test(tc, v_test1);

    suite_add_tcase(s, tc);
    return s;
}