#include <stdio.h>
#include <stdlib.h>

#define HISTOGRAM_SIZE 256

typedef struct {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
} Pixel;

void calculateHistogram(const char* filename, int* histogram) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("No se pudo abrir la imagen.\n");
        return;
    }

    // Leer la cabecera del archivo BMP
    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, file);

    // Obtener información de la imagen
    int width = *(int*)&header[18];
    int height = *(int*)&header[22];
    int bitsPerPixel = *(int*)&header[28];

    // Verificar si la imagen es en blanco y negro (8 bits por píxel)
    if (bitsPerPixel == 8) {
        printf("La imagen no es en blanco y negro.\n");
        fclose(file);
        return;
    }

    // Calcular el tamaño del histograma
    int imageSize = width * height;
    unsigned char* imagePixels = (unsigned char*)malloc(imageSize * sizeof(unsigned char));

    // Leer los píxeles de la imagen
    fread(imagePixels, sizeof(unsigned char), imageSize, file);

    // Obtener los valores de los píxeles y calcular el histograma
    int i;
    for (i = 0; i < imageSize; i++) {
        histogram[imagePixels[i]]++;
    }

    // Imprimir el histograma
    for (i = 0; i < HISTOGRAM_SIZE; i++) {
        printf("Valor %d: %d\n", i, histogram[i]);
    }

    // Liberar memoria y cerrar el archivo
    free(imagePixels);
    fclose(file);
}

int main() {
    const char* filename = "imagen.bmp";
    int histogram[HISTOGRAM_SIZE] = {0};
    calculateHistogram(filename, histogram);
    printf("Imagen Procesada!!!");
    return 0;
}