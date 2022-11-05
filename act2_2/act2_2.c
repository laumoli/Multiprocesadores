#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define NUM_THREADS 1

void kernel3();
void kernel9();
void kernel15();
void kernel23();
void kernel29();
void kernel35();


FILE *image, *output3_90, *output9_90, *output15_90,*output23_90,*output29_90, *output35_90,*output41_90, 
            *output3_180, *output9_180, *output15_180,*output23_180,*output29_180, *output35_180,*output41_180;


int main()
{
    omp_set_num_threads(NUM_THREADS);

    

    #pragma omp parallel
    {
    #pragma omp sections
    {
            #pragma omp section
            kernel3();
            #pragma omp section
            kernel9();
            #pragma omp section
            kernel15();
            #pragma omp section
            kernel23();
            #pragma omp section
            kernel29();
            #pragma omp section
            kernel35();
     
 
    }
    }

    return 0;
}

void kernel3(){

 
 
    image = fopen("lena_color.bmp","rb");         

    output3_90 = fopen("blur3_90.bmp","wb");
  
    output3_180 = fopen("blur3_180.bmp","wb");

    long ancho;
    long alto;

    unsigned char r, g, b;               //Pixel

    unsigned char xx[54]; 

      for(int i=0; i<54; i++){
        xx[i] = fgetc(image);
        fputc(xx[i], output3_90);
        fputc(xx[i], output3_180);
      }
      

    ancho = (long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto  = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];

    long n = ancho*alto;

    unsigned char* arr_in = (unsigned char*)malloc(n*sizeof(unsigned char));
    unsigned char* arr_out = (unsigned char*)malloc(n*sizeof(unsigned char));
    
    
      for(int i=0; i<n; i++){

       b = fgetc(image);
       g = fgetc(image);
       r = fgetc(image);

       unsigned char pixel = 0.21*r+0.72*g+0.07*b;

       arr_in[i]=pixel;

      }
    float v=1.0 / 9.0;                      // initialize the blurrring kernel
    float kernel[3][3]={{v,v,v},
                        {v,v,v},
                        {v,v,v}};
    
 
    for(int x=1;x<alto-1;x++)
    {                   
        for(int y=1;y<ancho-1;y++)
        {
            float sum0= 0.0;
            for(int i=-1;i<=1;++i)
            {
                for(int j=-1;j<=1;++j)
                {   
                    sum0=sum0+(float)kernel[i+1][j+1]*arr_in[(x+i)*ancho+(y+j)];

                }
            }
            arr_out[(x)*ancho+(y)]=sum0;

        }
    }
    
   #pragma omp parallel
   {
    //180º rotation
    
    int k2;
    
    #pragma omp for schedule(dynamic)
    for (int i=1;i<=(ancho);i++){
        for (int j=0;j<(alto);j++){
        k2 = ( n - (i*ancho)+j);
        putc(arr_out[k2],output3_180);
        putc(arr_out[k2],output3_180);
        putc(arr_out[k2],output3_180);   
    }
    }
    

    //90 rotation
    #pragma omp for schedule(dynamic)
    for (int i=1;i<=(ancho);i++){
        for (int j=0;j<alto;j++){

        k2 = ((j*ancho)+i);
        
        putc(arr_out[k2],output3_90);
        putc(arr_out[k2],output3_90);
        putc(arr_out[k2],output3_90);          
    }
    }
    
    }
    


    fclose(image);
    fclose(output3_180);
    fclose(output3_90);

}

void kernel9(){

    image = fopen("lena_color.bmp","rb");         
    output9_90 = fopen("blur9_90.bmp","wb"); 
    output9_180 = fopen("blur9_180.bmp","wb");
 

    long ancho;
    long alto;

    unsigned char r, g, b;               //Pixel

    unsigned char xx[54]; 

      for(int i=0; i<54; i++){
        xx[i] = fgetc(image);
        fputc(xx[i], output9_90);
        fputc(xx[i], output9_180);
      }
      

    ancho = (long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto  = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];

    long n = ancho*alto;

    unsigned char* arr_in = (unsigned char*)malloc(2782080*sizeof(unsigned char));
    unsigned char* arr_out = (unsigned char*)malloc(2782080*sizeof(unsigned char));
   
      for(int i=0; i<n; i++){

       b = fgetc(image);
       g = fgetc(image);
       r = fgetc(image);

       unsigned char pixel = 0.21*r+0.72*g+0.07*b;

       arr_in[i]=pixel;

      }
    float v=1.0 / 81.0;                      // initialize the blurrring kernel
    float kernel[9][9]={{v,v,v,v,v,v,v,v,v},
                        {v,v,v,v,v,v,v,v,v},
                        {v,v,v,v,v,v,v,v,v},
                        {v,v,v,v,v,v,v,v,v},
                        {v,v,v,v,v,v,v,v,v},
                        {v,v,v,v,v,v,v,v,v},
                        {v,v,v,v,v,v,v,v,v},
                        {v,v,v,v,v,v,v,v,v},
                        {v,v,v,v,v,v,v,v,v}};

    for(int x=1;x<alto-8;x++)        
    {                   
        for(int y=1;y<ancho-8;y++)  
        {
            float sum0 = 0.0;

         for(int i=-1;i<=7;++i)
            {
                for(int j=-1;j<=7;++j)
                {   

                    sum0 = sum0+(float)kernel[i+1][j+1]*arr_in[(x+i)*ancho+(y+j)];

                }
            }
            arr_out[(x)*ancho+(y)]=sum0;

        }
    }
    
     #pragma omp parallel
    {


    //180º rotation
        int k,k2;
    #pragma omp for schedule(dynamic)
    
    for (int i=1;i<=(ancho);i++){
        for (int j=0;j<(alto);j++){
        k2 = (n- (i*ancho)+j);
        putc(arr_out[k2],output9_180);
        putc(arr_out[k2],output9_180);
        putc(arr_out[k2],output9_180);

       
        
    }
    }



    //90 rotation
    #pragma omp for schedule(dynamic)
    for (int i=1;i<=(ancho);i++){
        for (int j=0;j<alto;j++){
        
        k2 = ((j*ancho)+i);
        
        putc(arr_out[k2],output9_90);
        putc(arr_out[k2],output9_90);
        putc(arr_out[k2],output9_90);

       
        
    }

    }}



    fclose(image);
    fclose(output9_180);
    fclose(output9_90);

}

void kernel15(){

 
 
    image = fopen("lena_color.bmp","rb");         

    output15_90 = fopen("blur15_90.bmp","wb");
  
    output15_180 = fopen("blur15_180.bmp","wb");

    long ancho;
    long alto;

    unsigned char r, g, b;               //Pixel

    unsigned char xx[54]; 

      for(int i=0; i<54; i++){
        xx[i] = fgetc(image);
        fputc(xx[i], output15_90);
        fputc(xx[i], output15_180);
      }
      

    ancho = (long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto  = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];

    long n = ancho*alto;

    unsigned char* arr_in = (unsigned char*)malloc(2782080*sizeof(unsigned char));
    unsigned char* arr_out = (unsigned char*)malloc(2782080*sizeof(unsigned char));
   
      for(int i=0; i<n; i++){

       b = fgetc(image);
       g = fgetc(image);
       r = fgetc(image);

       unsigned char pixel = 0.21*r+0.72*g+0.07*b;

       arr_in[i]=pixel;

      }

    float v=1.0 / 225.0;                      // blurring kernel
    float kernel[15][15]=       {{v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v}};

    for(int x=1;x<alto-14;x++)
    {                   
        for(int y=1;y<ancho-14;y++)
        {
            float sum0= 0.0;

            for(int i=-1;i<=13;++i)
            {
                for(int j=-1;j<=13;++j)
                {   
                    sum0=sum0+(float)kernel[i+1][j+1]*arr_in[(x+i)*ancho+(y+j)];
                }
            }
            arr_out[(x)*ancho+(y)]=sum0;
        }
    }
    

    //180º rotation
    #pragma omp parallel
    {
    int k,k2;
    #pragma omp for schedule(dynamic)
    for (int i=1;i<=(ancho);i++){
        for (int j=0;j<(alto);j++){
        k2 = (n- (i*ancho)+j);

        putc(arr_out[k2],output15_180);
        putc(arr_out[k2],output15_180);
        putc(arr_out[k2],output15_180);

       
        
    }
    }

    //90 rotation
    #pragma omp for schedule(dynamic)
    for (int i=1;i<=(ancho);i++){
        for (int j=0;j<alto;j++){

        k2 = ((j*ancho)+i);
        
        putc(arr_out[k2],output15_90);
        putc(arr_out[k2],output15_90);
        putc(arr_out[k2],output15_90);

       
        
    }

    }
    }


    fclose(image);
    fclose(output15_180);
    fclose(output15_90);

}

void kernel23(){

 
 
    image = fopen("lena_color.bmp","rb");         

    output23_90 = fopen("blur23_90.bmp","wb");
  
    output23_180 = fopen("blur23_180.bmp","wb");

    long ancho;
    long alto;

    unsigned char r, g, b;               //Pixel

    unsigned char xx[54]; 

      for(int i=0; i<54; i++){
        xx[i] = fgetc(image);
        fputc(xx[i], output23_90);
        fputc(xx[i], output23_180);
      }
      

    ancho = (long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto  = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];

    long n = ancho*alto;

    unsigned char* arr_in = (unsigned char*)malloc(2782080*sizeof(unsigned char));
    unsigned char* arr_out = (unsigned char*)malloc(2782080*sizeof(unsigned char));
   
      for(int i=0; i<n; i++){

       b = fgetc(image);
       g = fgetc(image);
       r = fgetc(image);

       unsigned char pixel = 0.21*r+0.72*g+0.07*b;

       arr_in[i]=pixel;

      }

   float v=1.0 / 529.0;                       // blurring kernel
    float kernel[23][23]=        {{v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v}};

    for(int x=1;x<alto-22;x++)
    {                   
        for(int y=1;y<ancho-22;y++)
        {
            float sum0= 0.0;

            for(int i=-1;i<=21;++i)
            {
                for(int j=-1;j<=21;++j)
                {   
                    sum0=sum0+(float)kernel[i+1][j+1]*arr_in[(x+i)*ancho+(y+j)];
                }
            }
            arr_out[(x)*ancho+(y)]=sum0;
        }
    }
    

    //180º rotation
    #pragma omp parallel

    {
    int k,k2;
    #pragma omp for schedule(dynamic)
    for (int i=1;i<=(ancho);i++){
        for (int j=0;j<(alto);j++){
        k2 = (n- (i*ancho)+j);
        putc(arr_out[k2],output23_180);
        putc(arr_out[k2],output23_180);
        putc(arr_out[k2],output23_180);

       
        
    }
    }

    //90 rotation
    #pragma omp for schedule(dynamic)
    for (int i=1;i<=(ancho);i++){
        for (int j=0;j<alto;j++){
        
        k2 = ((j*ancho)+i);

        putc(arr_out[k2],output23_90);
        putc(arr_out[k2],output23_90);
        putc(arr_out[k2],output23_90);

       
        
    }

    }
    }



    fclose(image);
    fclose(output23_180);
    fclose(output23_90);

}

void kernel29(){

 
    image = fopen("lena_color.bmp","rb");         

    output29_90 = fopen("blur29_90.bmp","wb");
  
    output29_180 = fopen("blur29_180.bmp","wb");

    long ancho;
    long alto;

    unsigned char r, g, b;               //Pixel

    unsigned char xx[54]; 

      for(int i=0; i<54; i++){
        xx[i] = fgetc(image);
        fputc(xx[i], output29_90);
        fputc(xx[i], output29_180);
      }
      

    ancho = (long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto  = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];

    long n = ancho*alto;

    unsigned char* arr_in = (unsigned char*)malloc(2782080*sizeof(unsigned char));
    unsigned char* arr_out = (unsigned char*)malloc(2782080*sizeof(unsigned char));
   
      for(int i=0; i<n; i++){

       b = fgetc(image);
       g = fgetc(image);
       r = fgetc(image);

       unsigned char pixel = 0.21*r+0.72*g+0.07*b;

       arr_in[i]=pixel;

      }

    float v = 1.0 / 841.0;                       // blurring kernel
    float kernel[29][29]=        {{v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v}};
    for(int x=1;x<alto-1;x++)
    {                   
        for(int y=1;y<ancho-1;y++)
        {
            float sum0= 0.0;

            for(int i=-1;i<=27;++i)
            {
                for(int j=-1;j<=27;++j)
                {   
                    sum0=sum0+(float)kernel[i+1][j+1]*arr_in[(x+i)*ancho+(y+j)];
                }
            }
            arr_out[(x)*ancho+(y)]=sum0;
        }
    }
    

    //180º rotation
    #pragma omp parallel
    {
    int k,k2;
    #pragma omp for schedule(dynamic)
    for (int i=1;i<=(ancho);i++){
        for (int j=0;j<(alto);j++){
        k2 = (n- (i*ancho)+j);
        putc(arr_out[k2],output29_180);
        putc(arr_out[k2],output29_180);
        putc(arr_out[k2],output29_180);

       
        
    }
    }

    //90 rotation
    #pragma omp for schedule(dynamic)
    for (int i=1;i<=(ancho);i++){
        for (int j=0;j<alto;j++){

        k2 = ((j*ancho)+i);
        putc(arr_out[k2],output29_90);
        putc(arr_out[k2],output29_90);
        putc(arr_out[k2],output29_90);

       
        
    }

    }
    }


    fclose(image);
    fclose(output29_180);
    fclose(output29_90);

}

void kernel35(){
  
    image = fopen("lena_color.bmp","rb");         

    output35_90 = fopen("blur35_90.bmp","wb");
  
    output35_180 = fopen("blur35_180.bmp","wb");

    long ancho;
    long alto;

    unsigned char r, g, b;               //Pixel

    unsigned char xx[54]; 

      for(int i=0; i<54; i++){
        xx[i] = fgetc(image);
        fputc(xx[i], output35_90);
        fputc(xx[i], output35_180);
      }
      

    ancho = (long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto  = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];

    long n = ancho*alto;

    unsigned char* arr_in = (unsigned char*)malloc(2782080*sizeof(unsigned char));
    unsigned char* arr_out = (unsigned char*)malloc(2782080*sizeof(unsigned char));
   
      for(int i=0; i<n; i++){

       b = fgetc(image);
       g = fgetc(image);
       r = fgetc(image);

       unsigned char pixel = 0.21*r+0.72*g+0.07*b;

       arr_in[i]=pixel;

      }

    float v = 1.0 / 1225.0;                       // blurring kernel
    float kernel[35][35]=       {{v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v},
                                 {v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v,v}};
    for(int x=1;x<alto-1;x++)
    {                   
        for(int y=1;y<ancho-1;y++)
        {
            float sum0= 0.0;

            for(int i=-1;i<=33;++i)
            {
                for(int j=-1;j<=33;++j)
                {   
                    sum0=sum0+(float)kernel[i+1][j+1]*arr_in[(x+i)*ancho+(y+j)];
                }
            }
            arr_out[(x)*ancho+(y)]=sum0;
        }
    }
    

    //180º rotation
    #pragma omp parallel
    {
    int k,k2;
    #pragma omp for schedule(dynamic)
    for (int i=1;i<=(ancho);i++){
        for (int j=0;j<(alto);j++){
        k2 = (n- (i*ancho)+j);
        putc(arr_out[k2],output35_180);
        putc(arr_out[k2],output35_180);
        putc(arr_out[k2],output35_180);

       
        
    }
    }

    //90 rotation
    #pragma omp for schedule(dynamic)
    for (int i=1;i<=(ancho);i++){
        for (int j=0;j<alto;j++){
        k2 = ((j*ancho)+i);
        putc(arr_out[k2],output35_90);
        putc(arr_out[k2],output35_90);
        putc(arr_out[k2],output35_90);

       
        
    }

    }

    }

    fclose(image);
    fclose(output35_180);
    fclose(output35_90);

}
