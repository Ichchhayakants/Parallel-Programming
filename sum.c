#include<stdio.h>
#include<mpi.h>
#include <sys/time.h>
int main()
{
	int rank,size;
	int sum=0;
	int sumRcv;
	int totalSum=0;
	char name[1024];
	int resultlen;
	int start,end,i,chunk=0;
	int n=1000;

	MPI_Init(NULL,NULL);
	

   


	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	chunk = n/size;
	start = rank * chunk + 1;
	end = start + chunk - 1;
	if(rank == size-1)
		if(n%size!=0)
		{
			end = end + (n%size);
		}
	MPI_Status status;
	//sleep(rank);
	for(i=start;i<=end;i++)
	{
		sum=sum+i;
	}
	int tag=1;
	printf("Processor = %d\tStart = %d\tEnd = %d\tSum = %d\n",rank,start,end,sum);
	if(rank!=0)
	{
		MPI_Send(&sum, 1, MPI_INT, 0,tag, MPI_COMM_WORLD);
	}
	else
	{
		for(i=1;i<size;i++)
		{
			MPI_Recv(&sumRcv,1,MPI_INT,i,tag,MPI_COMM_WORLD,&status);
			sum = sum + sumRcv;
		}
		//sleep(size);
		printf("Total Sum = %d\n",sum);
	}
      MPI_Finalize();
}
