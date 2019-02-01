/* File Name : monte_prng_gsl.c
 * Purpose   : To implement PRNG using GSL(GNU Scientific Library)
 * Compile   : gcc monte_prng_gsl.c `pkg-config --cflags --libs gsl` -o monte_prng_gsl -fopenmp
 * Execute   : ./monte_prng_gsl
 *             GSL Library need to be installed before executing
 */

#include<stdio.h>
#include<omp.h>
#include <gsl/gsl_rng.h>

int x0;        //seed value
int a=2;       //multiplier
int c=1;       //Additive constant
int M;         //Maximum Period
int xi;        //next value
int no;        //number of random numbers 
int i;         //loop counter
int acc[100];  //Accumulator to store numbers
void calc_rand_no(int x0,int M,int n0);
void main()
{
 const gsl_rng_type * T;
 gsl_rng * r;
 int my_rank;
 int num_threads;
 int my_seed;
 gsl_rng_env_setup();
 
 T = gsl_rng_default;
 r = gsl_rng_alloc (T);
 x0 = gsl_rng_uniform (r)*100;
 printf("\nSeed value taken using GSL is : %d",x0);
 printf("\nEnter Maximum Period : ");
 scanf("%d",&M);
 printf("\nEnter the number of random numbers required : ");
 scanf("%d",&no); 
 #pragma omp parallel num_threads(4) private(xi)
 {
   my_rank= omp_get_thread_num();
   my_seed=x0*my_rank;
   xi=my_seed;
   #pragma omp for
   for(i=0;i<no;i++)
    {
     xi= (xi*a+c)%M;
     printf("\nRandom Number generated by thread %d is %d\n",my_rank,xi);
    } 
 }

 gsl_rng_free (r);
}//end main


void calc_rand_no(int x0,int M,int no)
{
  int my_rank= omp_get_thread_num();
  int num_threads= omp_get_num_threads();
  int my_seed=x0*my_rank;
  printf("\nSeed Value of %d is %d\n",my_rank,my_seed);
  #pragma omp critical
  {
    for(i=1;i<no;i++)
    {
     acc[i]= (acc[i-1]*a+c)%M;
     printf("\nRandom Number generated by thread %d is %d\n",my_rank,acc[i]);
    }
  }  

  
}
 

  