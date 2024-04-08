CC=gcc
CFFLAGS=-Wall -Wextra -Werror -std=c11
CFFLAGS_DEBUG=-g -Wall -Wextra -Werror -std=c11

CAT_NAME=s21_cat

FILES=*.c *.h

s21_cat: clean
	$(CC) $(CFFLAGS) ./s21_cat.c -o ./$(CAT_NAME)

s21_cat_debug:
	$(CC) $(CFFLAGS_DEBUG) ./s21_cat.c -o ./$(CAT_NAME)

clean:
	rm -rf */*.o
	rm -rf */*.a
	rm -rf */*a.out
	rm -rf ./$(CAT_NAME)

rebuild: clean $(CAT_NAME)
