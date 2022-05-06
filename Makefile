CC=gcc

ASAN:=-fsanitize=address -g
CFLAGS=-c -Wall -Wextra -std=c11 #-Werror
MK=mkdir -p
RM=rm -f

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

GREP_TAR?=s21_grep
GREP_TEST_TAR?=s21_grep_test

GREP_SRC_DIR?=./grep
GREP_OBJ_DIR?=./grep/objs

GREP_TEST_SRC_DIR?=./grep/test
GREP_TEST_OBJ_DIR?=./grep/test/objs

GREP_SRC=$(shell find $(GREP_SRC_DIR) -maxdepth 1 -name "*.c")
GREP_TEST_SRC=$(shell find $(GREP_TEST_SRC_DIR) -maxdepth 1 -name "*.c")

GREP_OBJ:=$(addprefix $(GREP_OBJ_DIR)/, $(notdir $(GREP_SRC:.c=.o)))
GREP_TEST_OBJ:=$(addprefix $(GREP_TEST_OBJ_DIR)/, $(notdir $(GREP_TEST_SRC:.c=.o)))
GREP_INC=./grep/s21_grep.h
GREP_TEST_INC=./grep/test/s21_grep_test.h

all: $(GREP_TAR) grep_test #$(CAT_TAR) cat_test
#./s21_cat_test

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


$(GREP_TAR): $(GREP_OBJ)
	$(CC) $(ASAN) $(GREP_OBJ) -o $(GREP_TAR) 

grep_test: $(GREP_TEST_TAR)

$(GREP_TEST_TAR): $(GREP_TEST_OBJ)
	$(CC) $(ASAN) $(GREP_TEST_OBJ) -o $(GREP_TEST_TAR)

$(GREP_OBJ): $(GREP_OBJ_DIR)%.o: $(GREP_SRC_DIR)%.c $(GREP_INC) Makefile
	@$(MK) $(GREP_OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ $<

$(GREP_TEST_OBJ): $(GREP_TEST_OBJ_DIR)%.o: $(GREP_TEST_SRC_DIR)%.c $(GREP_TEST_INC) Makefile
	@$(MK) $(GREP_TEST_OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ $<


re: fclean all

clean:
	$(RM) -r $(CAT_OBJ_DIR)
	$(RM) -r $(CAT_TEST_OBJ_DIR)
	$(RM) -r $(GREP_OBJ_DIR)
	$(RM) -r $(GREP_TEST_OBJ_DIR)

fclean: clean
	$(RM) $(CAT_TAR)
	$(RM) $(CAT_TEST_TAR)
	$(RM) $(GREP_TAR)
	$(RM) $(GREP_TEST_TAR)