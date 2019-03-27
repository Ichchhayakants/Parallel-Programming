#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
void Quick_Sort(int Array[],int start,int end);
int Partition(int Array[],int start,int end);
void swap(int *a,int *b);
MPI_Status b;
int main()
{
	int Array[100],N=100,i,j,rank,size,chunk_size,pivot,send_count[100],rec[100],gp[100],lp[100],m,m1,cgp=0,clp=0,c1=0,c2=0,count1=0,count2=0,lessp[100],grep[100],p1,p2,n1=0,n2=0,recl[100],recg[100],r[100],rg[100];
	long int seed;
	FILE *fp;
	MPI_Init(NULL,NULL);
 	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	chunk_size=N/size;
	m=size/2;
	if(rank==0)
	{
		fp=fopen("/dev/urandom","r");
		if(fp==NULL)
		{
			printf("error\n");
			exit(0);
		}
		fread(&seed,sizeof(long),1,fp);
		srand((unsigned) seed);
		for(i=0;i<N;i++)
			Array[i]=rand()%1000;
			pivot=Array[0];
	
        }
        MPI_Bcast(&pivot,1,MPI_INT,0,MPI_COMM_WORLD);
        MPI_Scatter(Array,chunk_size,MPI_INT,rec,chunk_size,MPI_INT,0,MPI_COMM_WORLD);
     
        for(i=0;i<chunk_size;i++)
        {
        	if(rec[i]<pivot)
        	{
        		lp[clp]=rec[i];
        		clp++;
        	}
        	else
        	{
        		gp[cgp]=rec[i];
        		cgp++;
        	}
        }
     
       if(rank<2)
        {
        	MPI_Send(&cgp,1,MPI_INT,rank+2,0,MPI_COMM_WORLD);
        	MPI_Send(gp,cgp,MPI_INT,rank+2,1,MPI_COMM_WORLD);
        	MPI_Recv(&count1,1,MPI_INT,rank+2,2,MPI_COMM_WORLD,&b);
        	MPI_Recv(lessp,count1,MPI_INT,rank+2,3,MPI_COMM_WORLD,&b);
        		c1+=count1;
        		
        	for(i=clp,j=0;j<clp+count1;i++,j++)
        		lp[i]=lessp[j];
        }
        else
        {
        	MPI_Recv(&count2,1,MPI_INT,rank-2,0,MPI_COMM_WORLD,&b);
        	MPI_Recv(grep,count2,MPI_INT,rank-2,1,MPI_COMM_WORLD,&b);
        	MPI_Send(&clp,1,MPI_INT,rank-2,2,MPI_COMM_WORLD);
        	MPI_Send(lp,clp,MPI_INT,rank-2,3,MPI_COMM_WORLD);
        	c2+=count2;
        	for(i=cgp,j=0;j<cgp+count2;i++,j++)
        		gp[i]=grep[j];
        }
    
        if(rank==0)
        {
        	p1=lp[0];
        	MPI_Send(&p1,1,MPI_INT,1,4,MPI_COMM_WORLD);
        }
        else if(rank==1)
        	MPI_Recv(&p1,1,MPI_INT,0,4,MPI_COMM_WORLD,&b);
        else if(rank==2)
        {
        	p2=gp[0];
        	MPI_Send(&p2,1,MPI_INT,3,5,MPI_COMM_WORLD);
        }
        else
        	MPI_Recv(&p2,1,MPI_INT,2,5,MPI_COMM_WORLD,&b);
        
        if(rank<2)
        {
        	for(i=0;i<c1;i++)
        	{
        		if(lp[i]<p1)
        		{
        			recl[n1]=lp[i];
        			n1++;
        		}
        		else
        		{
        			recg[n2]=lp[i];
        			n2++;
        		}
        	}
        }
        else
        {
        	for(i=0;i<c2;i++)
        	if(gp[i]<p2)
        		{
        			recl[n1]=gp[i];
        			n1++;
        		}
        		else
        		{
        			recg[n2]=gp[i];
        			n2++;
        		}
        }
       if(rank==0)
        {
        	MPI_Send(&n2,1,MPI_INT,1,5,MPI_COMM_WORLD);
        	MPI_Send(recg,n2,MPI_INT,1,6,MPI_COMM_WORLD);
        	MPI_Recv(&m,1,MPI_INT,1,7,MPI_COMM_WORLD,&b);
        	MPI_Recv(r,m,MPI_INT,1,8,MPI_COMM_WORLD,&b);
        	for(i=n1,j=0;i<(n1+m);i++,j++)
        	{
        		recl[i]=r[j];
        	}
        }
        else if(rank==1)
         {
        	MPI_Send(&n1,1,MPI_INT,0,7,MPI_COMM_WORLD);
        	MPI_Send(recl,n1,MPI_INT,0,8,MPI_COMM_WORLD);
        	MPI_Recv(&m1,1,MPI_INT,0,5,MPI_COMM_WORLD,&b);
        	MPI_Recv(rg,m1,MPI_INT,0,6,MPI_COMM_WORLD,&b);
        	for(i=n2,j=0;i<(n2+m1);i++,j++)
        	{
        		recg[i]=rg[j];
        	}
        }
    else if(rank==2)
        {
        	MPI_Send(&n2,1,MPI_INT,3,9,MPI_COMM_WORLD);
        	MPI_Send(recg,n2,MPI_INT,3,10,MPI_COMM_WORLD);
        	MPI_Recv(&m,1,MPI_INT,3,11,MPI_COMM_WORLD,&b);
        	MPI_Recv(r,m,MPI_INT,3,12,MPI_COMM_WORLD,&b);
        	for(i=n1,j=0;i<(n1+m);i++,j++)
        	{
        		recl[i]=r[j];
        	}
        	
        	
        }
        else if (rank==3)
        {
        	MPI_Send(&n1,1,MPI_INT,2,11,MPI_COMM_WORLD);
        	MPI_Send(recl,n1,MPI_INT,2,12,MPI_COMM_WORLD);
        	MPI_Recv(&m1,1,MPI_INT,2,9,MPI_COMM_WORLD,&b);
        	MPI_Recv(rg,m1,MPI_INT,2,10,MPI_COMM_WORLD,&b);
        	for(i=n2,j=0;i<(n2+m1);i++,j++)
        	{
        		recg[i]=rg[j];
        	}
        	
        }
        
        	printf("\n\t rank=%d\n",rank);
        if(rank==0||rank==2)
        {
        	
        	for(i=0;i<(n1+m)-1;i++)
        	{
        		//if(recl[i]
        		//printf("%d\n",recl[i]);
        	}
        }
     if(rank==1||rank==3)
        {
        	for(i=0;i<(n2+m1);i++)
        	{
        		//printf("%d\n",recg[i]);
        	}
        }
        if(rank==0||rank==2)
        {
		Quick_Sort(recl,0,n1+m-1); 
		//sleep(rank);  
	for(i=0;i<n1+m-1;i++)
	printf("%d\n",recl[i]);   
	}
	if(rank==1||rank==3)
	{
		Quick_Sort(recg,0,n2+m1-1); 
		//sleep(rank);  
	for(i=0;i<n2+m1-1;i++)
	printf("%d\n",recg[i]);   
	}  
         MPI_Finalize();
 }
void swap(int *a,int *b)
{
	int t;
	t=*a;
	*a=*b;
	*b=t;
}
int Partition(int Array[],int start,int end)
{
	int i,pivot=Array[end];
	int Partition_Index=start;
	for(i=start;i<end;i++)
	{
		if(Array[i]<=pivot)
		{
			swap(Array+Partition_Index,Array+i);
			Partition_Index++;
		}
	}
	swap(Array+Partition_Index,Array+end);
	return Partition_Index;
}
void Quick_Sort(int Array[],int start,int end)
{
	if(start<end)
	{
		int Partition_Index=Partition(Array,start,end);
		Quick_Sort(Array,start,Partition_Index-1);
		Quick_Sort(Array,Partition_Index+1,end);
	}
	
}
