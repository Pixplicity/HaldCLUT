#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "png.c"

int main(int argc, char **argv) {
	char *file_name = "hald_clut.tga";
	unsigned int red, blue, green, level = 16;
	float *data, *p;

	if (argc > 1) {
		file_name = argv[1];
	} else {
		printf("Usage %s <FILENAME> <LEVEL>\n", argv[0]);
		printf("Using default values\n");
	}

	if (argc > 2) {
		if(sscanf(argv[2], "%u", &level) != 1 || level > 16) {
			printf("Not valid level: %s (level must be 16 or lower)\n", argv[2]);
			exit(0);
		}
	}

	printf("FILENAME: %s\n", file_name);
	printf("LEVEL:    %u\n", level);

	int cube_size = level * level;
	int width = level * level * level;
	int height = level * level * level;

	printf("Creating Hald CLUT at %ux%u pixels\n", width, height);

	data = p = malloc((sizeof *data) * width * height * 3);
	{
		long i = 0;
		for (blue = 0; blue < cube_size; blue++) {
		    for (green = 0; green < cube_size; green++) {
		        for (red = 0; red < cube_size; red++) {
		            p[i++] = (float)red / (float)(cube_size - 1);
		            p[i++] = (float)green / (float)(cube_size - 1);
		            p[i++] = (float)blue / (float)(cube_size - 1);
		        }
		    }
		}
	}

	printf("Writing PNG...\n");
	png_bytep *row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
	long i = 0;
	for(int y = 0; y < height; y++) {
		png_bytep row = (png_byte*) malloc(4 * width * sizeof(png_byte));
		row_pointers[y] = row;
		for (int x = 0; x < width; x++) {
			png_bytep px = &(row[x * 4]);
			px[0] = (int)(p[i++] * 255.0); // red
			px[1] = (int)(p[i++] * 255.0); // green
			px[2] = (int)(p[i++] * 255.0); // blue
			px[3] = 255; // alpha
		}
	}
	write_png_file(file_name, width, height, row_pointers);
	
	printf("Success!");
	return 0;
}
