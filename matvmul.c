#include<stdio.h>
#include<mpi.h>
  
int main()
{
	int i,j,r,c,size,rank,chunksize,a[100],b[100],x[100],mul=0; 
    
	MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    

if(rank==0)
{
	printf("\n Enter Number of row and col :\n");
    scanf("%d%d",&r,&c);
	printf(" Enter Matrix :\n");
 
	for(i=0;i<r;i++)
    for(j=0;j<c;j++)    
    {
    	scanf("%d",&a[i*c+j]);               
    }
    
	printf(" Enter Vector :\n");
    
    for(i=0;i<c;i++)
    scanf("%d",&b[i]);              
}



MPI_Barrier(MPI_COMM_WORLD);
MPI_Bcast(&c,1, MPI_INT,0, MPI_COMM_WORLD);
MPI_Bcast(&r,1, MPI_INT,0, MPI_COMM_WORLD);
MPI_Bcast(b,c, MPI_INT,0, MPI_COMM_WORLD);
chunksize=r*c/size;
MPI_Scatter(a,chunksize,MPI_INT,x,chunksize,MPI_INT,0,MPI_COMM_WORLD);

	
	for(i=0;i<c;i++)
    {
	mul=0;
    	for(j=0;j<c;j++)
    	{ 
    		mul=mul+x[i*c+j]*b[j];
			x[i]=mul;
		}              
	}


MPI_Gather(x,chunksize/c,MPI_INT,a,chunksize/c,MPI_INT,0,MPI_COMM_WORLD);
    

if(rank==0)
{
	printf("Result Vector :\n");
	for(j=0;j<c;j++)
    printf("%d\n",a[j]);
         
}

MPI_Finalize();
return 0;

}
