#include <errno.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void s21_grep(int argc, char **argv);

void scan_files(int argc, char **argv, char **patterns, int *flags, int k);
void seek(char *arg, char **patterns, int *flags, int k, int files_cnt);

char *get_e_pattern_from_args(int argc, char **argv, int i);
char *get_pattern_form_args(int argc, char **argv);
char *get_pattern_file_name_from_args(int argc, char **argv, int i);
void get_patterns_from_files(char **patterns, char **file_names, int f, int *offset, int *flags);
int count_lines(char *filename);
int s21_grep_flags(char *arg, int *flags);