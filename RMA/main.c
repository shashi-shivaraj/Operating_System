/**********************************************************************
*
*  FILE NAME	: main.c
*
*  DESCRIPTION  : Implement Rate Monotonic Analysis for given set of tasks.
* 
*  PLATFORM		: Win32
*
*  DATE                 NAME                     REASON
*  16th April,2018      Shashi Shivaraju         ECE_6680_Lab_08
*                       [C88650674]
***********************************************************************/

/* Header file inclusions */
#include "header.h"

int main(int argc, char *argv[])/* main function of the program */
{
	task_data* Tasks = NULL;						/* Pointer to memory */

	double RunTime[TOTAL_TASKS] = {1.30,4.70,9.00,23.00,38.30,3.00};					/* Predefined run time of the tasks */
	double Period[TOTAL_TASKS] = {2.56,40.96,61.44,1000.00,1024.00,1280.00};			/* Predefined period time of the tasks */
	double Max_BlockingTime[TOTAL_TASKS] = {0.30,0.30,6.30,6.30,0.20,0};  /* Calculated Max Blocking Time for eacch Tasks */
	int result = 0;									/* Variable to store return value */
	int i = 0;										/* Variable used in loop */

	/* Allocate memory to initialize Tasks */
	Tasks = (task_data*)calloc(TOTAL_TASKS,sizeof(task_data));
	if(!Tasks) /* error check */
	{
		printf("memory allocation failed"); /* display error message */
		return -1; /* return error code */
	}

	/*Initialize Tasks with the predefined data*/
	for(i = 0;i<TOTAL_TASKS;i++)
	{
		Tasks[i].priority = i+1;
		Tasks[i].RunTime = RunTime[i];
		Tasks[i].Period = Period[i];
		Tasks[i].Max_BlockingTime = Max_BlockingTime[i];
	}

	/* Perform Rate Monotonic Analysis to check if system is schedulable */	
	result = RateMonotonicAnalysis(Tasks);
	if(0 == result)/*Display result of RMA*/
	{
		printf("System is schedulable !!!");
	}
	else
	{
		printf("System is NOT schedulable !!!");
	}

	/* Deallocate the Memory */
	if(Tasks)
	{
		free(Tasks);	/* free the memory */
		Tasks = NULL;
	}

	return 0; /* return success*/
}