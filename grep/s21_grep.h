#include <errno.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define E 0
#define I 1
#define V 2
#define C 3
#define L 4
#define N 5
#define H 6
#define S 7
#define F 8
#define O 9

typedef struct s_file {
    char *file_name;
    int mached;
    int mached_all;
    int valid;
} t_file;

typedef struct s_pattern {
    char *name;
    int is_file;
    char *file_name;
    int is_default;
} t_pattern;

void s21_grep(int argc, char **argv);

// old
// void scan_files(int argc, char **argv, char **patterns, int *flags, int k);
void seek(char *arg, char **patterns, int *flags, int k, int files_cnt, t_file *files);
// char *get_e_pattern(int argc, char **argv, int i);
char *get_pattern_form_args(int argc, char **argv);
// char *get_pattern_file_name_from_args(int argc, char **argv, int i);
void get_patterns_from_files(char **patterns, char **file_names, int f, int *offset, int *flags);
int count_lines(char *filename);
int the_great_judge(int i, char *argv_i, char *argv_i_1, char *pattern_0, int *same, int *flags);
int do_regcomp(regex_t *regex, int *flags, char *pattern);
int printf_only_match(regex_t *regex, char *line, int line_number, int *flags);

// new

void init_patterns(t_pattern *patterns, int size);
void init_files(t_file *files, int size);

void get_grep_flags(int argc, char **argv, int *flags, t_pattern *patterns, int *patterns_cnt);
int get_flags_from_argv(char *arg, int *flags);

char *get_pattern_file_name(int argc, char **argv, int i);
char *get_e_pattern(int argc, char **argv, int i);

void scan_files(int argc, char **argv, t_pattern *patterns, int patterns_cnt, int *flags);
int is_arg_a_file(int i, char **argv, t_pattern *patterns, int patterns_cnt, int *same, int *flags);
int cnt_files(int argc, char **argv, t_pattern *patterns, int patterns_cnt, int *flags);
char *get_default_pattern(int argc, char **argv);
void get_files(int argc, char **argv, t_pattern *patterns, int patterns_cnt, t_file *files, int files_cnt,
               int *flags);
void files_processing(t_pattern *patterns, int patterns_cnt, t_file *files, int files_cnt, int *flags);
int seek_in_file(FILE *fd, t_pattern *patterns, int patterns_cnt, int *flags, t_file *file, int files_cnt);
void print_match(char *line, int *flags, t_file *file, int files_cnt, int line_number, int *one_time_print);

void print_files_c(t_file *file, int files_cnt, int maching_lines, int *flags);

void print_files_l(t_file *file, int files_cnt, int maching_lines, int *flags);
void seek_file_patterns(char *line, t_pattern *pattern, t_file *file, int *flags, int *matching_lines,
                        int files_cnt, int line_number, int *one_time_print);
void seek_pattern(char *line, t_pattern pattern, t_file *file, int *flags, int *matching_lines, int files_cnt,
                  int line_number, int *one_time_print);