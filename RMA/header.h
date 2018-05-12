/**********************************************************************
*
*  FILE NAME	: header.h
*
*  DESCRIPTION  : Header file
* 
*  PLATFORM		: Win32
*
*  DATE                 NAME                     REASON
*  16th April,2018      Shashi Shivaraju         ECE_6680_Lab_08
*                       [C88650674]
***********************************************************************/

/*Header file inclusions*/ 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*Macro definations*/
#define SYSTEM_OVERHEAD	0.153 /*153 micro-seconds*/
#define TOTAL_TASKS		6 

/*Structures definations*/
typedef struct __task
{
	int	  priority;
	double RunTime;
	double Period;
	//float TableUsageTime;
	//float IOUsageTime;
	double Max_BlockingTime;
}task_data;


/* Function Prototypes */
int RateMonotonicAnalysis(task_data* Tasks);