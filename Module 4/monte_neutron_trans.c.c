/* File Name : monte_neutron_trans.c
 * Purpose   : To Implement an Event based Monte Carlo Program on a 1D Region
 * Process   : 1.take input for number of neutrons 
 *             2.Calculate Scattering and Absorbing Component
 *             3.Perform required arthmetic
 * Compile   : cc monte_neutron_trans.c -fopenmp
 * Run       : ./a.out
 */


#include<stdio.h>
#include<math.h>
#include<omp.h>

#define PI 3.14
void monte_neutron(double C_c,double C_s,double C);
int r=0,b=0,t=0; //counts of reflected,absorbed,transmitted neutrons
int a=1; //true while particle still bouncing
int n; //Number of samples
double x=0; //position of particle (0<=x<H)
double u; //random number 
double d = 180; //Direction of neutron
double L; //Distance Neutron Travelled before collision
int H=150; //Thickness of a plate
double C_c; //Absorbing Component
double C_s; //Scattering Component
double C; //mean distance


void main()
{
 int i; //loop counter 
 
 C_c = random()%100; 
 C_s = random()%100; 
 C = C_c+C_s; 
 printf("\nEnter number of neutrons : ");
 scanf("%d",&n);
 #pragma omp parallelnum_threads(n)
 monte_neutron(C_c,C_s,C);
 
 printf("\nNeutrons Reflected,Absorbed and Transmitted are : %d,%d,%d\n",r,b,t);
}


/* Purpose : To determine if neutron is scattered, reflected or transmitted
 * Inputs  : Scattered and Absorbed Component
 * Outputs : No. of neutrons scattered,absorbed and transmitted 
 */
void monte_neutron(double C_c,double C_s,double C)
{
  int i;
  for(i=0;i<n;i++)
 {
   d=0;
   x=0;
   a=1;
   u=(random()%100)*0.01;
   while(a)
   {
    L = -(1/C)*log(u); 
    x = x+L*cos((d*PI)/180);
    if(x<0) //Reflected
    {
     r=r+1;
     printf("\n*---->--*             |");
     printf("\n          *           |"); 
     printf("\n*--*-<--*             |");    
     printf("\n                      |");
     a=0;
    }
    else if(x>=H) //Transmitted
    {
     t=t+1;
     a=0;
     printf("\n*--->---*---->-----*--|->-*");
     printf("\n                      |");
    }
    else if(u<(C_c/C)) //Absorbed
    {
     b=b+1;
     a=0;
     printf("\n*---->--*             |");
     printf("\n          *           |"); 
     printf("\n   *-<--*             |");
     printf("\n                      |");
    }
    else
      d=u*3.14;
   }//end while   
  }//end for
}