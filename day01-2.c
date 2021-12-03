#include <stdio.h>
#include <stdlib.h>

int main(void) {
  FILE *file = fopen("inputs/day01", "r");
  if (file == NULL) {
    perror("Failed to open input file");
    return EXIT_FAILURE;
  }
  int current_input, last_1, last_2, last_window, current_window;
  int increases = 0;
  fscanf(file, "%d\n", &last_1);
  fscanf(file, "%d\n", &last_2);
  fscanf(file, "%d\n", &current_input);
  last_window = last_1 + last_2 + current_input;
  last_1 = last_2;
  last_2 = current_input;
  do {
    fscanf(file, "%d\n", &current_input);
    current_window = last_1 + last_2 + current_input;
    if (current_window > last_window) {
      increases++;
    }
    last_window = current_window;
    last_1 = last_2;
    last_2 = current_input;

  } while (!feof(file) && !ferror(file));
  printf("%d\n", increases);

  return EXIT_SUCCESS;
}
