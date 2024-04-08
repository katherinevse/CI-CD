CC=gcc
CFFLAGS=-Wall -Wextra -Werror -std=c11
CFFLAGS_DEBUG=-g -Wall -Wextra -Werror -std=c11

CAT_NAME=s21_cat
GREP_NAME=s21_grep

CLANG_PATH=../materials/linters/
PATHS=*/*.c */*.h

CLANG_MODE=-n

CLANG_COPY=cp $(CLANG_PATH).clang-format .clang-format
CLANG_REMOVE=rm .clang-format

s21_cat:
	$(CC) $(CFFLAGS) cat/s21_cat.c -o cat/$(CAT_NAME)

s21_grep:
	$(CC) $(CFFLAGS) grep/s21_grep.c -o grep/$(GREP_NAME)


all: s21_cat grep_21


rebuild: clean all

clang:
	$(CLANG_COPY) && clang-format $(CLANG_MODE) $(PATHS) 2> style_test_result.txt && $(CLANG_REMOVE)
