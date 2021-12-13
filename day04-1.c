#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARD_SIZE 5

typedef int board_t[BOARD_SIZE][BOARD_SIZE];

void print_board(board_t board) {
  for(int i = 0; i < BOARD_SIZE; i++) {
    for(int j = 0; j < BOARD_SIZE; j++) {
      printf("%d\t", board[i][j]);
    }
    printf("\n");
  }
}

int main(void) {
  FILE *file = fopen("inputs/day04", "r");
  if (file == NULL) {
    perror("Failed to open input file");
    return EXIT_FAILURE;
  }

  char *line = NULL;
  size_t line_len; // size of buffer not size of string?
  
  // parse first line into draws
  size_t draws_cap = 1; // random default
  int *draws_arr = calloc(draws_cap,sizeof(int));
  size_t draws_count = 0;

  getline(&line, &line_len, file);
  for (char *p = strtok(line,","); p != NULL; p = strtok(NULL, ",")) {
    if (draws_count >= draws_cap) {
      draws_cap *= 2;
      draws_arr = reallocarray(draws_arr,draws_cap, sizeof(int));
    }
    draws_arr[draws_count] = atoi(p);
    draws_count++;
  }

  size_t board_cap = 4;
  board_t *board_arr = calloc(board_cap, sizeof(board_t));
  size_t board_count = 0;

  do {
    //skip empty line
    getline(&line, &line_len, file);
    if (feof(file) || ferror(file)) {
      break;
    }
    if (board_count >= board_cap) {
      board_cap = board_cap * 2;
      board_arr = reallocarray(board_arr, board_cap, sizeof(board_t));
    }
    for(int i = 0; i < BOARD_SIZE; i++) {
      getline(&line, &line_len, file);
      int j = 0;
      for (char *p = strtok(line," "); p != NULL; p = strtok(NULL, " ")) {
        board_arr[board_count][i][j] = atoi(p);
        j++;
        if (j > BOARD_SIZE) {
          perror("BOARD TOO WIDE!");
          return EXIT_FAILURE;
        }
      }
    }
    printf("--------- board #%zu ------\n", board_count);
    print_board(board_arr[board_count]);
    board_count++;
  } while (!feof(file) && !ferror(file));
  free(line);

  // TODO rest of the problem now...

  return EXIT_SUCCESS;
}
