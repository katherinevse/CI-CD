#include "s21_cat.h"

int main(int argc, char *argv[]) {
  Options options = {false};

  get_options(argc, argv, &options);

  for (int i = optind; i < argc; i++) read_file(argv[i], options);
}

void get_options(int argc, char *argv[], Options *options) {
  struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                  {"number", 0, 0, 'n'},
                                  {"squeeze-blank", 0, 0, 's'},
                                  {0, 0, 0, 0}};

  int opt;
  while ((opt = getopt_long(argc, argv, "+beEvnstTv", long_options, NULL)) !=
         -1) {
    switch (opt) {
      case 'b':
        options->b = true;
        break;
      case 'e':
        options->e = true;
        options->v = true;
        break;
      case 'v':
        options->v = true;
        break;
      case 'n':
        options->n = true;
        break;
      case 's':
        options->s = true;
        break;
      case 't':
        options->t = true;
        options->v = true;
        break;
      case 'T':
        options->t = true;
        break;
      case 'E':
        options->e = true;
        break;
      default:
        exit(1);
    }
  }
}

void read_file(char *filename, Options options) {
  FILE *file = fopen(filename, "r");

  if (file != NULL) {
    int line_counter = 1;
    int empty_line_counter = 0;
    char cur_char = '\0';

    for (char prev_char = '\n'; !feof(file); prev_char = cur_char) {
      cur_char = getc(file);

      if (options.s && cur_char == '\n' && prev_char == '\n') {
        empty_line_counter++;
        if (empty_line_counter > 1) continue;
      } else
        empty_line_counter = 0;

      if (options.b && cur_char != '\n' && prev_char == '\n' &&
          (signed char)cur_char != EOF)
        printf("%6d\t", line_counter++);

      if (options.n && !options.b && prev_char == '\n' &&
          (signed char)cur_char != EOF)
        printf("%6d\t", line_counter++);

      if (options.e && cur_char == '\n') printf("$");

      if (options.t) {
        if (cur_char == 9) {
          putchar('^');
          putchar('I');

          continue;
        }
      }

      if (options.v) {
        if ((cur_char < 9) || (cur_char > 10 && cur_char < 32)) {
          putchar('^');
          cur_char += 64;
        }
        if (cur_char == 127) {
          putchar('^');
          putchar('?');

          continue;
        }
      }

      if ((signed char)cur_char != EOF) printf("%c", cur_char);
    }

    fclose(file);
  } else
    printf("s21_cat: No such file or directory\n");
}
