#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#define M 5
#define N 3
#define FALSE 0
#define TRUE 1

/*Maximum resource requirements for N class resources for M processes*/
int MAX[M][N]={{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};

/*The number of resources currently available on the system*/
int AVAILABLE[N]={10,5,7};
/*Number of N class resources allocated by M processes */
int ALLOCATION[M][N]={{1,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
/*M processes also require the amount of resources of N classes */
int NEED[M][N]={{6,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};
/*The amount of N class resources that M processes are requesting at any one time*/
int Request[N]={0,0,0};


int main()
{
	int i=0,j=0;
	char flag='Y';
	char finishFlag='Y';
	void showdata();
	void changdata(int);
	void rstordata(int);
	int chkerr();
	showdata();
	while(finishFlag=='Y'||finishFlag=='y')  //You can allocate resources
	{
	 	i=-1;
		while(i<0||i>=M)    //Determine if the resource number is valid
		{
			printf("Please enter the process number (from 0 to %d, or re-enter!):",M-1);
			scanf("%d",&i);
			if(i<0||i>=M)
				printf("The entered process number does not exist. Reenter!\n");
		}

		printf("Please enter the number of resources requested by process %d\n",i);

		for (j=0;j<N;j++)
		{
			printf("resource %d:",j);
			scanf("%d",&Request[j]);
			if(Request[j]>NEED[i][j]) //A process requests more resources than it needs
			{
				printf("Process %d requested more resources than process %d required resources of class %d! Unreasonable application, wrong! Please reselect!\n",i,i,j);
				flag='N';
				break;
			}
			else
			{
				if(Request[j]>AVAILABLE[j]) //The number of resources requested by the process is greater than the number of such resources available to the system
				{
					printf("The number of resources requested by process %d is greater than the number of resources available to the system in class %d! Unreasonable application, wrong! Please reselect!\n",i,j);
					flag='N';
					break;
				}
			}
		}

		if(flag=='Y'||flag=='y')
		{
			int result;
			changdata(i);
			result=chkerr();
			if(result==1)
			{
				rstordata(i);
				showdata();
			}
			else
				showdata();
		}

		printf("\n");
		printf("To continue the Banker algorithm demo, press 'Y' or 'y' to continue and press 'N' or 'n' to exit: ");
		getchar();
		scanf("%c",&finishFlag);

	}
}

void showdata()     //Displays the allocation of various resources
{
	int i,j;
	printf("The number of resources available to the system is:\n");
	printf(" ");
	for (j=0;j<N;j++)
	{
		printf(" resource%d: %d  ",j,AVAILABLE[j]);
	}
	printf("\n");
	printf("The amount of resources required by each process:\n");
	for (i=0;i<M;i++)
	{
		printf(" process%d  ",i);
		for (j=0;j<N;j++)
		{
			printf("resource%d: %d ",j,NEED[i][j]);
		}
		printf("\n");
	}
	printf("The amount of resources that have been obtained by each process: \n");
	for (i=0;i<M;i++)
	{
		printf(" process%d  ",i);
		for (j=0;j<N;j++)
			printf("resource%d:%d ",j,ALLOCATION[i][j]);
		printf("\n");
	}
}

void changdata(int k)
{
	int j;
	for (j=0;j<N;j++)
	{
		AVAILABLE[j]=AVAILABLE[j]-Request[j];
		ALLOCATION[k][j]=ALLOCATION[k][j]+Request[j];
		NEED[k][j]=NEED[k][j]-Request[j];
	}
}

void rstordata(int k)
{
	int j;
	for (j=0;j<N;j++)
	{
		AVAILABLE[j]=AVAILABLE[j]+Request[j];
		ALLOCATION[k][j]=ALLOCATION[k][j]-Request[j];
		NEED[k][j]=NEED[k][j]+Request[j];
	}
}


int chkerr()   //Check whether the resource can be allocated
{
	int count=0;
	int WORK,FINISH[M],temp[M];
	int i=0,j=0,k=0;
	for(i=0;i<M;i++)FINISH[i]=FALSE;
	for(i=0;i<M;i++)
	{
		j=0;
		count=0;
	if (FINISH[i]==FALSE)
	{
		while(j<N)
		{ 	WORK=AVAILABLE[j];
			if (NEED[i][j]<=WORK)
				count++;
			j++;
		}
			if(count==N)
			{
				for(j=0;j<N;j++)
				{
					WORK=WORK+ALLOCATION[i][j];
				}
				FINISH[i]=TRUE;
				temp[k]=i;
				k++;
				i=-1;
			}
	}
		}
		for(i=0;i<M;i++)
			if(FINISH[i]==FALSE)
			{
				printf("\nThe system is not secure!! The resource application was unsuccessful!!!\n\n");
				return 1;
			}

	printf("\nAfter the security check, the system is safe and the distribution is successful.\n\n");
	printf(" The Safety sequence：");
	for(i=0;i<M;i++)
	{
		printf("process%d->",temp[i]);
	}
	printf("\n");
	return 0;
}
