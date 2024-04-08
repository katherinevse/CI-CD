#ifndef CAT_HEADER
#define CAT_HEADER

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  bool e, b, n, v, t, s;
} Options;

void get_options(int argc, char *argv[], Options *options);
void read_file(char *filename, Options options);
void cat_f(void);

#endif
