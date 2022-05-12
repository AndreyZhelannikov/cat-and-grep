#include "s21_cat.h"

int main(int argc, char **argv) {
    if (argc > 1)
        s21_cat(argc, argv);
    else
        printf("Not enough arguments\n");
    return 0;
}

// -b == --number-nonblank
// -e == -vE
// -E
// -v
// -n == --number
// -s == --squeeze-blank
// -t == -vT
// -T

// -b
// -v
// -E
// -n
// -s
// -T

void s21_cat(int argc, char **argv) {
    int flags[6] = {0};
    int fail_flags = 0;
    int i = 1;
    for (; i < argc; i++) {
        if (strspn(argv[i], "-") == 0) break;
        if (s21_cat_flags(argv[i], flags) == 1) fail_flags = 1;
    }
    if (flags[0]) flags[3] = 0;
    if (!fail_flags && i == argc) printf("Please enter the file name\n");
    for (; !fail_flags && i < argc; i++) {
        FILE *fd = fopen(argv[i], "r");
        if (fd) {
            int start_line_flag = 1;
            int counter_b = 1;
            int counter_n = 1;
            char prew = '\n';
            char prew_prew = '\n';
            char c[5] = {'\0'};
            while ((*c = fgetc(fd)) != EOF) {
                if (flags[4] && apply_flag_s(prew_prew, prew, *c)) continue;
                if (flags[3]) start_line_flag = apply_flag_n(start_line_flag, *c, &counter_n);
                if (flags[0]) apply_flag_b(prew, *c, &counter_b);
                if (flags[2]) apply_flag_E(*c);
                if (flags[1]) apply_flag_v(c);
                prew_prew = prew;
                prew = *c;
                if (flags[5] && apply_flag_T(*c)) continue;
                if (*c == '\0')
                    fputc(*c, stdout);
                else
                    fputs(c, stdout);
                memset(c, '\0', 5);
            }
        } else {
            perror("");
        }
    }
    if (fail_flags) printf("incorrect flags\n");
}

void apply_flag_b(char prew, char c, int *counter_b) {
    if (prew == '\n' && c != '\n') printf("%6d\t", (*counter_b)++);
}

void apply_flag_v(char *c) {
    unsigned char uc = *c;
    if (is_special(uc)) strcpy(c, s21_cat_spec_symbols[uc]);
}

int is_special(unsigned char c) { return (c <= 8) || (c >= 11 && c <= 31) || (c >= 127 && c <= 159); }

void apply_flag_E(char c) {
    if (c == '\n') putc('$', stdout);
}

int apply_flag_T(char c) {
    int res = 0;
    if (c == '\t') res = printf("^I");
    return res;
}

int apply_flag_n(int start_line_flag, char c, int *counter_n) {
    if (start_line_flag) printf("%6d\t", (*counter_n)++);
    return (c == '\n');
}

int apply_flag_s(char prew_prew, char prew, char c) { return c == '\n' && prew == '\n' && prew_prew == '\n'; }

int s21_cat_flags(char *arg, int *flags) {
    int fail = 0;
    if (strlen(arg) == 1 || strlen(arg) != strspn(arg, "-bvEnsTet")) fail = 1;
    if (!strcmp(arg, "--number-nonblank")) {
        flags[0] = 1;
        fail = 0;
    } else if (!strcmp(arg, "--number")) {
        flags[3] = 1;
        fail = 0;
    } else if (!strcmp(arg, "--squeeze-blank")) {
        flags[4] = 1;
        fail = 0;
    } else {
        if (strchr(arg, 'b')) flags[0] = 1;
        if (strchr(arg, 'v')) flags[1] = 1;
        if (strchr(arg, 'E')) flags[2] = 1;
        if (strchr(arg, 'n')) flags[3] = 1;
        if (strchr(arg, 's')) flags[4] = 1;
        if (strchr(arg, 'T')) flags[5] = 1;
        if (strchr(arg, 'e')) {
            flags[1] = 1;
            flags[2] = 1;
        }
        if (strchr(arg, 't')) {
            flags[1] = 1;
            flags[5] = 1;
        }
    }
    return fail;
}
