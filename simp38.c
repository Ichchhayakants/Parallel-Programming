#include<stdio.h>
#include<math.h>
#include<mpi.h>
MPI_Status p;
double fun(double x);
void main()
{
	int rank,size,a=0,b=1,n=21,i;
	double start,end,h,h2,x,value=0,sum=0,f0,f1;
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	h=(double)(b-a)/size;
	start=rank*h;
	end=start+h;
	h2=(double)(end-start)/n;
	//printf("\tstart=%lf,end=%lf,h2=%lf\n\t",start,end,h2);
	for(i=1;i<n;i++)
	{
		x=start+h2;
		if(i%3==0)
			value=value+2*fun(x);
		else
			value=value+3*fun(x);	
	}
	f0=fun(start);
	f1=fun(end);
	value=(3*h2)/8*(value+f0+f1);
	//printf(" value for value=%lf\n\t",value);
	MPI_Reduce(&value,&sum,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	if(rank==0)
	{
		printf("soln to fun using simpson's 3/8 rule-->%lf\n",sum);
	}
	MPI_Finalize();
}
double fun(double x)
{
	return (2+sin(2*sqrt(x)));
}
