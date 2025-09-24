#include <stdio.h>
#include <stdlib.h>

#pragma pack(push, 1)
typedef struct {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
} Pixel;
#pragma pack(pop)

int main() {
    // Abre el archivo de entrada
    FILE* file = fopen("calaca.bmp", "rb");
    if (!file) {
        printf("Error al abrir el archivo de entrada.\n");
        return 1;
    }

    // Lee la cabecera del archivo de imagen
    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, file);

    // Obtiene el ancho y alto de la imagen
    int width = *(int*)&header[18];
    int height = *(int*)&header[22];

    // Calcula el tamaño de la imagen en bytes
    int size = width * height;

    // Aloja memoria para almacenar la imagen en memoria
    Pixel* image = (Pixel*)malloc(size * sizeof(Pixel));

    // Lee los datos de imagen en memoria
    fread(image, sizeof(Pixel), size, file);

    // Cierra el archivo de entrada
    fclose(file);

    // Crea una nueva imagen de diferente color
    for (int i = 0; i < size; i++) {
        // Cambia el color de los píxeles
        image[i].red = 255;     // Componente de color rojo
        image[i].green = 0;   // Componente de color verde
        image[i].blue = 0;  // Componente de color azul
    }

    // Abre el archivo de salida
    FILE* output = fopen("imagen_nueva.bmp", "wb");
    if (!output) {
        printf("Error al crear el archivo de salida.\n");
        free(image);
        return 1;
    }

    // Escribe la cabecera y los datos de imagen en el archivo de salida
    fwrite(header, sizeof(unsigned char), 54, output);
    fwrite(image, sizeof(Pixel), size, output);

    // Cierra el archivo de salida
    fclose(output);

    // Libera la memoria
    free(image);

    printf("Imagen Procesada!!!");

    return 0;
}