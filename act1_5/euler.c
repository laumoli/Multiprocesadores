#include <stdio.h>
#include <omp.h>
#include <math.h>
#define NUM_THREADS 6

//trabaja en disco duro

   FILE *fptr;
   FILE *fptr1;
   FILE *fptr2;
   FILE *fptr3;
   FILE *fptr4;
   FILE *fptr5;
void iteracion(long N,FILE *x);

int main()
{  omp_set_num_threads(NUM_THREADS);

   fptr=fopen("Euler_n_0.txt","w");
   fptr1=fopen("Euler_n_1.txt","w");
   fptr2=fopen("Euler_n_2.txt","w");
   fptr3=fopen("Euler_n_3.txt","w");
   fptr4=fopen("Euler_n_4.txt","w");
   fptr5=fopen("Euler_n_5.txt","w");
 double t1 = omp_get_wtime();
 
   #pragma omp parallel
{   
   
     #pragma omp sections
    {
       #pragma omp section
         (void)iteracion(5000,fptr);//20//2000900
       #pragma omp section
         (void)iteracion(5000,fptr1);//200//2000400
       #pragma omp section
         (void)iteracion(5000,fptr2);//2000//2000700
       #pragma omp section
         (void)iteracion(5000,fptr3);//20000//2000800
       #pragma omp section
         (void)iteracion(5000,fptr4);//200000//2000500
       #pragma omp section
         (void)iteracion(5000,fptr5);//2000000//2000100
   }
   

   
}  
  double t2 = omp_get_wtime();
  printf("tomo (%lf) segundos\n",(t2-t1));
   fclose(fptr);
   fclose(fptr1);
   fclose(fptr2);
   fclose(fptr3);
   fclose(fptr4);
   fclose(fptr5);
   return (0);}
void iteracion(long N, FILE *x)
{
	printf("Numero de pasos:%d Atendido por thread:%d\n", N,omp_get_thread_num());
	fprintf(x, "Datos que encuentra el metodo de Euler(variable ind.\t variable dep.\t numero de thread)\n");
      double h,t,w,ab;
      double w0=0.5,a=0,b=2;
      int i;
      w=w0;
      fprintf(x, "%f\t %f\n", a, w);
      for(i=0;i<N;i++){
          h=(b-a)/N;
          t=a+(h*i);
          ab=t*t;
          w=w+h*(1+asin(t-w));
          fprintf(x, "%f\t %f \t numero de thread:%d\n", t+h, w,omp_get_thread_num());
         } }
