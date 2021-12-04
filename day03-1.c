#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  FILE *file = fopen("inputs/day03", "r");
  if (file == NULL) {
    perror("Failed to open input file");
    return EXIT_FAILURE;
  }

  char direction[12];
  u_int32_t lines = 0;
  u_int32_t columns[12] = {0};
  u_int32_t width;
  do {
    fscanf(file, "%s\n", direction);
    width = strlen(direction);
    for (size_t i = 0; i < 12; i++) {
      if (direction[i] == 0) {
        continue;
      }
      if (direction[i] == '1') {
        columns[i]++;
      }
    }
    lines++;
  } while (!feof(file) && !ferror(file));

  u_int32_t half = lines / 2;

  u_int32_t gamma = 0;
  for (size_t i = 0; i < width; i++) {
    gamma += (columns[i] > half) << (width - i - 1);
  }

  u_int32_t mask = (1 << width) - 1;
  u_int32_t epsilon = ~gamma & mask;

  printf("%d\n", epsilon * gamma);

  return EXIT_SUCCESS;
}
