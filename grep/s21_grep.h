#include <errno.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void s21_grep(int argc, char **argv);

void scan_files(int argc, char **argv, char **patterns, char *pattern_file_name, int *flags, int k);
void seek(char *arg, char **patterns, int *flags, int k);

char *get_pattern_from_args(int argc, char **argv, int i);
char *get_pattern_file_name_from_args(int argc, char **argv, int i);
void get_patterns(char **adr, int argc, char **argv, char *pattern_file_name, int *flags, int k);
void get_patterns_from_file(char **pattern, char *pattern_file_name, int k);
int count_lines(char *filename);
int s21_grep_flags(char *arg, int *flags);