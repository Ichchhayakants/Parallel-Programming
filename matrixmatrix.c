#include<stdio.h>
#include<mpi.h>

int main()
{
	int rank,size,start,end,chunksize,rem,noofrows;
        int n=4,i,j;
        int matrix[n*n],matrix2[n*n];
	MPI_Status status;
       	MPI_Init(NULL,NULL);        
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
        MPI_Comm_size(MPI_COMM_WORLD,&size);

	chunksize=n/size;
         
       	
	int nchunk[size],displacement[size],temp=0;      
        
        displacement[0]=0;
        for(i=0;i<size;i++)
 	{	nchunk[i]=(n/size);
		 if(i==(size-1))
				nchunk[i]+=(n%size);
		nchunk[i]*=n;
	}
	 for(i=0;i<size;i++)
 	{
	
		displacement[i]=i*((n/size)*n);
	}


	for(i=0;i<(n*n);i++)
		matrix[i]=i;

	for(i=0;i<(n*n);i++)
		matrix2[i]=i;

	
	
	
	int localmatrix2[(nchunk[rank])],result1[n*n];
	for(i=0;i<((nchunk[rank]));i++)
		localmatrix2[i]=0;

	
	//MPI_Scatter(&matrix,tno,MPI_INT,&localmatrix,tno,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatterv(&matrix2,&nchunk[0],&displacement[0],MPI_INT,&localmatrix2,nchunk[rank],MPI_INT,0, MPI_COMM_WORLD);
	MPI_Bcast(&matrix,(n*n),MPI_INT,0,MPI_COMM_WORLD);

	int result[(nchunk[rank])],flag1=1;
		
	
	
	int sum=0,s=0,m=0,l=1,k=0;
	temp=0;
	for(i=0;i<(nchunk[rank]/n);i++)
	{
		for(j=0,k=temp,l=1;j<(n*n);j++,k++,l++)
		{
			if(l == (n+1))
			{
				result[m]=sum;
				l=1;
				m++;
				k=temp;
				sum=0;
			}

			sum+=matrix[j]*localmatrix2[k];
		}

		result[m]=sum;
		sum=0;m++;		
		temp=temp+n;
		
	}
	
	int desprecv[size];
	
	desprecv[0]=0;
	
	for(i=0;i<size;i++)
	{
		desprecv[i+1]=desprecv[i]+nchunk[i];
	}
	
	             
	
	 MPI_Gatherv(&result,nchunk[rank],MPI_INT,&result1,&nchunk[rank],&desprecv[rank],MPI_INT,0,MPI_COMM_WORLD);

  	 if(rank == 0)
 	 {
		for(j=0;j<(n*n);)
		{
		printf("\n");
			for(i=0;i<(n);i++,j++)
			{
		
				printf("%d \t",result1[j]);	
			}
		}
	 }
   
	MPI_Finalize();
        return 0;
}
