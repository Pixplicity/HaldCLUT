#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "clut.c"

int main(int argc, char **argv) {
    unsigned int level = 16;
    unsigned int mode = 0;

    if (argc <= 1) {
        printf("Usage %s <FILENAME> <MODE> <LEVEL>\n", argv[0]);
        printf("MODE:\n");
        printf("  0 = Hald CLUT (square image with RGB along XYZ axes)\n");
        printf("  1 = Conventional CLUT (rectangular image with RGB along XYZ axes)\n");
        exit(0);
    }
    char *file_name = argv[1];

    if (argc > 2) {
        if(sscanf(argv[2], "%u", &mode) != 1 || mode < 0 || mode > 1) {
            printf("Not a valid mode: %s (mode must be 0 or 1)\n", argv[2]);
            exit(1);
        }
    }
    if (argc > 3) {
        if(sscanf(argv[3], "%u", &level) != 1 || level > 16) {
            printf("Not a valid level: %s (level must be 16 or lower)\n", argv[3]);
            exit(1);
        }
    }

    printf("FILENAME: %s\n", file_name);
    printf("LEVEL:    %u\n", level);
    printf("MODE:     %u\n", mode);

    int cube_size = level * level;
    int width, height;
    float *data;

    switch (mode) {
        default:
        case 0: {
            width = level * level * level;
            height = width;
            // Hald CLUT
            data = createHaldClut(cube_size);
        }
        break;
        case 1: {
            width = level * level * level * level;
            height = level * level;
            // Hald CLUT
            data = createClut(cube_size, width, height);
        }
        break;
    }

    writeOutput(file_name, data, width, height);
    
    printf("Success!");
    return 0;
}
