#include <mpi.h>
#include<unistd.h>
#include <stdio.h>
#include<stdlib.h>


#define SIZE 16
#define UP 0
#define DOWN 1
#define LEFT 0
#define RIGHT 1
int main(int argc, char *argv[]) 
{
	int numtasks, rank, source, dest, outbuf, i, tag=1,
	nbrs[4], dims[2]={4,4},periods[2]={1,1}, reorder=0, coords[2],vert[2],horz[2];

	int hdata=0,tmp=0,tmp1=0,rows=4,cols=4,vdata=0,hshift=1,vshift=1,prod=0;
	float *matrix,*matrix1,*ansMatrix;
	float A,B,tempA,tempB,C;
	int row,column,row1,column1;
	FILE *fp;
	MPI_Status status;
	
	MPI_Comm cartcomm;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if (numtasks == SIZE) 
	{
		MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, reorder, &cartcomm);

		MPI_Comm_rank(cartcomm, &rank);

		MPI_Cart_coords(cartcomm, rank, 2, coords);


		if(rank==0)
		{
			if(argv[1]!=NULL)
			{
				fp=fopen(argv[1],"r");
				if (fp == NULL)
				{
					printf("Cannot open file \n");
					exit(0);
				}
				fscanf(fp,"%d",&row);
				fscanf(fp,"%d",&column);
			
				//Accepting matrix from file as a 1D array.
				matrix=(float *)malloc(sizeof(float)*(row*column));
				for(i=0;i<row*column;i++)
				{
					fscanf(fp,"%f",&matrix[i]);
				}
				fclose(fp);
			}
			else
			{
				printf("Please Enter the file name");
				exit(0);			
			}
		
			if(argv[2]!=NULL)
			{
				fp=fopen(argv[2],"r");
				if (fp == NULL)
				{
					printf("Cannot open file \n");
					exit(0);
				}
				fscanf(fp,"%d",&row1);
				fscanf(fp,"%d",&column1);
			
				matrix1=(float *)malloc(sizeof(float)*(row1*column1));
				for(i=0;i<row1*column1;i++)
				{
					fscanf(fp,"%f",&matrix1[i]);
				}
				fclose(fp);
			}
			else
			{
				printf("Please Enter the file name");
				exit(0);			
			}
		}
		
		
		
	
		MPI_Bcast(&row,1,MPI_INT,0,MPI_COMM_WORLD);
		MPI_Bcast(&column,1,MPI_INT,0,MPI_COMM_WORLD);
	
		MPI_Scatter(matrix, 1, MPI_FLOAT, &A, 1, MPI_FLOAT, 0,MPI_COMM_WORLD);
		MPI_Scatter(matrix1, 1, MPI_FLOAT, &B, 1, MPI_FLOAT, 0,MPI_COMM_WORLD);
	
		
		C=0;
		for(i=0; i<rows;i++)
		{
			if(i==0)
			{
				hshift=rank/row;
				vshift=rank%row;
			}
			else
				hshift=vshift=1;
		



        	{

			
				MPI_Cart_shift(cartcomm, 1, hshift, &horz[LEFT], &horz[RIGHT]);
				MPI_Cart_shift(cartcomm, 0, vshift, &vert[UP], &vert[DOWN]);
			}
			
	
			MPI_Send(&A, 1, MPI_FLOAT, horz[LEFT], 1, MPI_COMM_WORLD);
			MPI_Recv(&tempA, 1, MPI_FLOAT, horz[RIGHT], 1, MPI_COMM_WORLD, &status);
			A = tempA;
		
			MPI_Send(&B, 1, MPI_FLOAT, vert[UP], 1, MPI_COMM_WORLD);
			MPI_Recv(&tempB, 1, MPI_FLOAT, vert[DOWN], 1, MPI_COMM_WORLD, &status);
			B = tempB;
		
			
			C += (A*B); 
		
		}
		
	
		ansMatrix=(float *)malloc(sizeof(float)*(row*column));
		
		MPI_Gather(&C, 1, MPI_FLOAT,ansMatrix, 1, MPI_FLOAT, 0,MPI_COMM_WORLD);
		if(rank==0)
		{
			for(i=0;i<(row*column);i++)
			{
				printf("Mat[%d] = %f\n",i,ansMatrix[i]);	
			}
		}
			
	}
	else
	{
		printf("Must specify %d processors. Terminating.\n",SIZE);
	}
	MPI_Finalize();
}
