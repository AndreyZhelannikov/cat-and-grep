#include "s21_grep.h"

int main(int argc, char **argv) {
    if (argc > 2) {
        s21_grep(argc, argv);
    } else {
        printf("Not enough arguments\n");
    }
    return 0;
}

void s21_grep(int argc, char **argv) {
    t_pattern patterns[argc];
    init_patterns(patterns, argc);
    int patterns_cnt = 0;
    int flags[10] = {0};

    get_grep_flags(argc, argv, flags, patterns, &patterns_cnt);
    scan_files(argc, argv, patterns, patterns_cnt, flags);
}

void scan_files(int argc, char **argv, t_pattern *patterns, int patterns_cnt, int *flags) {
    int files_cnt = cnt_files(argc, argv, patterns, patterns_cnt, flags);
    if (files_cnt) {
        t_file files[files_cnt];
        init_files(files, files_cnt);
        get_files(argc, argv, patterns, patterns_cnt, files, files_cnt, flags);
        files_processing(patterns, patterns_cnt, files, files_cnt, flags);
    } else {
        printf("No files found");
    }
}

void files_processing(t_pattern *patterns, int patterns_cnt, t_file *files, int files_cnt, int *flags) {
    int maching_lines = 0;
    for (int i = 0; i < files_cnt; i++) {
        FILE *fd = fopen(files[i].file_name, "r");
        if (fd) {
            maching_lines = seek_in_file(fd, patterns, patterns_cnt, flags, files + i, files_cnt);
            fclose(fd);
        } else {
            files[i].valid = 0;
        }
        if (flags[C]) print_files_c(files + i, files_cnt, maching_lines, flags);
        if (flags[L]) print_files_l(files + i, files_cnt, maching_lines, flags);
    }
}
void print_files_c(t_file *file, int files_cnt, int maching_lines, int *flags) {
    if (!flags[H] && files_cnt > 1) printf("%s:", file->file_name);
    if (!flags[L])
        printf("%d\n", maching_lines);
    else
        printf("%d\n", maching_lines > 0 ? 1 : 0);
}

void print_files_l(t_file *file, int files_cnt, int maching_lines, int *flags) {
    if (maching_lines > 0) printf("%s\n", file->file_name);
}

int seek_in_file(FILE *fd, t_pattern *patterns, int patterns_cnt, int *flags, t_file *file, int files_cnt) {
    int matching_lines = 0;
    int line_number = 0;
    size_t size = 0;
    char *line = NULL;
    while (getline(&line, &size, fd) != -1) {
        int one_time_print = 1;
        line_number++;
        trim_n(line);
        for (int i = 0; i < patterns_cnt; i++) {
            seek_choice(line, patterns + i, file, flags, &matching_lines, files_cnt, line_number,
                        &one_time_print);
        }
    }
    return matching_lines;
}

void seek_choice(char *line, t_pattern *pattern, t_file *file, int *flags, int *matching_lines, int files_cnt,
                 int line_number, int *one_time_print) {
    if (flags[V] && flags[O]) {
        //
    } else if (flags[O]) {
        //
    } else if (flags[V]) {
        //
    } else {
        if (pattern->is_file)
            seek_file_patterns(line, pattern, file, flags, matching_lines, files_cnt, line_number,
                               one_time_print);
        else
            seek_pattern(line, *pattern, file, flags, matching_lines, files_cnt, line_number, one_time_print);
    }
}

/*
void seek_v_pattern(char *line, t_pattern pattern, t_file *file, int *flags, int *matching_lines,
                    int files_cnt, int line_number, int *one_time_print) {
    //
    regex_t regex;
    trim_n(pattern.name);
    int comp_val = do_regcomp(&regex, flags, pattern.name);
    if (!comp_val) {
        int exec_val = regexec(&regex, line, 0, NULL, 0);
        if (exec_val == REG_NOMATCH) {
            print_match(line, flags, file, files_cnt, line_number, one_time_print, matching_lines);
        }
    } else {
        printf("Regex comp. fail\n");
    }
    regfree(&regex);
}
*/
void seek_file_patterns(char *line, t_pattern *pattern, t_file *file, int *flags, int *matching_lines,
                        int files_cnt, int line_number, int *one_time_print) {
    FILE *fd = fopen(pattern->file_name, "r");
    if (fd) {
        char *file_line = NULL;
        size_t file_line_size = 0;
        while (getline(&file_line, &file_line_size, fd) != -1) {
            pattern->name = file_line;
            seek_pattern(line, *pattern, file, flags, matching_lines, files_cnt, line_number, one_time_print);
        }
        free(file_line);
        fclose(fd);
    } else {
        printf("No such file or directory\n");
    }
}

void seek_pattern(char *line, t_pattern pattern, t_file *file, int *flags, int *matching_lines, int files_cnt,
                  int line_number, int *one_time_print) {
    regex_t regex;
    trim_n(pattern.name);
    int comp_val = do_regcomp(&regex, flags, pattern.name);
    if (!comp_val) {
        int exec_val = regexec(&regex, line, 0, NULL, 0);
        if (exec_val == 0) {
            print_match(line, flags, file, files_cnt, line_number, one_time_print, matching_lines);
        }
    } else {
        printf("Regex comp. fail\n");
    }
    regfree(&regex);
}

// void seek_in_file_o(FILE *fd, t_pattern *patterns, int patterns_cnt, int *flags, t_file *file) {
// }

void print_match(char *line, int *flags, t_file *file, int files_cnt, int line_number, int *one_time_print,
                 int *maching_lines) {
    if (!flags[C] && !flags[L] && *one_time_print) {
        if (strlen(line) == 1 && line[0] == '.') line[0] = '\0';
        if (!flags[H] && files_cnt > 1) printf("%s:", file->file_name);
        if (flags[N]) printf("%d:", line_number);
        printf("%s\n", line);
    }
    if (*one_time_print) (*maching_lines)++;
    *one_time_print = 0;
}

void trim_n(char *line) {
    if (strlen(line) == 1 && line[0] == '\n') line[0] = '.';
    if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
}

void get_files(int argc, char **argv, t_pattern *patterns, int patterns_cnt, t_file *files, int files_cnt,
               int *flags) {
    int same = 0;
    int k = 0;
    for (int i = 1; i < argc; i++) {
        if (is_arg_a_file(i, argv, patterns, patterns_cnt, &same, flags)) files[k++].file_name = argv[i];
    }
}

int do_regcomp(regex_t *regex, int *flags, char *pattern) {
    int comp_val;
    if (flags[1])
        comp_val = regcomp(regex, pattern, REG_ICASE);
    else
        comp_val = regcomp(regex, pattern, 0);
    return comp_val;
}

int cnt_files(int argc, char **argv, t_pattern *patterns, int patterns_cnt, int *flags) {
    int res = 0;
    int same = 0;
    for (int i = 1; i < argc; i++)
        if (is_arg_a_file(i, argv, patterns, patterns_cnt, &same, flags)) res++;
    return res;
}

int is_arg_a_file(int i, char **argv, t_pattern *patterns, int patterns_cnt, int *same, int *flags) {
    return (!strspn(argv[i], "-") &&
            !((strchr(argv[i], 'f') && strspn(argv[i], "-")) ||
              (i != 1 && argv[i - 1][strlen(argv[i - 1]) - 1] == 'f' && strspn(argv[i - 1], "-")) ||
              (strchr(argv[i], 'e') && strspn(argv[i], "-")) ||
              (i != 1 && argv[i - 1][strlen(argv[i - 1]) - 1] == 'e' && strspn(argv[i - 1], "-")) ||
              (!(flags[8] || flags[0]) && !strcmp(argv[i], patterns[0].name) && ((*same)--) >= 0)));
}

char *get_default_pattern(int argc, char **argv) {
    char *res = NULL;
    for (int i = 1; i < argc; i++) {
        if (!strspn(argv[i], "-")) {
            res = argv[i];
            break;
        }
    }
    return res;
}

char *get_e_pattern(int argc, char **argv, int i) {
    char *res = NULL;
    if (strchr(argv[i], 'e') == argv[i] + strlen(argv[i]) - 1) {
        if (i + 1 < argc) res = argv[i + 1];
    } else
        res = strchr(argv[i], 'e') + 1;
    return res;
}

char *get_pattern_file_name(int argc, char **argv, int i) {
    char *res = NULL;
    if (strchr(argv[i], 'f') == argv[i] + strlen(argv[i]) - 1) {
        if (i + 1 < argc) res = argv[i + 1];
    } else
        res = strchr(argv[i], 'f') + 1;
    return res;
}

void init_patterns(t_pattern *patterns, int size) {
    for (int i = 0; i < size; i++) {
        patterns[i].is_default = 0;
        patterns[i].is_file = 0;
        patterns[i].file_name = NULL;
        patterns[i].name = NULL;
    }
}

void init_files(t_file *files, int size) {
    for (int i = 0; i < size; i++) {
        files[i].mached = 0;
        files[i].mached_all = 0;
        files[i].valid = 0;
        files[i].file_name = NULL;
    }
}

void get_grep_flags(int argc, char **argv, int *flags, t_pattern *patterns, int *patterns_cnt) {
    int e = 0, f = 0;
    for (int i = 1; i < argc; i++) {
        if (strspn(argv[i], "-")) {
            get_flags_from_argv(argv[i], flags);
            if (strchr(argv[i], 'f')) {
                f++;
                patterns[*patterns_cnt].is_default = 0;
                patterns[*patterns_cnt].is_file = 1;
                patterns[*patterns_cnt].file_name = get_pattern_file_name(argc, argv, i);
                (*patterns_cnt)++;
            }
            if (strchr(argv[i], 'e')) {
                e++;
                patterns[*patterns_cnt].is_default = 0;
                patterns[*patterns_cnt].is_file = 0;
                patterns[*patterns_cnt].name = get_e_pattern(argc, argv, i);
                (*patterns_cnt)++;
            }
        }
    }
    if (e == 0 && f == 0) {
        patterns[*patterns_cnt].is_file = 0;
        patterns[*patterns_cnt].is_default = 1;
        patterns[*patterns_cnt].name = get_default_pattern(argc, argv);
        (*patterns_cnt)++;
    }
}

int get_flags_from_argv(char *arg, int *flags) {
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