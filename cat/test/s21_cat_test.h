#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void start_tests(void);
void file_gen(void);

static const char *const s21_mac_flags[6] = {
    [0] = " -b ", [1] = " -e ", [2] = " -v ", [3] = " -n ", [4] = " -s ", [5] = " -t "};

static const char *const s21_GNU_flags[5] = {
    [0] = " --number-nonblank ", [1] = " -E ", [2] = " --number ", [3] = " --squeeze-blank ", [4] = " -T ",
};