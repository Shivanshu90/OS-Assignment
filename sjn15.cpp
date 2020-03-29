#include<iostream>
#include<stdio.h>
#include<conio.h>
int main()
{
	int i,a,j,w,p[10],n, tatt=0, watt=0,total_burst_time=0;
	int burst_time[10],temp,arrival_time[10],t,wait_time[10],ct[10],turn_around_time[10],wt[10],ta=0;
	int at[10],process[10],bt[10];
	float total_tat_time=0,total_wait_time=0;
	float priority[10]={0};
	
	x:
	printf("\nEnter the Number of Processes: ");
	scanf("%d",&n);
	if(n>0)
	{
	
		for(int i=0; i<n; i++) 
		{ 
			printf("...Process %d...", (i+1),"...\n"); 
			printf("\nEnter Process Id: "); 
			scanf("%d",&p[i]); 
			y:
			printf("Enter Arrival Time: "); 
			scanf("%d",&arrival_time[i]);
			if(arrival_time[i]<0)
			{
				printf("Invalid Input. Please try again...\n");
				goto y;				
			}
			z:
			printf("Enter Burst Time: "); 
			scanf("%d",&burst_time[i]);
			if(burst_time[i]<=0)
			{
				printf("Invalid Input. Please try again...\n");
				goto z;				
			}
			printf("\n");
		}
		printf("\n\n\n\n");	
		printf(" \t\t\t-------------------------Before Scheduling------------------------\n\n\n"); 
		printf("\t\t\t\tProcess ID\tArrival Time\tBurst Time\n"); 
		for(i=0; i<n; i++) 
		{ 
			printf("\n\t\t\t\t\tP%d\t\t%d\t\t%d\t", p[i],arrival_time[i],burst_time[i],"\n"); 
		}

		//To calculate the earliest(shortest) arrival time.
		a=arrival_time[0];
		for(i=0;i<n;i++)
		{
			if(a>arrival_time[i])
			a=arrival_time[i];
		}

		//Swapping the processes according to shortest-job-next
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				if(arrival_time[i]<arrival_time[j])
				{
					temp=p[j];
					p[j]=p[i];
					p[i]=temp;

					temp=arrival_time[j];
					arrival_time[j]=arrival_time[i];
					arrival_time[i]=temp;

					temp=burst_time[j];	
					burst_time[j]=burst_time[i];
					burst_time[i]=temp;
				}
			}
		}

		//Calculating the priority of each process.
		int time=burst_time[0];
		for(i=1;i<n;i++)
		{  
			if(time>=arrival_time[i])
			{ 
				at[i]=arrival_time[i];
				bt[i]=burst_time[i];
				process[i]=p[i];
				wt[i]=time-at[i];
				priority[i]=1+(wt[i]/bt[i]);
			}	
		}
		//Swapping the processes according to the priority.
		for(i=1;i<n;i++)
		{
			for(j=i+1;j<n;j++)
			{
				if(priority[i]<priority[j])
				{
					t=burst_time[i];
					burst_time[i]=burst_time[j];
					burst_time[j]=t;

					t=p[i];
					p[i]=p[j];
					p[j]=t;

					t=arrival_time[i];
					arrival_time[i]=arrival_time[j];
					arrival_time[j]=t;

					t=priority[i];
					priority[i]=priority[j];
					priority[j]=t;
				}
				else if(priority[i]==priority[j])
				{
					if(burst_time[i]>burst_time[j])
					{
						t=burst_time[i];
						burst_time[i]=burst_time[j];
						burst_time[j]=t;

						t=p[i];
						p[i]=p[j];
						p[j]=t;

						t=arrival_time[i];
						arrival_time[i]=arrival_time[j];
						arrival_time[j]=t;

						t=priority[i];
						priority[i]=priority[j];
						priority[j]=t;	
					}
				}
			}
		}

		//To claculate Completion-time.
		ct[0]=burst_time[0]+a;
		for(i=1;i<n;i++)
		{
			ct[i]=burst_time[i]+ct[i-1];
		}
		//To calculate Turn-around-time,
		for(i=0;i<n;i++)
		{
			turn_around_time[i]=ct[i]-arrival_time[i];
			tatt=tatt+turn_around_time[i];
		}
		//To calculate Waiting-time.
		for(i=0;i<n;i++)
		{
			wait_time[i]=turn_around_time[i]-burst_time[i];
			watt=watt+wait_time[i];
		}
		//Checking the condition if CPU becomes idle.
			for(i=0;i<n;i++)
			{
				if(wait_time[i]<0)
				{
					w=wait_time[i];
					w=-w;
					wait_time[i]=wait_time[i]+w;
					ct[i]=ct[i]+w;
					turn_around_time[i]=turn_around_time[i]+w;
					watt=watt+wait_time[i]+w;
				}
			}

		printf("\n\n\n");

		printf(" \t\t\t-------------------------After Scheduling------------------------\n\n\n");

		printf("\tProcess\t Arrival time\t Burst time\t Waiting time\t Turn Around Time\tPriority\tCompletion Time\t");
		for(i=0;i<n;i++)
		{                                              
			printf("\n\tP%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%0.2f\t\t\t%d",p[i],arrival_time[i],burst_time[i],wait_time[i],turn_around_time[i],priority[i],ct[i]);
		} 
		printf("\n\t---------------------------------------------------------------------------------------------------------------");

		//Calculates Avg. Waiting-time and Avg. Turnaround-time
	    float cc=n;
	    float aa;
		aa=tatt/cc;
	    float bb;
		bb=watt/cc;
	    printf("\n\n\tAverage Waiting time = %0.2f",bb);
	    printf("\n\tAverage Turn Around time = %0.2f",aa);         
		return 0;
	}
	else
	printf("Invalid Input\nPlease try again...");
	goto x;
}
