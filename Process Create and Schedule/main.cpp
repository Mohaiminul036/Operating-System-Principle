#include"stdio.h"
#include"stdlib.h"
#include "string.h"
#include "ctime"
#include <iostream>
#include<windows.h>
#define WAIT 1
#define RUN 2
#define FINISH 3
using namespace std;
typedef struct pcb
{
  int num;
  struct pcb *next;
  int priority;
  int timeneed;
  int state;
}pcb;/*Use this structure to simulate a process*/

struct pcb *head;
struct pcb *run;

pcb *jccreat(int n)/*This function is used to create a process queue*/
{
 int i=1;
 pcb *head,*p,*q;
 head=(pcb *)malloc(sizeof(pcb));/*Create a blank header*/
 p=head;

 for(i=1;i<=n;i++)/*Use a loop to create a specified node*/
 {
//	 srand((unsigned int)time(NULL));//
  q=(pcb *)malloc(sizeof(pcb));
                p->next=q;
  q->num=i;
  q->next=NULL;

  q->priority=1+(10*rand()/(RAND_MAX+1.0));/*Randomly generate priorities*/
  q->timeneed=1+(100*rand()/(RAND_MAX+1.0));/*Randomly generate running time*/
  q->state=WAIT;
  p=q;
 }

 return head;/*Returns a pointer to the header*/
}

pcb *getmaxpriority(struct pcb *head)/*This function is used to select the process with the highest priority for execution*/
{
  struct pcb *p,*q;
  int max;
  p=head->next;
  max=p->priority;/*Initial max is the priority of the first node of the team*/
  q=p;
  while(p)
  {
   if(p->priority>max)/*Compare one by one to select the node with the largest priority*/
   {max=p->priority;
    q=p;}
   p=p->next;
  }
  return q;
}

void delect(struct pcb *head,struct pcb *run)/*This function is used to remove the finished process from the process queue*/
{
	struct pcb *q=head;

	while(q->next)/*Scan the process queue to find the finished process*/
	{
		if(q->next->num==run->num)/*Determine if the process is complete*/
		{
			if(run->next!=NULL)
				q->next=run->next;
			else q->next=NULL;
			free(run);/*Free up space for application*/
			return;
		}
	q=q->next;
	}

}
int i=0;
void control()/*This function is used to control the execution and scheduling of individual processes*/
{
	struct pcb *p;
	run=head->next;/*Start with the first process running*/
	run->state=RUN;
	while(run)
	{
		if(run->timeneed>0)/*If the current run pointer points to a process that does not take zero time and is in a running state, let the process run*/
		if(run->state==RUN)
		{
			printf("pcb%d is running.\n",run->num);
			printf("Waiting list:");/*Displays the entire wait queue*/
			p=head->next;
			while(p)
			{
				if(p!=run)
				printf("pcb%d  ",p->num);
				p=p->next;
			}
			printf("\n");
			Sleep(500);/*Simulated process running*/
			if(run->timeneed>10)
				run->timeneed=run->timeneed-run->timeneed/10;/*The process takes time to reduce*/
			else
				run->timeneed--;
			run->priority=run->priority-1;/*Process priority minus 1*/
			cout<<run->timeneed;
			cout<<"\t";
			cout<<run->priority;
			cout<<"\n";
			if(i==5)
			{ i=0;
			  getchar();}
			else
			  i++;
			}

			if(run->timeneed!=0)
			{
				if(run->priority<=head->next->priority)/*If the currently completed process has a lower priority than the queue leader process*/
				{	run->state=WAIT;
					run=getmaxpriority(head);/*A process with the highest priority is selected from the process queue to run*/
					run->state=RUN;}
			}
			else
            { printf("pcb%d is finished.\n",run->num);
              Sleep(500);
              delect(head,run);/*Delete this node*/
              if(head->next!=NULL)/*Determines if the process queue is empty*/
              {run=head->next;
              run->state=RUN;}
              else
              {
printf("All progresses are done.\n");
               		return;
}
             }
       }
}

int main()
{
	int n;
	int flag=1;

	printf("Enter the number of the progresses:");
	scanf("%d",&n);/*Enter the number of processes to be created*/

	head=jccreat(n);/*Creates a process queue that assigns the header of a linked list to the head pointer*/
	run=head->next;/*The run pointer points to the PCB of the running process*/
	while(run)
	{
		printf("num: %d ,priority: %d ,timenees: %d \n",run->num,run->priority,run->timeneed);
 		run=run->next;
	} /*Print out the queue of processes you just created*/
	while(flag)/*The value of flag determines whether to continue the control() function*/
	{
		if(head->next)/*Determines if the process is complete*/
			control();
		else flag=0;
	}
	getchar();
}
