#include "bmp.h"
#include <GL/glut.h>
#include <stdio.h>

BMPImage *image;

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  if (image) {
    drawBMP(image);
  }
  glFlush();
}

void convertGrayScale(BMPImage* image) {
  for(unsigned int i=0; i<image->width * image->height; i++){
    unsigned int r=image->data[i*3+2]:
    unsigned int g=image->data[i*3+1];
    unsigned int b=image->data[i*3];
    unsigned promedio = r + g + b;
  }
}

int main() {
  char filename[256];

  // Pedir al usuario el nombre del archivo BMP
  printf("Ingrese el nombre del archivo BMP (con extensión): ");
  scanf("%255s", filename);

  image = readBMP(filename);
  if (!image) return 1;

  // Inicializar GLUT
  int argc = 1; // Necesario para evitar problemas con glutInit
  char *argv[1] = { "" }; // Argumento vacío para GLUT
  glutInit(&argc, argv);

  // Establecer el modo de visualización
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(image->width, image->height);
  glutCreateWindow("Visualizador de BMP");

  glLoadIdentity();
  glOrtho(0, image->width, image->height, 0, -1, 1);

  glutDisplayFunc(display);
  glutMainLoop();

  freeBMP(image);
  return 0;
}
