#include "s21_grep_test.h"

START_TEST(o_test1) {
    system("grep -o void v2 > tmp1");
    system("./s21_grep -o void v2 > tmp2");
    ck_assert(system("diff tmp1 tmp2") == 0);
}
END_TEST

START_TEST(o_test2) {
    system("grep -o void v2 void > tmp1");
    system("./s21_grep -o void v2 void > tmp2");
    ck_assert(system("diff tmp1 tmp2") == 0);
}
END_TEST

START_TEST(o_test3) {
    system("grep -o void char v2 void > tmp1");
    system("./s21_grep -o void char v2 void > tmp2");
    ck_assert(system("diff tmp1 tmp2") == 0);
}
END_TEST

START_TEST(o_test4) {
    system("grep -o char v2 void > tmp1");
    system("./s21_grep -o char v2 void > tmp2");
    ck_assert(system("diff tmp1 tmp2") == 0);
}
END_TEST

Suite *suite_o(void) {
    Suite *s = suite_create("suite_o");
    TCase *tc = tcase_create("o_tc");

    tcase_add_test(tc, o_test1);
    tcase_add_test(tc, o_test2);
    tcase_add_test(tc, o_test3);
    tcase_add_test(tc, o_test4);

    suite_add_tcase(s, tc);
    return s;
}