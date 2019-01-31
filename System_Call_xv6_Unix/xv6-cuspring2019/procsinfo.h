#ifndef PROCSINFO_H
#define PROCSINFO_H

#include "types.h" /*required for datatypes int and char*/

#define PROC_NAMELEN 16 /*refer proc.h: struct proc { char name[16];}*/
#define PROCSINFO_INVALID_ARG -1 /*error code for the getprocsinfo() system call*/

/*adding a type for getprocsinfo*/
struct ProcsInfo
{
	int  pid; /*PID value*/
	char pname[PROC_NAMELEN]; /*process name*/
};

#endif /*PROCSINFO_H*/
