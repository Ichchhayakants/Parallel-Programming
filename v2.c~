#include<stdio.h>
#include<mpi.h>
   MPI_Status p;
   int main()
      {
        int v1,v2,a[100],b[100],i,x[100],y[100];
        int rank,chunksize;
        int num =100,sum=0;
        int size;
	double Start_time, end_time;
        int final,ans[50];
	MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    
    
    //Start_time=MPI_Wtime();

  if(rank==0)
   {
    for(i=0;i<num;i++)
     {
       a[i]=i+1;
       b[i]=i;
     }
   }
  
   chunksize=num/size;
   //printf("\nchunksize is %d",chunksize);

  MPI_Scatter(a,chunksize,MPI_INT,x,chunksize,MPI_INT,0,MPI_COMM_WORLD);
  MPI_Scatter(b,chunksize,MPI_INT,y,chunksize,MPI_INT,0,MPI_COMM_WORLD);

	// printf("for the processor %d\n",rank);
 
    for(i=0;i<chunksize;i++)
      { 
        sum+=x[i]*y[i];
       }
	printf("Local sum=%d\n",sum);

  // MPI_Gather(a,chunksize,MPI_INT,x,chunksize,MPI_INT,0,MPI_COMM_WORLD);
 //  MPI_Gather(b,chunksize,MPI_INT,y,chunksize,MPI_INT,0,MPI_COMM_WORLD);
     MPI_Reduce(&sum,&final,1,MPI_LONG,MPI_SUM,0,MPI_COMM_WORLD);
    if(rank==0) 
    {
   //  for(i=0;i<size;i++)
     //   {
       // 
         // final=final+ans[i];
        //}
	
printf("dot product=%d\n",final);
          //end_time=MPI_Wtime();

         // printf("start time=%lf\n",Start_time);
         // printf("end time=%lf\n",end_time);
        
     }
  MPI_Finalize();
  return 0;
}
