#include<stdio.h>
#include<mpi.h>
   MPI_status p;

   int main()
      {
        int v1,v2,a[100],b[100],i,x[100],y[100];
        int rank,chunksize[50];
        int num =100,sum=0;
        int size;

    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Init(NULL,NULL);


  if(rank==0)
   {
    for(i=0;i<num;i++)
     {
       a[i]=i+1;
       b[i]=i+2;
     }
   }
  
   chunksize=num/size;
   printf("\nchunksize is %d",chunksize);

  MPI_Scatter(a,chunksize,MPI_INT,x,chunksize,MPI_INT,0,MPI_COMM_WORLD);
  MPI_Scatter(b,chunksize,MPI_INT,y,chunksize,MPI_INT,0,MPI_COMM_WORLD);

 printf("for the processor",rank);
 
    for(i=0;i<chunksize;i++)
      { 
        sum+=x[i]*y[i];
        printf("%d",num);
      }

  MPI_Finalize();
  return 0;
}
