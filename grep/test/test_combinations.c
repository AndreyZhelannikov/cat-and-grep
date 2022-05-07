#include "s21_grep_test.h"

START_TEST(test_combinations_1) {
    system("grep -e void -i -v -c -l -n -h -s -o -f void -f char void v2 char > tmp1");
    system("./s21_grep grep -e void -i -v -c -l -n -h -s -o -f void -f char void v2 char > tmp2");
    ck_assert(system("diff tmp1 tmp2") == 0);
}
END_TEST

Suite *suite_combinations(void) {
    Suite *s = suite_create("suite_combinations");
    TCase *tc = tcase_create("combinations_tc");

    tcase_add_test(tc, test_combinations_1);

    suite_add_tcase(s, tc);
    return s;
}