/*header file inclusion*/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "fs.h"

/*macro declarartions*/
/*from stat.h*/
#define T_DIR  1   // Directory
#define T_FILE 2   // File
#define T_DEV  3   // Device


