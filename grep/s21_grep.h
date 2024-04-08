#ifndef GREP_HEADER
#define GREP_HEADER

#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct {
  bool e, i, v, c, l, n, h, s, o, f;
  int files_count;
  char target[BUFFER_SIZE * 4];
} Options;

void get_opt(int argc, char *argv[], Options *options);

void get_files_count(Options *options, int argc);
void get_search_string(Options *options, char *argv[]);
bool check_file_exists(char *filename);

void read_file(char *file_name, Options *options);

void output_files(int argc, char *argv[], Options *options);
void print_line(char *line);

void handle_o(char *line, Options *options);
void handle_f(Options *options);
void handle_l(Options *options, char *file_name);
void handle_c(Options *options, char *file_name, int match_count);

#endif