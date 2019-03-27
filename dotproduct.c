#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
void main()
{
	int rank,size;
	char name[1024];
	int resultlen;
	int n=4,i;
	int X[n],Y[n];
	int localX[n],localY[n];
	int chunk;
	int displs1[100],displs2[100],chunkA[100];
	int sum=0,recvSum=0,endSum=0;
	MPI_Status status;
	double startTime,endTime;

	MPI_Init(NULL,NULL);
	startTime = MPI_Wtime();
	MPI_Get_processor_name(name,&resultlen);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	
	int recvSumA[size];

	if(rank==0)
	{
		for(i=0;i<n;i++)
		{
			X[i]=i+1;
			Y[i]=i+1;
		}
	}

	for(i=0;i<size;i++)
	{
	chunkA[i] = n/size;

	if(i == size-1){
		chunkA[i] = chunkA[i] + (n%size);
		
	}
	}

	for(i=0;i<size;i++)
	{
		displs1[i] = i*(n/size);
		displs2[i] = i*(n/size);
	}
	
	MPI_Scatterv(X, chunkA, displs1,MPI_INT, localX, chunkA[rank],MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatterv(Y, chunkA, displs2,MPI_INT, localY, chunkA[rank],MPI_INT, 0, MPI_COMM_WORLD);


	
	for(i=0;i<chunkA[rank];i++)
	{
		
		sum = sum + (localX[i]*localY[i]);
		
	}

	
	MPI_Reduce(&sum, &endSum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if(rank==0)
	{
		printf("Dot Product = %d\n",endSum);
	}
	

	MPI_Finalize();


}
