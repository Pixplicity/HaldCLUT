#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "png.c"

float* createHaldClut(int cube_size) {
    printf("Creating Hald CLUT with %u pixel blocks\n", cube_size);

    // Hald CLUT
    float *data = malloc((sizeof *data) * cube_size * cube_size * cube_size * 3);
    unsigned int red, blue, green;
    long i = 0;
    for (blue = 0; blue < cube_size; blue++) {
        for (green = 0; green < cube_size; green++) {
            for (red = 0; red < cube_size; red++) {
                data[i++] = (float)red / (float)(cube_size - 1);
                data[i++] = (float)green / (float)(cube_size - 1);
                data[i++] = (float)blue / (float)(cube_size - 1);
            }
        }
    }

    return data;
}

float* createClut(int cube_size, int width, int height) {
    printf("Creating conventional CLUT at %ux%u pixels\n", width, height);

    // Conventional CLUT
    float *data = malloc((sizeof *data) * width * height * 3);
    unsigned int red, blue, green;
    long i = 0;
    for (green = 0; green < cube_size; green++) {
        for (blue = 0; blue < cube_size; blue++) {
            for (red = 0; red < cube_size; red++) {
                data[i++] = (float)red / (float)(cube_size - 1);
                data[i++] = (float)green / (float)(cube_size - 1);
                data[i++] = (float)blue / (float)(cube_size - 1);
            }
        }
    }

    return data;
}

float* readClut(char *file_name) {
    struct Image image = read_png_file(file_name);

    printf("Reading %ux%u image...\n", image.width, image.height);

    float *data = malloc((sizeof *data) * image.width * image.height * 3);
    long i = 0;

    for(int y = 0; y < image.height; y++) {
        png_bytep row = image.row_pointers[y];
        for (int x = 0; x < image.width; x++) {
            png_bytep px = &(row[x * 4]);
            data[i++] = px[0] / 255.0; // red
            data[i++] = px[1] / 255.0; // green
            data[i++] = px[2] / 255.0; // blue
            // Ignore alpha
            //printf("%u -> %f\n", px[2], data[i-1]);
        }
    }

    printf("Read %u pixels\n", image.width * image.height * 3);

    return data;
}

void writeOutput(char *file_name, float *data, int width, int height) {
    printf("Mapping %ux%u pixels for output...\n", width, height);

    png_bytep *row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
    long i = 0;
    for(int y = 0; y < height; y++) {
        png_bytep row = (png_byte*) malloc(4 * width * sizeof(png_byte));
        row_pointers[y] = row;
        for (int x = 0; x < width; x++) {
            png_bytep px = &(row[x * 4]);
            px[0] = (int)(data[i++] * 255.0); // red
            px[1] = (int)(data[i++] * 255.0); // green
            px[2] = (int)(data[i++] * 255.0); // blue
            px[3] = 255; // alpha
        }
    }

    printf("Writing PNG...\n");
    write_png_file(file_name, width, height, row_pointers);
}
