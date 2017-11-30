#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "clut.c"

int main(int argc, char **argv) {
    unsigned int level = 16;

    if (argc <= 2) {
        printf("Usage %s <INPUT> <OUTPUT> <LEVEL>\n", argv[0]);
        exit(0);
    }
    char *input_file = argv[1];
    char *output_file = argv[2];

    if (argc > 3) {
        if (sscanf(argv[3], "%u", &level) != 1 || level > 16) {
            printf("Not a valid level: %s (level must be 16 or lower)\n", argv[3]);
            exit(1);
        }
    }

    printf("INPUT:    %s\n", input_file);
    printf("OUTPUT:   %s\n", output_file);
    printf("LEVEL:    %u\n", level);

    int cube_size = level * level;
    float *data = readClut(input_file);
    
    int width = level * level * level * level;
    int height = level * level;

    writeOutput(output_file, data, width, height);
    
    printf("Success!");
    return 0;
}
