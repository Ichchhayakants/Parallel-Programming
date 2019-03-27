#include<stdio.h>
#include<mpi.h>   

int main()
{
	MPI_Status p;
	int rank;
        int size;
         int i,j;
	

	MPI_Init(NULL,NULL);
    	MPI_Comm_size(MPI_COMM_WORLD,&size);
    	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    	

	int n=4;
	int matrix[n*n],vector[n];
	
	for(i=0;i<(n*n);i++)
		matrix[i]=i;

	for(i=0;i<(n);i++)
		vector[i]=i;

	
	int noofrows;
	noofrows=n/size;
		
	if(rank == (size-1))
		noofrows+=(n%size);

	int noofelements[size];
	int displacement[size];

	displacement[0]=0;
	
	for(i=1;i<size;i++)
	{
		displacement[i]=displacement[i-1]+n;
	}
	int temp=0;
	
	for(i=0;i<size;i++)
	{
		noofelements[i]=n/size;
		if(i == (size-1))
		{
				noofelements[i]+=n%size;
		}
		noofelements[i]*=n;
	}
	
	
	int localmatrix[n*n];
	int result1[n];
	MPI_Scatterv(matrix,&noofelements[rank],displacement,MPI_INT,localmatrix,noofelements[rank],MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(vector,n,MPI_INT,0,MPI_COMM_WORLD);

	
	int sum=0;
	int result[(noofrows)],k;
	for(i=0,k=0;i<(noofelements[rank]);k++)
	{
		sum=0;
		for(j=0;j<n;j++,i++)
		{
			sum+=localmatrix[i]*vector[j];
		}
		result[k]=sum;
	}
	
/*	for(i=0;i<(noofrows);i++)
	{
		if(rank ==2 )
		printf("%d \n",result[i]);
	}
*/		
	int noofrecv[size];
	int desprecv[size];
	desprecv[0]=0;
	for(i=0;i<size;i++)
	{
		noofrecv[i]=noofelements[i]/n;
		desprecv[i+1]=desprecv[i]+1;
	}

		MPI_Gatherv(&result,noofrecv[rank],MPI_INT,result1,&noofrecv[rank],desprecv,MPI_INT,0,MPI_COMM_WORLD);

	if(rank==0)
	{
	for(i=0;i<n;i++)
	printf("%d \n",result1[i]);	
	}
	
	MPI_Finalize();
	
	
	return 0;
}	
