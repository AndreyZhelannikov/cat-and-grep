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
    char *e_patterns[(argc - 1) / 2];
    char *file_names[(argc - 1) / 2];
    int k = 0, f = 0, e = 0;
    int flags[10] = {0};
    int fail_flags = 0;
    for (int i = 1; i < argc; i++)
        if (strspn(argv[i], "-")) {
            if (s21_grep_flags(argv[i], flags)) fail_flags = 1;
            if (strchr(argv[i], 'f')) file_names[f++] = get_pattern_file_name_from_args(argc, argv, i);
            if (strchr(argv[i], 'e')) e_patterns[e++] = get_e_pattern_from_args(argc, argv, i);
        }
    int offset = k = e;
    k += (e == 0 && f == 0);
    for (int i = 0; i < f; i++) k += count_lines(file_names[i]);
    if (k) {
        char **patterns = malloc(sizeof(char *) * (k));
        if (patterns) {
            for (int i = 0; i < k; i++) patterns[i] = NULL;
            for (int i = 0; i < e; i++) patterns[i] = e_patterns[i];
            if (flags[8])
                get_patterns_from_files(patterns, file_names, f, &offset, flags);
            else if (e == 0)
                patterns[offset] = get_pattern_form_args(argc, argv);
            if (patterns[0]) scan_files(argc, argv, patterns, flags, k);
            if (flags[8])
                for (int i = e; i < k; i++) free(patterns[i]);
            free(patterns);
        } else {
            printf("malloc failed\n");
        }
    } else {
        if (!flags[7]) perror("");
    }
}

void scan_files(int argc, char **argv, char **patterns, int *flags, int k) {
    int fail = 1;
    int files_cnt = 0;
    int same = 0;
    for (int i = 1; i < argc; i++) {
        if (!strspn(argv[i], "-") &&
            !((strchr(argv[i], 'f') && strspn(argv[i], "-")) ||
              (i != 1 && argv[i - 1][strlen(argv[i - 1]) - 1] == 'f' && strspn(argv[i - 1], "-")) ||
              (strchr(argv[i], 'e') && strspn(argv[i], "-")) ||
              (i != 1 && argv[i - 1][strlen(argv[i - 1]) - 1] == 'e' && strspn(argv[i - 1], "-")) ||
              (!(flags[8] || flags[0]) && !strcmp(argv[i], patterns[0]) && (same--) >= 0))) {
            fail = 0;
            files_cnt++;
        }
    }
    same = 0;
    for (int i = 1; i < argc; i++) {
        if (!strspn(argv[i], "-") &&
            !((strchr(argv[i], 'f') && strspn(argv[i], "-")) ||
              (i != 1 && argv[i - 1][strlen(argv[i - 1]) - 1] == 'f' && strspn(argv[i - 1], "-")) ||
              (strchr(argv[i], 'e') && strspn(argv[i], "-")) ||
              (i != 1 && argv[i - 1][strlen(argv[i - 1]) - 1] == 'e' && strspn(argv[i - 1], "-")) ||
              (!(flags[8] || flags[0]) && !strcmp(argv[i], patterns[0]) && (same--) >= 0))) {
            seek(argv[i], patterns, flags, k, files_cnt);
        }
        if (fail) printf("No files found\n");  // read form stdin maybe ?
    }
}

void seek(char *arg, char **patterns, int *flags, int k, int files_cnt) {
    int line_number = 0;
    int line_mached = 0;
    int files_mached = 0;
    size_t size;
    FILE *fd = fopen(arg, "r");
    if (fd) {
        char *line = NULL;
        char *mached_files[files_cnt];
        int file_len = count_lines(arg);
        regex_t regex;
        for (int i = 0; i < file_len; i++) {
            if (getline(&line, &size, fd) != -1) {
                line_number++;
                if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
                for (int i = 0; i < k; i++) {
                    int one_time_mach_flag = 1;
                    int one_time_printf_file_flag = 1;
                    int comp_val;
                    if (flags[1])
                        comp_val = regcomp(&regex, patterns[i], REG_ICASE);
                    else
                        comp_val = regcomp(&regex, patterns[i], 0);
                    if (!comp_val) {
                        int exec_val;
                        exec_val = regexec(&regex, line, 0, NULL, 0);
                        if ((!flags[2] && !exec_val) || (flags[2] && exec_val == REG_NOMATCH)) {
                            if (one_time_mach_flag) {
                                one_time_mach_flag = 0;
                                line_mached++;
                            }
                            if (flags[4] && one_time_printf_file_flag) {
                                one_time_printf_file_flag = 0;
                                mached_files[files_mached++] = arg;
                            } else if (!flags[3] && !flags[4]) {
                                if (files_cnt > 1) printf("%s:", arg);
                                printf("%s\n", line);
                            }
                        }
                    }
                }
            }
        }
        regfree(&regex);
        free(line);
        fclose(fd);
        if (flags[4]) {
            printf("%d", files_mached);
            for (int i = 0; i < files_mached; i++) printf("%s\n", mached_files[i]);
        } else if (flags[3]) {
            printf("%d\n", line_mached);
        }
    } else if (!flags[7]) {
        perror("");
    }
}

char *get_e_pattern_from_args(int argc, char **argv, int i) {
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

char *get_pattern_form_args(int argc, char **argv) {
    char *res = NULL;
    for (int i = 1; i < argc; i++) {
        if (!strspn(argv[i], "-")) {
            res = argv[i];
            break;
        }
    }
    return res;
}
void get_patterns_from_files(char **patterns, char **file_names, int f, int *offset, int *flags) {
    for (int i = 0; i < f; i++) {
        int start = *offset;
        int len = count_lines(file_names[i]);
        FILE *fd = fopen(file_names[i], "r");
        size_t size = 0;
        if (fd) {
            for (int i = start; i < start + len; i++) {
                getline(&patterns[i], &size, fd);
                if (patterns[i][strlen(patterns[i]) - 1] == '\n') patterns[i][strlen(patterns[i]) - 1] = '\0';
                (*offset)++;
            }
            fclose(fd);
        } else if (flags[7]) {
            perror("");
            break;
        }
    }
}

int count_lines(char *filename) {
    int cnt = 0;
    if (filename) {
        char c;
        FILE *fd = fopen(filename, "r");
        if (fd) {
            cnt++;
            while ((c = fgetc(fd)) != EOF)
                if (c == '\n') cnt++;
            fclose(fd);
        }
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
