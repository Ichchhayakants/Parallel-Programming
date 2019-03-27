#include<stdio.h>
#include<mpi.h>
  

 MPI_Status p;
   int main()
      {
        int v1,v2,a[100][100],b[100],x[100],y[100];
          int ans[100],xans[100];   
     int rank,chunksize;
          int mul=0;       
           int nc,nr;
         int num =100,sum=0;
        int size;
         int i,j;
	double Start_time, end_time;
        int final;


	MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    

if(rank==0)
   {
nr=4;
nc=3;           

                for(i=0;i<nr;i++)
                     for(j=0;j<nc;j++)    
                         a[i][j]=i+j;              
 }


  MPI_Bcast(&nc,1, MPI_INT,0, MPI_COMM_WORLD);
  MPI_Bcast(&nr,1, MPI_INT,0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);


     chunksize=nr/size;

      
       MPI_Scatter(a,chunksize*nc,MPI_INT,x,chunksize*nc,MPI_INT,0,MPI_COMM_WORLD);


        for(i=0;i<chunksize;i++)
               {
             
                        for(j=0;j<nc;j++)
                             printf("[ %d ->%d] ",x[i*nc+j],rank);
               }


    MPI_Barrier(MPI_COMM_WORLD);

MPI_Finalize();

}
