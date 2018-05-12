/**********************************************************************
*
*  FILE NAME	: functions.c
*
*  DESCRIPTION  : Modular functions used to implement 
*				  Rate Monotonic Analysis.
* 
*  PLATFORM		: Win32
*
*  DATE                 NAME                     REASON
*  16th April,2018      Shashi Shivaraju         ECE_6680_Lab_08
*                       [C88650674]
***********************************************************************/

/*Header file inclusions*/
#include "header.h" 

int RateMonotonicAnalysis(task_data* Tasks)
{
	int isSchedulable = 0;				/* Flag to represent Schedulability*/
	int result = 0,limit = 0;			/* Variable to return value */
	int i = 0, l = 0,k = 0,j = 0;		/* Variables used in loop */
	double condition = 0;				/* Variable used to store (l*Tk) */
	double summation = 0;				/* Variable used to store LHS of schedulability test condition */

	for(i = 1;i <= TOTAL_TASKS ; i++) /* i = 1 .....n; n = no. of tasks*/
	{
		isSchedulable = 0; /*Initialize to 0*/
			
		for(k = 1;k <= i; k++) /* k = 1.....i */
		{
			limit = (int)floor(Tasks[i-1].Period/Tasks[k-1].Period);
			for(l = 1;l <= limit;l++) /* l = 1 .... |_(Ti/Tk)_| */
			{
				summation = 0; /* initialize to 0 */
				condition = l * Tasks[k-1].Period; /* RHS = (l*Tk) */

				for(j = 1;j < i;j++)
				{
					summation = summation + (Tasks[j-1].RunTime + SYSTEM_OVERHEAD)*(float)ceil((l*Tasks[k-1].Period)/Tasks[j-1].Period); 
				} 
		
				/*add max blocking time,runtime of the task and SYSTEM_OVERHEAD to LHS*/
				summation = summation + Tasks[i-1].Max_BlockingTime + Tasks[i-1].RunTime + SYSTEM_OVERHEAD;

				/*Schedulability Test Condition*/
				if(summation <= condition)
				{
					isSchedulable = 1;
					printf("Condition satisfied for i = %d k = %d l = %d summation = %f condition = %f\n",\
						i,k,l,summation,condition);
					break; /*increment i*/
				}
				else
				{
					isSchedulable = 0;
					printf("Condition NOT satisfied for i = %d k = %d l = %d summation = %f condition = %f\n",i,k,l,summation,condition);
					/*increment l*/
				}
			}
			break; /*increments i*/
		}
	}

	if(isSchedulable)
		return 0;
	else
		return -1;
}