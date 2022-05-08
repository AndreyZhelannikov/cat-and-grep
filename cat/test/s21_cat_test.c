#include "s21_cat_test.h"

int main(void) {
    start_tests();
    return 0;
}

void start_tests() {
    int len = 64;
    char buff[64][32];
    for (int i = 0; i < len; i++) {
        memset(buff[i], '\0', 32);
        if (i >> 0 & 1) strcat(buff[i], s21_mac_flags[0]);
        if (i >> 1 & 1) strcat(buff[i], s21_mac_flags[1]);
        if (i >> 2 & 1) strcat(buff[i], s21_mac_flags[2]);
        if (i >> 3 & 1) strcat(buff[i], s21_mac_flags[3]);
        if (i >> 4 & 1) strcat(buff[i], s21_mac_flags[4]);
        if (i >> 5 & 1) strcat(buff[i], s21_mac_flags[5]);
    }
    for (int i = 0; i < 64; i++) {
        file_gen();
        char command1[64] = {'\0'};
        char command2[64] = {'\0'};
        strcat(command1, "cat");
        strcat(command2, "./s21_cat");
        strcat(command1, buff[i]);
        strcat(command2, buff[i]);
        strcat(command1, " tmp_test_file1 > tmp1");
        strcat(command2, " tmp_test_file2 > tmp2");
        printf("%s\n", command1);
        printf("%s\n", command2);
        system(command1);
        system(command2);
        if (system("diff tmp1 tmp2")) {
            printf("%sFAIL%s\n", RED, RESET);
        } else {
            printf("%sOK!%s\n", GRN, RESET);
        }
    }
}

/*int compare(void) {
    FILE *fd_tmp1 = fopen("tmp1", "r");
    FILE *fd_tmp2 = fopen("tmp2", "r");
    if (fd_tmp1 && fd_tmp2) {
        while (1) {
            char *ptr_tmp1 = NULL;
            char *ptr_tmp2 = NULL;
            size_t buff1 = 0;
            size_t buff2 = 0;
            if (getline(&ptr_tmp1, &buff1, fd_tmp1) == -1) break;
            if (getline(&ptr_tmp2, &buff2, fd_tmp2) == -1) break;
            if (buff1 != buff2) printf("buffers no eq\n");
            if (memcmp(ptr_tmp1, ptr_tmp2, buff1))
                printf("CMP::%d\nS1::%s\nS2::%s\n", strcmp(ptr_tmp1, ptr_tmp2), ptr_tmp1, ptr_tmp2);
        }
        fclose(fd_tmp1);
        fclose(fd_tmp2);
    } else {
        perror("");
    }
}
*/

void file_gen(void) {
    int len = rand() % 10000;
    FILE *fd1 = fopen("tmp_test_file1", "w");
    FILE *fd2 = fopen("tmp_test_file2", "w");
    if (fd1 && fd2) {
        for (int i = 0; i < len; i++) {
            unsigned char c = rand() % 127;
            fputc(c, fd1);
            fputc(c, fd2);
        }
        fclose(fd1);
        fclose(fd2);
    } else {
        perror("");
    }
}