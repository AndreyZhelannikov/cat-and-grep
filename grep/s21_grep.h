#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void s21_grep(int argc, char **argv);
int s21_grep_flags(char *arg, int *flags);
char *get_pattern(int argc, char **argv);
char *get_pattern_from_file(char *pattern_file_name);