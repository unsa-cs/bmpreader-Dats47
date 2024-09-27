/***Extensión del Proyecto**: Modifica el código para que el nombre del archivo BMP sea recibido como un argumento en la línea de comandos. 
/*Asegúrate de manejar correctamente los errores en caso de que el archivo no se encuentre o no sea un BMP válido.
#include "bmp.h"
#include <GL/glut.h>

BMPImage* readBMP(const char *filename) {
  BMPImage *image = malloc(sizeof(BMPImage));
  FILE *file = fopen(filename, "rb");

  //Verifica si el archivo existe o se puede abrir
  if (!file) {
    fprintf(stderr, "No se puede abrir el archivo %s\n", filename);
    free(image);
    return NULL;
  }

  fread(image->header, sizeof(unsigned char), 54, file);
  image->width = *(int*)&image->header[18];
  image->height = *(int*)&image->header[22];

  image->data = malloc(image->width * image->height * 3); // 3 bytes por píxel
  fread(image->data, sizeof(unsigned char), image->width * image->height * 3, file);
  fclose(file);

  return image;
}

void freeBMP(BMPImage *image) {
  free(image->data);
  free(image);
}

void drawBMP(BMPImage *image) {
  glDrawPixels(image->width, image->height, GL_BGR, GL_UNSIGNED_BYTE, image->data);
}
