#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *file = fopen("inputs/day02", "r");
    if (file == NULL) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    char direction[8];
    do {
        fscanf(file, "%s\n", direction);
        printf("%s\n", direction);

    } while (!feof(file) && !ferror(file));

    return EXIT_SUCCESS;
}
