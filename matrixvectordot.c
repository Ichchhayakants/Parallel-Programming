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
	int vector1[n],vector2[n];
	
	int chunksize=n/size;
	
	if(rank == size-1)
		chunksize+=((n%size));
	for(i=0;i<(n);i++)
		vector1[i]=i;

	for(i=0;i<(n);i++)
		vector2[i]=i;

	int noofelements[size];
	for(i=0;i<size;i++)
	{
		noofelements[i]=n/size;
		if(i==(size-1))
			noofelements[i]+=n%size;
	}
		
	int displacement[size];

	displacement[0]=0;
	
	for(i=1;i<size;i++)
	{	
		displacement[i]=(displacement[i-1]+noofelements[i]);
		if(i == (size-1))
			displacement[i]-=1;

	}
	
		
	int localvector1[chunksize],localvector2[chunksize];
	int result1[n];
	MPI_Scatterv(vector1,&noofelements[rank],displacement,MPI_INT,localvector1,noofelements[rank],MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatterv(vector2,&noofelements[rank],displacement,MPI_INT,localvector2,noofelements[rank],MPI_INT,0,MPI_COMM_WORLD);
	
	/*for(i=0;i<noofelements[rank];i++)
	{
		if(rank==2)
		printf("%d \n",localvector1[i]);
	}*/
	int sum=0;
	for(i=0;i<n;i++)
	{
		sum+=localvector1[i]*localvector2[i];
	}
	int sum1=0;
	MPI_Reduce(&sum,&sum1,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	
	
	if(rank==0)
	{
		printf("%d \n",sum1);	
	}
	
	MPI_Finalize();
	
	
	return 0;
}	

