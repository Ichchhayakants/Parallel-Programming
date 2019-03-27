#include<iostream>
#include<mpi.h>
#include<stdlib.h>
#include<fstream.h>
using namespace std;
int main()
{
	int mat[12],i,j;
    ifstream fin("mat.txt");
    for(i=0;i<12;i++) 
    {
     fin>>mat[i]; 
     cout<<mat[i];
	}

	MPI_Status status,status1;
    MPI_Init(NULL,NULL);        
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
       

MPI_Finalize();

}
