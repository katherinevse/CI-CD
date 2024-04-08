CC=gcc
CFFLAGS=-Wall -Wextra -Werror -std=c11
CFFLAGS_DEBUG=-g -Wall -Wextra -Werror -std=c11

GREP_NAME=s21_grep

FILES=../grep/*.c

s21_grep: clean
	$(CC) $(CFFLAGS) ./s21_grep.c -o ./$(GREP_NAME)

s21_grep_debug:
	$(CC) $(CFFLAGS_DEBUG) ./s21_grep.c -o ./$(GREP_NAME)

clean:
	rm -rf */*.o
	rm -rf */*.a
	rm -rf */*a.out
	rm -rf ./$(GREP_NAME)

rebuild: clean $(GREP_NAME)
