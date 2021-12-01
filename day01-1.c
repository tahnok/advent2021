#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *file = fopen("inputs/day01", "r");
    if (file == NULL) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }
    int current_input, last_input;
    int increases = 0;
    fscanf(file, "%d\n", &last_input); // initialize with first line
    do {
        fscanf(file, "%d\n", &current_input);
        if (current_input > last_input) {
            increases++;
        }
        last_input = current_input;
    } while (!feof(file) && !ferror(file));
    printf("%d\n", increases);

    return EXIT_SUCCESS;
}
