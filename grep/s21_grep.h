#include <errno.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_file {
    char *file_name;
    int mached;
    int mached_all;
    int valid;
} t_file;

typedef struct s_pattern {
    char *pattern;
    int is_file_name;
} t_pattern;

void s21_grep(int argc, char **argv);

void scan_files(int argc, char **argv, char **patterns, int *flags, int k);
void seek(char *arg, char **patterns, int *flags, int k, int files_cnt, t_file *files);
char *get_e_pattern_from_args(int argc, char **argv, int i);
char *get_pattern_form_args(int argc, char **argv);
char *get_pattern_file_name_from_args(int argc, char **argv, int i);
void get_patterns_from_files(char **patterns, char **file_names, int f, int *offset, int *flags);
int count_lines(char *filename);
int s21_grep_flags(char *arg, int *flags);
int the_great_judge(int i, char *argv_i, char *argv_i_1, char *pattern_0, int *same, int *flags);
int do_regcomp(regex_t *regex, int *flags, char *pattern);
int printf_only_match(regex_t *regex, char *line, int line_number, int *flags);
