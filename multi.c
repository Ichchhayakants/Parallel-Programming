#include<stdio.h>
#include<mpi.h>
   MPI_Status p;
   int main()
      {
        int v1,v2,a[100],b[100],x[100],y[100];
        int rank,chunksize;
          int mul=0;       
           int nc,nr;
         int num =100,sum=0;
        int size;
         int i,j;
	double Start_time, end_time;
        int final,ans[50];


	MPI_Init(NULL,NULL);

    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    

if(rank==0)
   {
            printf("\n Enter Number of row and col :\n");
            scanf("%d%d",&nr,&nc);

              printf(" Enter Matrix :\n");

                for(i=0;i<nr;i++)

                     for(j=0;j<nc;j++)  
  
                         scanf("%d",&a[i*nc+j]);              
 
              printf(" Enter Vector :\n");
               
                      for(i=0;i<nc;i++)
                    
                      scanf("%d",&b[i]);              

  }

  MPI_Barrier(MPI_COMM_WORLD);

   

  MPI_Bcast(&nc,1, MPI_INT,0, MPI_COMM_WORLD);
  MPI_Bcast(&nr,1, MPI_INT,0, MPI_COMM_WORLD);

  MPI_Bcast(b,nc, MPI_INT,0, MPI_COMM_WORLD);

  chunksize=nr*nc/size;

  MPI_Scatter(a,chunksize,MPI_INT,x,chunksize,MPI_INT,0,MPI_COMM_WORLD);

//  printf("Chunk %d \n",chunksize);


        for(i=0;i<chunksize/nc;i++)
               {
                        mul=0;
                        for(j=0;j<nc;j++)
                        mul=mul+x[i*nc+j]*b[j];

                        x[i]=mul;
                        printf(" %d ",mul);     
           
                }


  MPI_Gather(x,chunksize,MPI_INT,a,chunksize,MPI_INT,0,MPI_COMM_WORLD);
    
  if(rank==0)
      {

        for(j=0;j<nc;j++)
        printf(" %d  ",x[j]);
         
          
       }


  MPI_Finalize();
  return 0;

}
