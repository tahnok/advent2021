#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  FILE *file = fopen("inputs/day04-sample", "r");
  if (file == NULL) {
    perror("Failed to open input file");
    return EXIT_FAILURE;
  }

  char *line = NULL;
  size_t len; // size of buffer not size of string?
  ssize_t read;
  
  read = getline(&line, &len, file);
  for (char *p = strtok(line,","); p != NULL; p = strtok(NULL, ",")) {
    printf("%s = %d\n", p, atoi(p));
  }

  do {
    read = getline(&line, &len, file);
    printf("read: %zu, len: %zu, line: %s\n", read, len, line);
  } while (!feof(file) && !ferror(file));
  free(line);

  return EXIT_SUCCESS;
}
