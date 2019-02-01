/* File-name: monte_temp_detection.c
 * Purpose : To determine the temperature on a 2D plate which is being heated from outside
 * Compile : cc monte_temp_detection.c -lpthread -lm
 * Run     : ./a.out 
 * Inputs  :1.Select the size of the square matrix nxn
 *          2.Enter the surrounding temperature in degrees
 *          3.Select the coordinates on the plate where the temperature need to determined 
 * Outputs :1.Temperature will be displayed
 *          2.Graph associated with samples will be displayed X Denotes the given input coordinates
 *                                                            . Denotes the path of random walk
 *                                                            * Denotes the point where the thread came into contact where the temperature is known   
 */
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<pthread.h>

int count[4];
double a[20][20]; //elements of the graph
char display[20][20]; //stores the path of random walk
double x,y; //coordinates and the copy of the coordinates
int org_x,org_y,sample;  
double temp,req_temp;
int i,j; //loop counters
int m,n; //rows and columns of the graph
void visited(int mk_z_x,int mk_z_y);
void *Rand_walk(void* rank);
void Rand_walk_display();

void main()
{
 long thread;
 pthread_t* thread_handles;
 
 
 printf("Enter the Size of the plane : ");
 scanf("%d %d",&m,&n); 
 
 for(i=0;i<m;i++)
    for(j=0;j<n;j++)
      display[i][j]=' ';
 
 printf("\n2D PLANE IS INITIALIZED\n");
 for(i=0;i<m;i++)
 {
   for(j=0;j<n;j++)
   {
     a[i][j]=0;
     printf("%.2lf ",a[i][j]);
   }
   printf("\n"); 
 }
 srandom(0);                             //seeding random number generator
 printf("\nEnter the temperature arround the plane     : ");
 scanf("%lf",&temp);
 
 printf("\nSET PROBABILITIES\n");
 for(i=0;i<m;i++)          
 {
   for(j=0;j<n;j++)
   {
     a[i][j]= rand()%100;               //initializing the plane with random numbers 
     a[i][j]=a[i][j]*0.01;    
     printf("%.2lf ",a[i][j]);
   }
   printf("\n");
 }
 printf("\nEnter the Coordinates from (0,0) to (%d,%d) : ",m-1,n-1);
 scanf("%lf%lf",&x,&y);
 org_x = (int)x;
 org_y = (int)y;  //storing the copies of original coordinates

 thread_handles=malloc(4*sizeof(pthread_t));                              //allocating memory for threads
 for(i=0;i<4;i++)
   pthread_create(&thread_handles[i],NULL,Rand_walk,(void*)i);
 
 for(i=0;i<4;i++)
   pthread_join(thread_handles[i],NULL);
 free(thread_handles);
 
 req_temp=0;
 Rand_walk_display(); 
 

 for(i=0;i<4;i++)                   //temperature calculation
  req_temp=temp*(count[i]%4)+req_temp;
 req_temp=req_temp/4; 
 printf("\nEstimated Temperature at the point (%d,%d) is %.2lf\n",org_x,org_y,req_temp); 
 printf("\nSamples Considered : %d\n",sample=count[0]+count[1]+count[2]+count[3]);
 printf("\nEfficiency of the process : %.2lf",(sample/(m*n)));
  
}//end of main

/* Purpose : Random walk is performed in the initialized graph depending on the assigned probabilities
 * Input   : Thread Rank
 * Output  : Random Walk on the graph will be obtained
 */
void *Rand_walk(void* rank)
{
 double north,south,east,west,selected_dir;  //directions of the points
 char* my_dir;
 int my_x,my_y;
 int my_count=0;
 int my_rank=(int)rank;
 if(my_rank==0)
 {
   my_dir="north";
   north=a[my_x=(int)x-1][my_y=(int)y];
 }
 else if(my_rank==1)
 {
   my_dir="west";
   west=a[my_x=(int)x][my_y=(int)y+1];
 } 
 else if(my_rank==2)
 {
   my_dir="south";
   south=a[my_x=(int)x+1][my_y=(int)y];
 }
 else if(my_rank==3)
 {
   my_dir="east";
   east=a[my_x=(int)x][my_y=(int)y-1];
 }
 
 while(1)                 
 {
  west=a[my_x][my_y+1];    //west
  east=a[my_x][my_y-1];    //east
  north=a[my_x-1][my_y];    //north  
  south=a[my_x+1][my_y];    //south
  
  if((north>south)&&(north>east)&&(north>west))
  {
    selected_dir=north;
    display[my_x][my_y]='.';
    my_x=my_x-1;
  }  
  else if((south>east)&&(south>west)) 
  {
    selected_dir=south;
    display[my_x][my_y]='.';
    my_x=my_x+1;
  }
  else if((east>west)) 
  {
    selected_dir=east;
    display[my_x][my_y]='.';
    my_y=my_y-1;
  }
  else
  {
    selected_dir=west; 
    display[my_x][my_y]='.';
    my_y=my_y+1;
  }
  my_count++;
  visited(my_x,my_y); 
  if(my_x==0||my_y==0||my_x==20||my_y==20)
  {
    display[my_x][my_y]='*';
    break;
  }
 } 
 count[my_rank]=my_count; 
  return NULL; 
}//end of Rand_walk function
 
/* Purpose : To make the visited node zero so as to avoid redundancy
 * Input   : Visited node on the graph
 * Output  : Visited nodes on the grpahs will be marked zero
 */
void visited(int mk_z_x,int mk_z_y)
{
  a[mk_z_x][mk_z_y]=0;
} 
/* Purpose : To display the graph with the defined symbols initially
 * Input   : No inputs required 
 * Output  : A graph displaying the visited nodes and originally selected co ordinates etc.,
 */
void Rand_walk_display()
{
  printf("\nRandom Walk\n");
  display[org_x][org_y]='X';
  for(i=0;i<m;i++)
  {
    for(j=0;j<n;j++)
    {
      printf("%c ",display[i][j]);
    }
    printf("\n");
  }
   
}