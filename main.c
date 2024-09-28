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
    unsigned int b=image->data[i*3+0];
    unsigned gray =  (0.299 * r + 0.587 * g + 0.114 * b); // formula ponderada
    
    image->data[i*3+2] = gray; // R
    image->data[i*3+1] = gray; // G
    image->data[i*3+0] = gray; // B
  }
}

int processArguments(int argc, char *argv[]) {
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-bw") == 0) {
            convertToBlackAndWhite(image);
            return 1; // Se realizó la conversión
        }
    }
    return 0; // No se realizó ninguna conversión
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
        fprintf(stderr, "Uso: %s <nombre_del_archivo.bmp> [opciones]\n", argv[0]);
        return 1;
  }

  image = readBMP(argv[1]);
  if (!image) {
      fprintf(stderr, "Error: No se pudo leer el archivo BMP: %s\n", argv[1]);
      return 1;
  }

  // Procesar argumentos
  processArguments(argc, argv);
  
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
