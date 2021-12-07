#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_WIDTH 13
#define MAX_LENGTH 1000

u_int32_t count(char to_count, size_t pos, char inputs[MAX_LENGTH][MAX_WIDTH], bool *skips, u_int32_t lines);
u_int32_t skip(char to_skip, size_t pos, char inputs[MAX_LENGTH][MAX_WIDTH], bool *skips, u_int32_t lines);
u_int32_t bool_str_to_int(char *columns, u_int32_t width);

int main(void) {
  FILE *file = fopen("inputs/day03", "r");
  if (file == NULL) {
    perror("Failed to open input file");
    return EXIT_FAILURE;
  }

  char line[MAX_WIDTH];
  u_int32_t lines = 0;
  u_int32_t ones_count[MAX_WIDTH] = {0};
  u_int32_t width = 0;
  char inputs[MAX_LENGTH][MAX_WIDTH] = {0};
  do {
    fscanf(file, "%s\n", line);

    if (width == 0) {
      width = strlen(line);
      if (width > MAX_WIDTH) {
        perror("Line is longer than expected!");
        return EXIT_FAILURE;
      }
    }

    for (size_t i = 0; i < MAX_WIDTH; i++) {
      if (line[i] == 0) {
        continue;
      }
      if (line[i] == '1') {
        ones_count[i]++;
      }
    }

    strncpy(inputs[lines], line, MAX_WIDTH);
    lines++;
    if(lines > MAX_LENGTH) {
      perror("More lines than expected!");
      return EXIT_FAILURE;
    }
  } while (!feof(file) && !ferror(file));


  bool skips[MAX_LENGTH] = { 0 };

  u_int32_t left = lines;
  for(size_t pos = 0; pos < width; pos++) {
    u_int32_t found = count('1', pos, inputs, skips, lines);

    if (found * 2 >= left) {
      left = skip('0', pos, inputs, skips, lines);
    } else {
      left = skip('1', pos, inputs, skips, lines);
    }

    if (left == 1) {
      break;
    }
  }
  size_t oxygen_index = 0;
  for(oxygen_index = 0; oxygen_index < lines; oxygen_index++) {
    if(!skips[oxygen_index]) {
      break;
    }
  }
  u_int32_t oxygen = bool_str_to_int(inputs[oxygen_index], width);

  left = lines;
  memset(skips, false, lines);
  for(size_t pos = 0; pos < width; pos++) {
    u_int32_t found = count('1', pos, inputs, skips, lines);

    if (found * 2 >= left) {
      left = skip('1', pos, inputs, skips, lines);
    } else {
      left = skip('0', pos, inputs, skips, lines);
    }

    if (left == 1) {
      break;
    }
  }
  size_t co2_index = 0;
  for(co2_index = 0; co2_index < lines; co2_index++) {
    if(!skips[co2_index]) {
      break;
    }
  }
  u_int32_t co2 = bool_str_to_int(inputs[co2_index], width);

  printf("%d\n", oxygen * co2);

  return EXIT_SUCCESS;
}

u_int32_t count(char to_count, size_t pos, char inputs[MAX_LENGTH][MAX_WIDTH], bool *skips, u_int32_t lines) {
  u_int32_t found = 0;
  for(size_t i = 0; i < lines; i++) {
    if(skips[i]) {
      continue;
    }
    if(inputs[i][pos] == to_count) {
      found++;
    }
  }

  return found;
}

u_int32_t skip(char to_skip, size_t pos, char inputs[MAX_LENGTH][MAX_WIDTH], bool *skips, u_int32_t lines) {
  u_int32_t remaining = 0;
  for(size_t i = 0; i < lines; i++) {
    if(skips[i]) {
      continue;
    }
    if(inputs[i][pos] == to_skip) {
      skips[i] = true;
    } else {
      remaining++;
    }
  }
  return remaining;
}

u_int32_t bool_str_to_int(char *columns, u_int32_t width) {
  u_int32_t gamma = 0;
  for (size_t i = 0; i < width; i++) {
    gamma += (columns[i] == '1') << (width - i - 1);
  }
  return gamma;
}
