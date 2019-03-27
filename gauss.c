#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
//#include<fstream.h>
int main()
{
	float mat[12]={1,3,1,9,1,1,-1,1,3,11,5,35};
    int n=12,chunksize,i,j;
    int pivote=0;
	MPI_Status status,status1;
    MPI_Init(NULL,NULL); 
	int rank;       
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	int size;
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    chunksize=n/size;
    float localmat[chunksize];
  MPI_Scatter(mat,chunksize,MPI_FLOAT,localmat,chunksize,MPI_FLOAT,0,MPI_COMM_WORLD);
  
   
 
 pivote=localmat[0];
MPI_Bcast(&pivote,1,MPI_INT,0,MPI_COMM_WORLD);
//printf("rank pivote %d%d ",rank,pivote);
/*for(i=0;i<chunksize;i++)
	{
	  printf(" %f ",localmat[i]);
	}*/

//if(rank==0)
 //{
 //printf("rank=%d",rank);
 for(i=0;i<chunksize;i++)
  {
   localmat[i]=localmat[i]/localmat[0];
MPI_Send(&localmat,chunksize,MPI_FLOAT,rank+1,0,MPI_COMM_WORLD);
  }
 //}
float matb[chunksize];
for(rank=1;rank<size;rank++)
  {
   MPI_Recv(&matb,chunksize,MPI_INT,rank-1,0,MPI_COMM_WORLD,&status);
   for(i=0;i<chunksize;i++)
    {
	 localmat[i]=localmat[i]-matb[i];
     localmat[i]=localmat[i]/localmat[rank];
    } 
   //MPI_Send(&localmat,chunksize,MPI_FLOAT,rank+1,0,MPI_COMM_WORLD);
   //MPI_Recv(&mat,count2,MPI_INT,rank-1,1,MPI_COMM_WORLD,&status);
  }

printf("rank=%d\n",rank);
for(i=0;i<chunksize;i++)
	{
	  printf(" %f ",localmat[i]);
	}


MPI_Finalize();
}
