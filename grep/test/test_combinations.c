#include "s21_grep_test.h"

START_TEST(test_combinations) {
    char f_file[] = " void ";
    char e_pattern[] = " void ";
    char search_files[] = " v2 void char";
    char search_pattern[] = " void ";
    char grep[512] = "grep ";
    char s21_grep[512] = "./s21_grep ";
    char flags[512] = "";
    if (_i >> 0 & 1) {
        strcat(flags, s21_grep_flags[0]);
        strcat(flags, e_pattern);
    }
    if (_i >> 1 & 1) strcat(flags, s21_grep_flags[1]);
    if (_i >> 2 & 1) strcat(flags, s21_grep_flags[2]);
    if (_i >> 3 & 1) strcat(flags, s21_grep_flags[3]);
    if (_i >> 4 & 1) strcat(flags, s21_grep_flags[4]);
    if (_i >> 5 & 1) strcat(flags, s21_grep_flags[5]);
    if (_i >> 6 & 1) strcat(flags, s21_grep_flags[6]);
    if (_i >> 7 & 1) strcat(flags, s21_grep_flags[7]);
    /*if (_i >> 8 & 1) {
        strcat(flags, s21_grep_flags[8]);
        strcat(flags, f_file);
    }*/
    if (_i >> 9 & 1) strcat(flags, s21_grep_flags[9]);
    if (!(_i >> 0 & 1)) strcat(flags, search_pattern);
    strcat(grep, flags);
    strcat(grep, search_files);
    strcat(s21_grep, flags);
    strcat(s21_grep, search_files);
    strcat(grep, " > tmp1");
    strcat(s21_grep, " > tmp2");

    printf("\nCURRENT TEST: %d\n%s%s\n%s%s\n", _i, BLUE, grep, s21_grep, RESET);
    system(grep);
    system(s21_grep);
    int val = system("diff tmp1 tmp2");
    printf("\nCURRENT TEST: %d\n%s%s\n%s%s\nSUCCESS: %s%d%s\n", _i, BLUE, grep, s21_grep, RESET,
           !val ? GREEN : RED, val, RESET);
    char str[2048];
    sprintf(str, "\nTEST N:%d\n%s%s\n%s%s\n", _i, BLUE, grep, s21_grep, RESET);
    ck_assert_msg(val == 0, str);
}
END_TEST

Suite *suite_combinations(void) {
    Suite *s = suite_create("suite_combinations");
    TCase *tc = tcase_create("combinations_tc");

    tcase_add_loop_test(tc, test_combinations, 0, 1024);

    suite_add_tcase(s, tc);
    return s;
}