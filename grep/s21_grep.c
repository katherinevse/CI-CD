#include "s21_grep.h"

int main(int argc, char *argv[]) {
  Options options = {false};

  if (argc < 3) {
    fprintf(stderr, "ERROR: try ./s21_grep [OPTIONS] PATTERN [FILE]");
  } else {
    get_opt(argc, argv, &options);
    get_files_count(&options, argc);
    get_search_string(&options, argv);
    output_files(argc, argv, &options);
  }

  return 0;
}

void get_opt(int argc, char *argv[], Options *options) {
  int opt = 0;

  while ((opt = getopt(argc, argv, "e:ivclnhsof:")) != -1) {
    switch (opt) {
      case 'e':
        options->e = true;
        if (strlen(options->target) > 0) {
          strcat(options->target, "|");
        }
        strcat(options->target, optarg);
        break;
      case 'i':
        options->i = true;
        break;
      case 'v':
        options->v = true;
        break;
      case 'c':
        options->c = true;
        break;
      case 'l':
        options->l = true;
        break;
      case 'n':
        options->n = true;
        break;
      case 's':
        options->s = true;
        break;
      case 'h':
        options->h = true;
        break;
      case 'o':
        options->o = true;
        break;
      case 'f':
        options->f = true;
        handle_f(options);
        break;
      case '?':
        fprintf(stderr, "ERROR: invalid flag!\n");
        break;
    }
  }
}

void get_files_count(Options *options, int argc) {
  options->files_count = argc - optind;
}

void get_search_string(Options *options, char *argv[]) {
  if (!options->e && !options->f) {
    strcpy(options->target, argv[optind]);
    options->files_count--;
  }
}

bool check_file_exists(char *filename) {
  int file_exist = false;

  FILE *file = fopen(filename, "r");

  if (file != NULL) {
    file_exist = true;
    fclose(file);
  }

  return file_exist;
}

void read_file(char *file_name, Options *options) {
  FILE *fp = NULL;
  fp = fopen(file_name, "r");

  int match_count = 0;
  int line_enum = 0;
  int res;

  regex_t regex;
  regcomp(&regex, options->target, options->i ? REG_ICASE : REG_EXTENDED);

  char line[BUFFER_SIZE];
  while ((fgets(line, BUFFER_SIZE, fp)) != NULL) {
    line_enum++;
    res = regexec(&regex, line, 0, NULL, 0);

    if (options->v) {
      res = !(res);
    }

    if (!res) {
      match_count++;
      if (options->l) {
        handle_l(options, file_name);
        break;
      } else if (!options->c) {
        if (options->files_count > 1 && !options->h) {
          printf("%s:", file_name);
        }

        if (options->n) {
          printf("%d:", line_enum);
        }

        if (options->o) {
          handle_o(line, options);
        } else {
          print_line(line);
        }
      }
    }
  }

  if (options->c) {
    handle_c(options, file_name, match_count);
  }

  regfree(&regex);
  fclose(fp);
}

void output_files(int argc, char *argv[], Options *options) {
  int start = argc - options->files_count;
  for (int i = start; i < argc; i++) {
    if (check_file_exists(argv[i])) {
      read_file(argv[i], options);
    } else {
      if (!options->s) {
        fprintf(stderr, "ERROR: File %s is not found!", argv[i]);
      }
    }
  }
}

void print_line(char *line) {
  printf("%s", line);
  if (line[strlen(line) - 1] != '\n') {
    printf("\n");
  }
}

void handle_c(Options *options, char *file_name, int match_count) {
  if (!options->l || !match_count) {
    if (options->files_count > 1 && !options->h) {
      printf("%s:", file_name);
    }
    printf("%d\n", match_count);
  }
}

void handle_l(Options *options, char *file_name) {
  if (options->c) {
    if (options->files_count > 1 && !options->h) {
      printf("%s:", file_name);
    }

    printf("1\n");
  }

  printf("%s\n", file_name);
}

void handle_o(char *line, Options *options) {
  regex_t regex;
  int rc;
  regmatch_t matches[1];

  rc = regcomp(&regex, options->target, options->i ? REG_ICASE : REG_EXTENDED);

  while (*line) {
    rc = regexec(&regex, line, 1, matches, 0);
    if (rc == REG_NOMATCH && options->v) {
      print_line(line);
      break;
    } else if (rc == 0) {
      for (int i = matches[0].rm_so; i < matches[0].rm_eo; i++) {
        printf("%c", line[i]);
      }
      printf("\n");
      line += matches[0].rm_eo;

    } else {
      line++;
    }
  }

  regfree(&regex);
}

void handle_f(Options *options) {
  FILE *fp = NULL;

  if (check_file_exists(optarg)) {
    fp = fopen(optarg, "r");
    char line[BUFFER_SIZE];

    while ((fgets(line, BUFFER_SIZE, fp)) != NULL) {
      if (strlen(options->target) > 0) {
        strcat(options->target, "|");
      }

      if (line[strlen(line) - 1] == '\n') {
        line[strlen(line) - 1] = '\0';
      }

      strcat(options->target, line);
    }

    fclose(fp);
  } else
    fprintf(stderr, "ERROR: file %s doesn't exist\n", optarg);
}
