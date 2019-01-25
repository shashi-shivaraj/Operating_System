typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef uint pde_t;

/*adding a type for getprocsinfo*/
typedef struct __procinfo
{
	int  pid; /*PID value*/
	char* pname; /*process name*/
}procinfo;
