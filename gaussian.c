#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	int rank,size;
	FILE *fp;
	int row,column,rowV,columnV,i,j,k,l;
	int chunk;
	float *matrix,*vector,*recvMatrix,*recvVector,*finalMatrix,*finalVector,*ansVector;
	float diagonal,temp;
	MPI_Status status;
	
	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	
	if(rank==0)
	{
			fp=fopen("a.txt","r");
			if (fp == NULL)
			{
				printf("Cannot open file \n");
				exit(0);
	        	}
			fscanf(fp,"%d",&row);
			fscanf(fp,"%d",&column);
			matrix=(float *)malloc(sizeof(float)*(row*column));
			for(i=0;i<row*column;i++)
			{
				fscanf(fp,"%f",&matrix[i]);
			}
			fclose(fp);
		
			fp=fopen("b.txt","r");
			if (fp == NULL)
			{
				printf("Cannot open file \n");
				exit(0);
	        	}
			fscanf(fp,"%d",&rowV);
			fscanf(fp,"%d",&columnV);
			vector=(float *)malloc(sizeof(float)*(rowV*columnV));
			for(i=0;i<rowV*columnV;i++)
			{
				fscanf(fp,"%f",&vector[i]);
			}
			
		}
	
	MPI_Bcast(&row,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(&column,1,MPI_INT,0,MPI_COMM_WORLD);
	
	if(rank != 0)
	{
		matrix=(float *)malloc(sizeof(float)*(row*column));
		vector=(float *)malloc(sizeof(float)*(rowV*columnV));
	}
	
 	chunk=row/size;	
	if(rank == (size-1))
	{
		if(row % size != 0)
		{
			chunk += (row % size);
		}
	}
	chunk *= column;
	
	recvMatrix=(float *)malloc(sizeof(float)*(chunk));
	recvVector=(float *)malloc(sizeof(float)*(1));
	
	MPI_Scatter(matrix, row, MPI_FLOAT,recvMatrix, row, MPI_FLOAT, 0,MPI_COMM_WORLD);
	MPI_Scatter(&vector[rank], 1, MPI_FLOAT,recvVector, 1, MPI_FLOAT, 0,MPI_COMM_WORLD);
	
	
	
	finalMatrix=(float *)malloc(sizeof(float)*row);
	finalVector=(float *)malloc(sizeof(float)*1);
	
	
	for(i=0;i<rank;i++)
	{
		
		MPI_Recv(finalMatrix, chunk, MPI_FLOAT,i, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(finalVector, 1, MPI_FLOAT,i, 1, MPI_COMM_WORLD, &status);
		
	
		temp = recvMatrix[i];
		for(j=0;j<chunk;j++)
		{
			recvMatrix[j] /= temp;
		}
		recvVector[0] /= temp;
		
		for(j=i;j<column;j++)
		{
			recvMatrix[j] -= finalMatrix[j];
		}
		recvVector[0] -= finalVector[0];	
	}
	
	
	if(recvMatrix[rank] != 0)
	{
		diagonal = recvMatrix[rank];
		for(i=rank;i<chunk;i++)
		{
			recvMatrix[i] /= diagonal;
		}
		recvVector[0] /= diagonal;
	}
	
	for(i=rank+1;i<size;i++)
	{
		MPI_Send(recvMatrix, chunk, MPI_FLOAT, i, 1, MPI_COMM_WORLD);
		MPI_Send(recvVector, 1, MPI_FLOAT, i, 1, MPI_COMM_WORLD);
	}
	
	
	
		
		
/*------------- Back Subsitution --------------*/


	ansVector=(float *)malloc(sizeof(float)*1);
	for(i=rank;i<size;i++)
	{
		if(i!=rank)
		{
			MPI_Recv(ansVector, 1, MPI_FLOAT,i, 1, MPI_COMM_WORLD, &status);
			
		}
		
		if(rank != (size-1) && i!=rank)
		{
			ansVector[0] *= recvMatrix[(size-1)-rank];
			recvVector[0] -= ansVector[0];
		}
		

	}
	
	
	
	for(i=rank;i>=0;i--)
	{	if(i!=rank)
		{
			MPI_Send(recvVector, 1, MPI_FLOAT, i, 1, MPI_COMM_WORLD);
		}
	}	
	
	printf("Rank %d =%f\n",rank,recvVector[0]);
	
	MPI_Finalize();
}


