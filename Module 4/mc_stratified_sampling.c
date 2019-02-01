/* File Name : mc_stratified_sampling.c
 * Purpose   : To Implement Stratified Sampling using monte carlo method 
 * Process   : Take number of stratums and take their size also
 *             Take the total number of samples required 
 *             Collect indivdual samples from stratums using the below formula
 *             Sample_stratum = (sample_stratum_size)*(req_sample/total_sample_size)
 *             Paradigm - employee selection for a project
 * Compile   : cc mc_stratified_sampling.c -fopenmp
 * Run       : ./a.out
 */

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int monte_stratified(int sample_stratum_size,int req_sample,int total_samples_size);
int count[5];
void main()
{
  int mft; //male full time employees
  int mpt; //male part time employees
  int fft; //female full  time employees
  int fpt; //female part time employees
  int project_size;  //No of Employees required for the project
  int emp_size; //Total Number of Employees available
  int pmft; //No. of full time working men selected for project
  int pmpt; //No. of part time working men selected for project
  int pfft; //No. of full time working women selected for project
  int pfpt; //No. of part time working women selected for project
  int thread_num;
 
  printf("\nEnter No. of male full time working employees   : ");
  scanf("%d",&mft);
  printf("\nEnter No. of male part time working employees   : ");
  scanf("%d",&mpt);
  printf("\nEnter No. of female full time working employees : ");
  scanf("%d",&fft);
  printf("\nEnter No. of female part time working employees : ");
  scanf("%d",&fpt);
  emp_size=mft+mpt+fft+fpt;
  printf("\nTotal No. of Employees in the organization      : %d\n",emp_size);
  printf("\nEnter the No. of employees required for project ; ");
  scanf("%d",&project_size);
  #pragma omp parallel num_threads(4)
  {
   thread_num = omp_get_thread_num(); 
     if(thread_num==0)
      pmft=monte_stratified(mft,project_size,emp_size);
       else if(thread_num==1)
        pmpt=monte_stratified(mpt,project_size,emp_size);
	 else if(thread_num==2)
	  pfft =monte_stratified(fft,project_size,emp_size);
	 else 
	   pfpt = monte_stratified(fpt,project_size,emp_size);
    
  }
}

/* Purpose : To calculate No. of Employees required from each stratums
 * Input   : sample size of individual stratum, required sample and total number of samples
 * Output  : No. of male and female full and part time employees
 */

int monte_stratified(int sample_stratum_size,int req_sample,int total_samples_size)
{
  int sample_stratum=0,thread_num;
  float temp;
  thread_num = omp_get_thread_num();
  sample_stratum = (sample_stratum_size*req_sample)/total_samples_size;
  if(thread_num==0)
  printf("\nNo. of male full time working employees     : %d\n",sample_stratum);
  else if(thread_num==1)
  printf("\nNo. of female full time working employees   : %d\n",sample_stratum);
  else if(thread_num==2)
  printf("\nNo. of male part time working employees     : %d\n",sample_stratum);
  else
  printf("\nNo. of female part time working employees   : %d\n",sample_stratum);
}