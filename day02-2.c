#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *file = fopen("inputs/day02", "r");
    if (file == NULL) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }
    const char *FORWARD = "forward";
    const char *DOWN = "down";
    const char *UP = "up";

    char direction[8];
    u_int32_t change = 0;

    u_int32_t aim = 0;
	u_int32_t horizontal = 0;
    u_int32_t depth = 0;
    do {
        fscanf(file, "%s %d\n", direction, &change);
        if (strncmp(direction, FORWARD, 8) == 0) {
            horizontal += change;
            depth += aim * change;
        } else if (strncmp(direction, DOWN, 8) == 0) {
            aim += change;
        } else if (strncmp(direction, UP, 8) == 0) {
            aim -= change;
        } else {
            fprintf(stderr, "Unknown line: %s\n", direction);
            exit(EXIT_FAILURE);
        }

    } while (!feof(file) && !ferror(file));

    printf("%d\n", depth * horizontal);
    

    return EXIT_SUCCESS;
}
