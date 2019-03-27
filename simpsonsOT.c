#include<mpi.h>
#include<stdio.h>
#include<math.h>
MPI_Status b;
double fun(double a)
 {
   //double tmp = a*a*a*a;
   double temp=2+sin(2*sqrt(a));
   return tmp;
 }
int main()
{
	int rank,size,chunk_size,start,end,i,n=6,a=-3,b=3;
	double it[1],h,a1[1],b1,f0,f1,fn,x,area,sum=0;
	int cnt=1;
	double simpans;
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	 chunk_size=n/size;
	it[0] =(double) (b-a)/size ;
	
	double sendmat[size];
	if(rank == 0)
	 {
	   sendmat[0]=a;
	   for(i=1;i<size;i++)
	    {
	     sendmat[i] = sendmat[i-1]+it[0];
	    }
	    for(i=0;i<size;i++)
	    {
	    //printf("%f\n",sendmat[i]);
	    }
	 }
	 MPI_Scatter(sendmat,cnt,MPI_DOUBLE,a1,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
	 MPI_Bcast(it,1,MPI_INT,0,MPI_COMM_WORLD);
	 
	 b1=a1[0]+it[0];
	  h = (double) (b1-a1[0])/n;
	  x=a1[0];
	  f0 = fun(a1[0]);
	  fn = fun(b1);
	
	 for(i=1;i<n;++i)
	  {
	    x = x+h;
	    if(i%3 == 0)
	      {
	        f1 = 2*fun(x);
	      }
	    else
	      {
	       f1 = 3*fun(x);
	      }  
	      
	      sum = sum + f1;
	   
	  }//end for
	  sum = sum+f0+fn;
	  area = sum*((3*h)/8); 
	
	MPI_Reduce(&area,&simpans,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
         if(rank == 0) 
	printf("Simpson 3/8 = %lf\n",simpans);
	
	MPI_Finalize();
	
}//end for main()	
