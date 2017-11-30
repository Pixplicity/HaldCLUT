#include <stdlib.h>
#include <stdio.h>

void save_targa(char *file_name, float *data, unsigned int width, unsigned int height) {
  FILE *image;
  char *foot = "TRUEVISION-XFILES.";
  unsigned int i, x, y;

  if ((image = fopen(file_name, "wb")) == NULL) {
    printf("Could not create file: %s\n", file_name);
    return;
  }
  fputc(0, image);
  fputc(0, image);
  fputc(2, image); /* uncompressed */

  for (i = 3; i < 12; i++) {
    fputc(0, image); /* ignore some stuff */
  }
  fputc(width % 256, image);  /* size */
  fputc(width / 256, image);
  fputc(height % 256, image);
  fputc(height / 256, image);

  /* Clamping nod needed since clut is not HDRI */
  /*  for(i = 0; i < 3 * width * height; i++) 
    {
      if(data[i] > 1)
        data[i] = 1;
      if(data[i] < 0)
        data[i] = 0;
    }
  */

  fputc(24, image); /* 24 bit image */

  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      int offset = ((height - y - 1) * width + x) * 3;

      int r = (int)(data[offset + 0] * 255.0);
      fputc(r, image);

      int g = (int)(data[offset + 2] * 255.0);
      fputc(g, image);

      int b = (int)(data[offset + 1] * 255.0);
      fputc(b, image);
    }
  }
  /* Footer not described in TARGA spec but for some reason needed by photoshop */
  for (i = 0; i < 9; i++) {
    fputc(0, image); // ignore some stuff
  }
  for (i = 0; foot[i] != 0; i++) {
    fputc(foot[i], image); // ignore some stuff
  }
  fputc(0, image);
  fclose(image);
}
