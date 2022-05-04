CC=gcc

CAT_TAR?=s21_cat
CAT_TEST_TAR?=s21_cat_test

CAT_SRC_DIR?=./cat
CAT_OBJ_DIR?=./cat/objs

CAT_TEST_SRC_DIR?=./cat/test
CAT_TEST_OBJ_DIR?=./cat/test/objs

CAT_SRC=$(shell find $(CAT_SRC_DIR) -maxdepth 1 -name "*.c")
CAT_TEST_SRC=$(shell find $(CAT_TEST_SRC_DIR) -maxdepth 1 -name "*.c")

CAT_OBJ:=$(addprefix $(CAT_OBJ_DIR)/, $(notdir $(CAT_SRC:.c=.o)))
CAT_TEST_OBJ:=$(addprefix $(CAT_TEST_OBJ_DIR)/, $(notdir $(CAT_TEST_SRC:.c=.o)))
CAT_INC=./cat/s21_cat.h
CAT_TEST_INC=./cat/test/s21_cat_test.h

CFLAGS=-c -Wall -Wextra -std=c11 #-Werror

MK=mkdir -p
RM=rm -f

all: $(CAT_TAR) cat_test

$(CAT_TAR): $(CAT_OBJ)
	$(CC) $(CAT_OBJ) -o $(CAT_TAR) 

cat_test: $(CAT_TEST_TAR)

$(CAT_TEST_TAR): $(CAT_TEST_OBJ)
	$(CC) $(CAT_TEST_OBJ) -o $(CAT_TEST_TAR)

$(CAT_OBJ): $(CAT_OBJ_DIR)%.o: $(CAT_SRC_DIR)%.c $(CAT_INC) Makefile
	@$(MK) $(CAT_OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ $<

$(CAT_TEST_OBJ): $(CAT_TEST_OBJ_DIR)%.o: $(CAT_TEST_SRC_DIR)%.c $(CAT_TEST_INC) Makefile
	@$(MK) $(CAT_TEST_OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ $<

re: fclean all

clean:
	$(RM) -r $(CAT_OBJ_DIR)

fclean: clean
	$(RM) $(CAT_TAR)