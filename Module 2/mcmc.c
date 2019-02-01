/* File Name : mcmc.c
 * Purpose   : To Implement Markov Chain Monte Carlo using GSL
 * Process   : Using GSL we will seed the random numbers and those will be written in a file 
 *             And we used MPI to generate threads and to communicate among them
 * Compile   : mpicc mcmc.c `pkg-config --cflags --libs gsl` -o mcmc
 * Run       : mpiexec mcmc (no. of numbers) (Any String)
 * Outputs   : A File with random numbers 
 */


#include <gsl/gsl_rng.h> 
#include <gsl/gsl_randist.h> 
#include <mpi.h>
#include<timer.h>
double start,end;
int main(int argc,char *argv[]) 
{ 
 const gsl_rng_type * T;
 int k,i,iters,ierr,my_rank; double x,can,a,alpha; gsl_rng *r; 
 FILE *s; char filename[15]; 
 T = gsl_rng_default;
 GET_TIME(start)
 MPI_Init(&argc,&argv); 
 MPI_Comm_rank(MPI_COMM_WORLD,&k); 
 if ((argc != 3)) 
 { 
 if (k == 0) 
 printf("Usage: %s <iters> <alpha>\n",argv[0]); 
 MPI_Finalize();
 return(EXIT_FAILURE); 
 } 
 
 iters=atoi(argv[1]);
 alpha=atof(argv[2]); 
 
 r=gsl_rng_alloc(T); 
 
 sprintf(filename,"chain-%03d.tab",k); 
 s=fopen(filename,"w"); 
 if (s==NULL) 
 { 
  perror("Failed open");
  MPI_Finalize(); 
  return(EXIT_FAILURE); 
 } 
 x = gsl_ran_flat(r,-20,20); 
 fprintf(s,"Iter X\n"); 
 for (i=0;i<iters;i++) 
 { 
 can = x + gsl_ran_flat(r,-alpha,alpha); 
 a = gsl_ran_ugaussian_pdf(can) / gsl_ran_ugaussian_pdf(x); 
 if (gsl_rng_uniform(r) < a) 
 x = can*my_rank;
 fprintf(s,"%d Thread printed %f",k,x); 
 fprintf(s,"%d %f\n",i,x); 
 } 
 fclose(s); 
 MPI_Finalize();
 GET_TIME(end);
 printf("\nTime Take %.lf",end-start);
 return(EXIT_SUCCESS); 
}

