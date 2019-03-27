#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
//#include<fstream.h>
int main()
{
	float mat[12]={1,3,1,9,1,1,-1,1,3,11,5,35};
    int n=12,chunksize,i,j,k;
    int pivote=0;
	MPI_Status status,status1;
    MPI_Init(NULL,NULL); 
	int rank;       
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	int size;
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    chunksize=n/size;
    float localmat[chunksize];
float matb[chunksize];
  MPI_Scatter(mat,chunksize,MPI_FLOAT,localmat,chunksize,MPI_FLOAT,0,MPI_COMM_WORLD);
 
for(i=0;i<rank;i++)
   {
    MPI_Recv(&matb,chunksize,MPI_FLOAT,i,0,MPI_COMM_WORLD,&status1);
      for(j=0;j<=i;j++)
         { 
	  for(k=0;k<chunksize;k++)
           {
           localmat[k]/=localmat[i];
          }
         }
       for(j=0;j<chunksize;j++)
         { 
           localmat[j]-=matb[i];
         }
   }

for(i=0;i<chunksize;i++)
   localmat[i]/=localmat[rank];
 
for(i=rank+1;i<size;i++)
MPI_Send(&localmat,chunksize,MPI_FLOAT,rank+1,0,MPI_COMM_WORLD);

for(i=0;i<chunksize;i++)
	{
	  printf(" %f ",localmat[i]);
	}


MPI_Finalize();
}
