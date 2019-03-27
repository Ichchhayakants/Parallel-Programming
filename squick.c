#include<stdio.h>
#include<stdlib.h>
void Quick_Sort(int Array[],int start,int end);
int Partition(int Array[],int start,int end);
void swap(int *a,int *b);
void main()
{
	int Array[10000],N=10000,i;
	
	long int seed;
	FILE *fp;
	fp=fopen("/dev/urandom","r");
	if(fp==NULL)
	{
		printf("error\n");
		exit(0);
	}
	fread(&seed,sizeof(long),1,fp);
	srand((unsigned) seed);
	for(i=0;i<N;i++)
		Array[i]=rand()%10000;
	Quick_Sort(Array,0,N-1);
	for(i=0;i<N;i++)
	{
		printf("%d",Array[i]);
		printf("\t");
	}
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
