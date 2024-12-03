#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
  FILE *file = fopen(argv[argc - 1], "r");
  char *line = NULL;
  size_t length = 0;
  while (getline(&line, &length, file) != -1) {

    line = NULL;
    length = 0;
  }

  fclose(file);
  return 0;
}
