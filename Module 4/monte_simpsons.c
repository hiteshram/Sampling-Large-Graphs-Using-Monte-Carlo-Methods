/* File Name : monte_simpsons.c
 * Purpose   : To apply simpsons rule and determine the area of the function
 * Compile   : cc monte_simpsons.c -fopenmp
 * Run       : ./a.out
 */ 



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

double count_x[50],count_fx[50];
double f(double x);


void main()
{
 double a,b,n; //lower and upper bound and total number of samples required 
 double h; //period or 
 int i,j; 
 double temp,sum=0;
 printf("Enter the Lower and Upper Bounds : ");
 scanf("%lf%lf",&a,&b);
 printf("\nTotal Number of Samples : ");
 scanf("%lf",&n);
 h=(b-a)/n;
 for(i=0;i<n;i++)
 {
  count_x[i]=random()%(int)(b-a+1)+a;
 }
 
 #pragma omp parallel num_threads((int)n)
 {
  count_fx[omp_get_thread_num()]=f(count_x[omp_get_thread_num()]);  
 }
  sum=count_fx[0];
  for(j=1;j<n;j++)
  {
   if(j%2==0)
   count_fx[j]=2*count_fx[j];
   else
   count_fx[j]=4*count_fx[j];
   sum=sum+count_fx[j];
  }
  sum = (h/3)*sum;
 printf("Area of the curve according to Simpsons Rule is : %.2f\n",sum);
 
}//end of main

/* Purpose : To calculate the square of the number in x
 * Input   : value x
 * Output  : value x^2
 */
double f(double x) {
double return_val;
return_val = x*x;
return return_val;
} /* f */

 
