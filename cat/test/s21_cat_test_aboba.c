#include "s21_cat_test.h"

int main(void) {
    start_tests();
    return 0;
}

void start_tests() {
    file_gen();
    printf("%d\n", system("cat cat/test/tmp_test_file > tmp1.txt"));
    printf("%d\n", system("./s21_cat cat/test/tmp_test_file > tmp2.txt"));
    printf("%d\n", system("diff tmp1.txt tmp2.txt"));
}

void file_gen(void) {
    int len = rand();
    FILE *fd = fopen("cat/test/tmp_test_file", "w");
    if (fd) {
        for (int i = 0; i < len; i++) {
            fputc((unsigned int)((rand() % 127 + 44) % 127), fd);
        }
        fclose(fd);
    } else {
        perror("");
    }
}