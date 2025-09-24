#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>

typedef struct{
    int size; 
    uint16_t reserva1;
    uint16_t reserva2;
    int  offset; 
}CabeceraArchivo;

typedef struct{
    unsigned int tamCabecera; 
    uint32_t ancho;
    uint32_t alto;
    uint16_t planosColor;
    uint16_t bpp; 
    uint32_t compresion;
    uint32_t tamImg;
    uint32_t resX;
    uint32_t resY;
    uint32_t rangeColor;
    uint32_t impColor;
}CabeceraImagen;

void imprimeCabeceraArchivo(CabeceraArchivo headerFile)
{
    printf("Tamano archivo: %d\n",headerFile.size);
    printf("offSet: %d\n",headerFile.offset);
}

void imprimeCabeceraImagen(CabeceraImagen headerImg)
{
    printf("Ancho imagen: %d\n",headerImg.ancho);
    printf("Alto imagen: %d\n",headerImg.alto);
    printf("bpp de la imagen: %d\n",headerImg.bpp);
    printf("Tam de la imagen: %d\n",headerImg.tamImg);
    printf("planos de color de la imagen: %d\n",headerImg.planosColor);
    printf("ResX de la imagen: %d\n",headerImg.resX);
    printf("ResY de la imagen: %d\n",headerImg.resY);
    printf("impColor de la imagen: %d\n",headerImg.impColor);
}

unsigned char* cargarImagen(char* nombreArchivoImg, CabeceraImagen* cabeceraBMP)
{
    FILE* archivoImagen=fopen(nombreArchivoImg,"r");
    if(archivoImagen==NULL)
    {
        puts("No se puede abrir la imagen\n");
        return NULL;
    } 
    else
    {
        CabeceraArchivo headerArchivo; 
        unsigned char* matrizDatos=NULL; 
        int tipoImg=0;
        fread(&tipoImg, sizeof(uint16_t),1,archivoImagen);
        printf("Tipo imagen = %p\n", tipoImg);
        if(tipoImg!=0x4D42)
        {
            printf("El formato de la imagen no corresponde\n");
            fclose(archivoImagen);
            return NULL;
        }
        printf("Comenzando la lectura de las cabeceras del archivo\n");
        fread(&headerArchivo, sizeof(CabeceraArchivo),1,archivoImagen);
        fread(cabeceraBMP,sizeof(CabeceraImagen),1,archivoImagen);
        printf("Imprimiendo cabecera de archivo\n");
        imprimeCabeceraArchivo(headerArchivo);
        printf("Imprimiendo cabecera de imagen\n");
        imprimeCabeceraImagen(*cabeceraBMP);
        matrizDatos=(unsigned char*)malloc(sizeof(unsigned char)*(cabeceraBMP->tamImg));
        if(matrizDatos==NULL)
        {
            printf("No hubo memoria para los datos\n");
            fclose(archivoImagen);
            return NULL;
        }
        fseek(archivoImagen,headerArchivo.offset,SEEK_SET);
        fread(matrizDatos,cabeceraBMP->tamImg,1, archivoImagen);
        fclose(archivoImagen);
        return matrizDatos;
    }
}

void imprimirPixeles(CabeceraImagen cabeceraBMP, unsigned char* matrizImg)
{
    int posX=0, posY=0;
    int ejeY,  ejeX;
    for( ejeY=--cabeceraBMP.alto;ejeY>0; ejeY--)
    {
        posX=0;
        for( ejeX=0; ejeX<cabeceraBMP.ancho;ejeX++)
        {
            printf("[%d][%d]=%d\n", posY, posX, matrizImg[ejeX+ejeY*(cabeceraBMP.ancho)]);
            posX++;
        }
        printf("\n\n");
        posY++;
    }
}

unsigned char *suma(unsigned char *pixeles, unsigned char *data)
{
  unsigned char *pixels;
  pixels=(unsigned char*)malloc(49152);
   int ejeX, ejeY, posicionX=0, posicionY=0;
  int i;
  for(i=0; i<49152; i++)
	pixels[i]=data[i]+pixeles[i];
  
  free(pixeles);
  free(data);
  return pixels;
}

void guardarImg(char *filename, CabeceraImagen *info, unsigned char *imgdata)
{
  CabeceraArchivo header;
  FILE *f;
  uint16_t type;
 
  f=fopen(filename, "wb");
  header.size=info->tamImg+sizeof(CabeceraArchivo)+sizeof(CabeceraImagen);
  header.offset=sizeof(CabeceraArchivo)+sizeof(CabeceraImagen)+2;
  type=0x4D42;
  fwrite(&type, sizeof(type),1,f);
  fwrite(&header, sizeof(CabeceraArchivo),1,f);
  fwrite(info, sizeof(CabeceraImagen),1,f);
  fwrite(imgdata, info->tamImg, 1, f);
  fclose(f);
}

void main()
{
    CabeceraImagen headerImagen1;
    unsigned char* img1=cargarImagen("calaca.bmp",&headerImagen1);
	
	CabeceraImagen headerImagen2;
    unsigned char* img2=cargarImagen("luna.bmp",&headerImagen2);
    
    unsigned char* sumaImagenes = suma(img1, img2);
    
    guardarImg("nuevaimagen.bmp",&headerImagen1, sumaImagenes);

    printf("Imagen Procesada!!!");
}