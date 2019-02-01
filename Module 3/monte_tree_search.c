/* File Name : monte_tree_search.c
 * Purpose   : To implement monte carlo tree monte_tree_search
 * Compile   : cc monte_tree_search.c -fopenmp
 * Run       : ./a.out (No. of threads)
 */

#include<omp.h>

#include<stdlib.h>

#include<stdio.h>



int func1(int g,int thread_count);

int func2(int g,int thread_count);

int func3(int g,int thread_count);

int main(int argc,char* argv[])

{

int i,j,m,g,n,num,gw,gp,k,b;

int thread_count=strtol(argv[1],NULL,10);

printf("enter the number of games to be played\n");

scanf("%d",&g);
b=g%3;
switch(b)
{
case 0:
{

func1(g,thread_count);
break;
}

case 1:
{

func2(g,thread_count);
break;
}

case 2:
{

func3(g,thread_count);
break;
}
}
}//main

int func1(int g,int thread_count)

{


int i,m,n,k;

#pragma omp parallel for num_threads(thread_count)

for(i=0;i<3;i++){
int gw=0,gp=0,j,num;
for(j=0;j<g/3;j++)

{

num=rand()%2;

if(num==0){

gp++;

}

else{

gw++;
gp++;

}

}

printf("no.of games won/no.of games played: %d/%d\n",gw,gp);

}

}//func1

int func2(int g,int thread_count)

{
int j,i,m,n,k;
int gp=0,gw=0;
for(j=0;j<g/3+1;j++)

{
int num;
num=rand()%2;

if(num==0){

gp++;

}

else{

gw++;

gp++;

}

}

printf("no.of games won/no.of games played: %d/%d\n",gw,gp);



#pragma omp parallel for num_threads(thread_count) 

for(i=0;i<2;i++){
int gp=0,gw=0,num,j;
for(j=0;j<g/3;j++)

{

num=rand()%2;

if(num==0){

gp++;

}

else{

gw++;

gp++;

}
}
printf("no.of games won/no.of games played: %d/%d\n",gw,gp);


}
}//func2



int func3(int g,int thread_count)

{
int num,j,i,m,n,k,gw=0,gp=0;
for(k=0;k<g/3+2;k++)

{

num=rand()%2;

if(num==0){

gp++;

}

else{

gw++;

gp++;

}

}

printf("no.of games won/no.of games played is: %d/%d\n",gw,gp);


#pragma omp parallel for num_threads(thread_count)
for(i=0;i<2;i++){
int gp=0,gw=0,num,j;
for(j=0;j<g/3;j++)

{

num=rand()%2;

if(num==0){

gp++;

}

else{

gw++;

gp++;

}

}

printf("no.of games won/no.of games played: %d/%d\n",gw,gp);

}

}//func3
