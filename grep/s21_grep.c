#include "s21_grep.h"

int main(int argc, char **argv) {
    s21_grep(argc, argv);
    return 0;
}

void s21_grep(int argc, char **argv) {
    char *pattern = NULL;
    char *pattern_file_name = NULL;
    int flags[10] = {0};
    int fail_flags = 0;
    for (int i = 1; i < argc; i++) {
        if (strspn(argv[i], "-")) {
            if (s21_grep_flags(argv[i], flags)) fail_flags = 1;
            if (strchr(argv[i], 'f')) pattern_file_name = get_task_from_args(argc, argv, i, 'f');
            if (strchr(argv[i], 'e')) pattern = get_task_from_args(argc, argv, i, 'e');
        }
    }
    pattern = get_pattern(argc, argv, pattern_file_name, flags);

    if (!fail_flags) {
        for (int i = 1; i < argc; i++) {
            if (!strspn(argv[i], "-") && strcmp(argv[i], pattern)) {
                FILE *fd = fopen(argv[i], "r");
                if (fd) {
                    ;
                } else if (!flags[7]) {
                    perror("");
                }
            }
        }
    } else {
        printf("incorrect flags\n");
    }

    if (flags[8]) free(pattern);
}

char *get_task_from_args(int argc, char **argv, int i, char flag) {
    char *result = NULL;
    if (strchr(argv[i], flag) == argv[i] + strlen(argv[i]) - 1) {
        if (i + 1 < argc) result = argv[i + 1];
    } else
        result = strchr(argv[i], 'f') + 1;
    return result;
}

char *get_pattern(int argc, char **argv, char *pattern_file_name, int *flags) {
    char *pattern = NULL;
    if (flags[8]) {
        pattern = get_pattern_from_file(pattern_file_name);
        if (pattern == NULL && !flags[7]) perror("");
    } else if (!flags[0]) {
        for (int i = 1; i < argc; i++) {
            if (!strspn(argv[i], "-")) {
                pattern = argv[i];
                break;
            }
        }
    }
    return pattern;
}

char *get_pattern_from_file(char *pattern_file_name) {
    char *pattern = NULL;
    FILE *fd = fopen(pattern_file_name, "r");
    size_t size = 0;
    if (fd) {
        getline(&pattern, &size, fd);
    }
    return pattern;
}

// 0 -e  pattern
// 1 -i  Ignore uppercase vs. lowercase.
// 2 -v
// 3 -c
// 4 -l
// 5 -n
// 6 -h
// 7 -s
// 8 -f file
// 9 -o
int s21_grep_flags(char *arg, int *flags) {
    int fail = 0;
    if (strlen(arg) == 1 || strlen(arg) != strspn(arg, "-eivclnhsfo")) fail = 1;
    if (strchr(arg, 'e')) flags[0] = 1;
    if (strchr(arg, 'i')) flags[1] = 1;
    if (strchr(arg, 'v')) flags[2] = 1;
    if (strchr(arg, 'c')) flags[3] = 1;
    if (strchr(arg, 'l')) flags[4] = 1;
    if (strchr(arg, 'n')) flags[5] = 1;
    if (strchr(arg, 'h')) flags[6] = 1;
    if (strchr(arg, 's')) flags[7] = 1;
    if (strchr(arg, 'f')) flags[8] = 1;
    if (strchr(arg, 'o')) flags[9] = 1;
    return fail;
}
