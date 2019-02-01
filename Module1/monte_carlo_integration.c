/* File Name : monte_carlo_integration.c
 * Purpose   : To apply Monte Carlo Integration on a Function and compare with actual result 
 * Process   : Conside f(x) as a function whose limits are inbetween [a,b]
 *             we are going to generate the random numbers x1,x2,x3......xn in between the interval [a,b] and 
 *             estimate the average and compare with the result obtained from actual integration of the function 
 *             we took simple function f(x) = x^2+3*x+3 to process
 * Compile   : cc monte_carlo_integration.c -fopenmp
 * Run       : ./a.out
 * Inputs    : 1.For convinience we took limits from 0 to 1 and random numbers will be generated in between the limits
 *             2.Given number of samples to be considered 
 * Outputs   : 1.Gives the result of monte carlo integration is applied 
 *             2.Actual result when original integration is applied             
 */
#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define PI 3.1416

void monte_func(double a,double b,int n);
double count[20000];
double sum=0;
double start,end;

void main()
{
 double I;   //x-is function variable y-function output
 int i;        //n-number of samples i- loop counter
 int threads;
 I = (1/3+3/2+3);    //substituting 1 in the integral of f(x)
 printf("\nValue obtained after integrating mathematically       : %lf\n",I);
 printf("\nEnter Number of threads                               : ");
 scanf("%d",&threads);
 #pragma omp parallel num_threads(threads)
 {
   start = omp_get_wtime();
   monte_func(0,1,threads);
   end = omp_get_wtime();
 }
 
 for(i=0;i<threads;i++)
   sum=sum+count[i];                    //Summation of substitutions
   sum=sum/threads;                     //Average with total number of samples
 printf("\nIntegral Value obtained by applying Monte Carlo Method : %lf\n",sum);
 printf("\nElapsed Time is %lf",end-start);
  
}


/* Purpose : To generate random numbers and substitute in the function and store the value
 * Inputs  : Lower and upper limit and total number of samples
 * Output  : An Array with results of random number substitutions
 */

void monte_func(double a,double b,int n)
{
 float x;
 int thread_num=omp_get_thread_num();
 if(x= (random()%100)*0.01)
 {
   printf("\n %d thread executed with random number %.2f \n",thread_num,x);
   count[thread_num]= x*x+3*x+3; 
   printf("\nCount[%d]  : %lf\n",thread_num,count[thread_num]);
 }
}



