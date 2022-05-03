#include "s21_cat.h"

int main(int argc, char **argv) {
    s21_cat(argc, argv);

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
    for (int i = 1; i < argc;i++) {
        if (!strspn(argv[i], "-"))
            break;
        s21_flags(argv[i], flags);
    }
    for (int i = 0; i < 6; i++) {
        printf("%d ", flags[i]);
    }
    int fd = 0;
    //FILE *fd = fopen(argv[argc - 1], "r");
    if (fd) {
    } else {
        perror("");
    }
}

void s21_flags(char *arg, int *flags) {
    if (!strcmp(arg, "--number-nonblank"))
        flags[0] = 1;
    else if (!strcmp(arg, "--number"))
        flags[3] = 1;
    else if (!strcmp(arg, "--squeeze-blank"))
        flags[4] = 1;
    else {
        if (strchr(arg, 'b'))
            flags[0] = 1;
        if (strchr(arg, 'v'))
            flags[1] = 1;
        if (strchr(arg, 'E'))
            flags[2] = 1;
        if (strchr(arg, 'n'))
            flags[3] = 1;
        if (strchr(arg, 's'))
            flags[4] = 1;
        if (strchr(arg, 'T'))
            flags[5] = 1;
        if (strchr(arg, 'e')) {
            flags[1] = 1;
            flags[2] = 1;
        }
        if (strchr(arg, 't')) {
            flags[1] = 1;
            flags[5] = 1;
        }
    }
}