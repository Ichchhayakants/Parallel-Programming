#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
MPI_Status p;
void main()
{
	FILE *fp;
	int i,size,rank,Nr=0,Na=0,R=1,N=10000;
	long int seed;
	double x[10000],y[10000],xn,yn,eq,pi,fpi;
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	fp=fopen("/dev/urandom","r");
	if(fp==NULL)
	{
		printf("error\n");
		exit(0);
	}
	//fscanf(fp,"%ld",&seed);
	fread(&seed,sizeof(long),1,fp);
	srand((unsigned) seed);
	for(i=0;i<N;i++)
	{
		x[i]=(double)rand()/RAND_MAX;
		y[i]=(double)rand()/RAND_MAX;
	}
	for(i=0;i<N;i++)
	{
		xn=x[i];
		yn=y[i];
		eq=(xn*xn)+(yn*yn)-(R*R);
		if(eq<=0)
			Na++;
		else
			Nr++;
	}
	pi=(double)Na/N;
	pi=pi*4;
	MPI_Reduce(&pi,&fpi,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	fpi=fpi/size;
	printf("Value of Pi %lf on processor %d\n\t",pi,rank);
	if(rank==0)
		printf("Final Value of Pi=%lf\n",fpi);

	
MPI_Finalize();
}
