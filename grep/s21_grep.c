#include "s21_grep.h"

int main(int argc, char **argv) {
    if (argc > 1) {
        s21_grep(argc, argv);
    } else {
        printf("Not enough arguments\n");
    }
    return 0;
}

void s21_grep(int argc, char **argv) {
    char *pattern = NULL;
    char **patterns = NULL;
    char *pattern_file_name = NULL;
    int k = 0;
    int flags[10] = {0};
    int fail_flags = 0;
    for (int i = 1; i < argc; i++) {
        if (strspn(argv[i], "-")) {
            if (s21_grep_flags(argv[i], flags)) fail_flags = 1;
            if (strchr(argv[i], 'f')) {
                pattern_file_name = get_pattern_file_name_from_args(argc, argv, i);
            }
            if (strchr(argv[i], 'e')) pattern = get_pattern_from_args(argc, argv, i);
        }
    }
    k = pattern_file_name ? count_lines(pattern_file_name) : 1;
    if (k) {
        patterns = malloc(sizeof(char *) * k);
        if (patterns) {
            for (int i = 0; i < k; i++) patterns[i] = NULL;
            patterns[0] = pattern;
            get_patterns(patterns, argc, argv, pattern_file_name, flags, k);
            if (!fail_flags)
                scan_files(argc, argv, patterns, pattern_file_name, flags, k);
            else
                printf("incorrect flags\n");
            if (flags[8])
                for (int i = 0; i < k; i++) free(patterns[i]);
            free(patterns);
        } else {
            printf("malloc failed\n");
        }
    } else {
        if (!flags[7]) perror("");
    }
}

void scan_files(int argc, char **argv, char **patterns, char *pattern_file_name, int *flags, int k) {
    int fail = 1;
    for (int i = 1; i < argc; i++) {
        if (!strspn(argv[i], "-") && strcmp(argv[i], patterns[0]) &&
            !(pattern_file_name && strcmp(argv[i], pattern_file_name))) {
            seek(argv[i], patterns, flags, k);
            fail = 0;
        }
    }
    if (fail) printf("No files found\n");  // read form stdin maybe ?
}

void seek(char *arg, char **patterns, int *flags, int k) {
    int line_number = 0;
    size_t size;
    FILE *fd = fopen(arg, "r");
    if (fd) {
        for (int i = 0; i < k; i++) {
            regex_t regex;
            if (!regcomp(&regex, patterns[i], 0)) {
                int file_len = count_lines(arg);
                for (int i = 0; i < file_len; i++) {
                    char *line = NULL;
                    if (getline(&line, &size, fd) != -1) {
                        if (regexec(&regex, line, 0, NULL, 0) == 0) {
                            if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
                            printf("%s\n", line);
                        }
                    }
                    free(line);
                }
                regfree(&regex);
            } else {
                printf("Regex compilation error");
            }
        }
        line_number++;
    } else if (!flags[7]) {
        perror("");
    }
}

char *get_pattern_from_args(int argc, char **argv, int i) {
    char *res = NULL;
    if (strchr(argv[i], 'e') == argv[i] + strlen(argv[i]) - 1) {
        if (i + 1 < argc) res = argv[i + 1];
    } else
        res = strchr(argv[i], 'e') + 1;
    return res;
}

char *get_pattern_file_name_from_args(int argc, char **argv, int i) {
    char *res = NULL;
    if (strchr(argv[i], 'f') == argv[i] + strlen(argv[i]) - 1) {
        if (i + 1 < argc) res = argv[i + 1];
    } else
        res = strchr(argv[i], 'f') + 1;
    return res;
}

void get_patterns(char **patterns, int argc, char **argv, char *pattern_file_name, int *flags, int k) {
    if (flags[8]) {
        get_patterns_from_file(patterns, pattern_file_name, k);
        if (patterns[0] == NULL && !flags[7]) perror("");
    } else if (!flags[0]) {
        for (int i = 1; i < argc; i++) {
            if (!strspn(argv[i], "-")) {
                patterns[0] = argv[i];
                break;
            }
        }
    }
}

void get_patterns_from_file(char **patterns, char *pattern_file_name, int k) {
    for (int i = 0; i < k; i++) patterns[i] = NULL;
    FILE *fd = fopen(pattern_file_name, "r");
    size_t size = 0;
    if (fd)
        for (int i = 0; i < k; i++) {
            getline(&patterns[i], &size, fd);
            if (patterns[i][strlen(patterns[i]) - 1] == '\n') patterns[i][strlen(patterns[i]) - 1] = '\0';
        }
}

int count_lines(char *filename) {
    int cnt = 0;
    char c;
    FILE *fd = fopen(filename, "r");
    if (fd) {
        cnt++;
        while ((c = fgetc(fd)) != EOF)
            if (c == '\n') cnt++;
        fclose(fd);
    }
    return cnt;
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
