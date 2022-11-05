
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_THREADS 1

void mirror();
void invert();

int main()
{
    invert();
    return 0;
}

void mirror(){

    omp_set_num_threads(NUM_THREADS);
    FILE *image, *outputImage, *lecturas;
    image = fopen("lena_color.bmp","rb");         
    outputImage = fopen("mirror.bmp","wb");  \
 
    long ancho;
    long alto;

    unsigned char r, g, b;               //Pixel

    unsigned char xx[54]; 

      for(int i=0; i<54; i++){
        xx[i] = fgetc(image);
        fputc(xx[i], outputImage);
      }
      

    ancho = (long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto  = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];
    long n = ancho*alto;

    unsigned char* arr_in = (unsigned char*)malloc(n*3*sizeof(unsigned char));

   
      for(int i=0; i<n; i++){

       b = fgetc(image);
       g = fgetc(image);
       r = fgetc(image);

       unsigned char pixel = 0.21*r+0.72*g+0.07*b;

       arr_in[i]=pixel;

    }

    #pragma omp parallel
    {
    int k;

    #pragma omp for schedule(dynamic)
    for (int i=1;i<=(alto);i++){
        for (int j=0;j<(ancho);j++){        
        k = (ancho * i) - j;
        putc(arr_in[k],outputImage);
        putc(arr_in[k],outputImage);
        putc(arr_in[k],outputImage);              
    }
    }
    }

    fclose(image);
    fclose(outputImage);
}

void invert(){

    omp_set_num_threads(NUM_THREADS);
    FILE *image, *outputImage, *lecturas;
    image = fopen("f7.bmp","rb");         
    outputImage = fopen("invert.bmp","wb");  \
 
    long ancho;
    long alto;

    unsigned char r, g, b;               //Pixel

    unsigned char xx[54]; 

      for(int i=0; i<54; i++){
        xx[i] = fgetc(image);
        fputc(xx[i], outputImage);
      }
      

    ancho = (long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto  = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];
    long n = ancho*alto;

    unsigned char* arr_in = (unsigned char*)malloc(n*3*sizeof(unsigned char));

   
      for(int i=0; i<n; i++){

       b = fgetc(image);
       g = fgetc(image);
       r = fgetc(image);

       unsigned char pixel = 0.21*r+0.72*g+0.07*b;

       arr_in[n-i]=pixel;

    }

    #pragma omp parallel
    {
    int k;

    #pragma omp for schedule(dynamic)
    for (int i=1;i<=(alto);i++){
        for (int j=0;j<(ancho);j++){        
        k = (ancho * i) - j;
        putc(arr_in[k],outputImage);
        putc(arr_in[k],outputImage);
        putc(arr_in[k],outputImage);              
    }
    }
    }

    fclose(image);
    fclose(outputImage);
}
