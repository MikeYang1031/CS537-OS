/***********************************************************************
* FILENAME :       psfind.h             
*
* DESCRIPTION :
*       A simple 537 version of the Linux ps command
*
* PUBLIC FUNCTIONS :
*       
*
*
*
* AUTHOR :    Jiwon Song  HyukJun Yang   
*
*
*
**/


#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#ifndef PS_FIND
#define PS_FIND

#define NUM_FLAGS 6


typedef struct Flags{
    int pidflag;
    char * pid;
    int stateflag; 
    int stimeflag;
    int vmemflag; 
    int utimeflag;
    int cmdflag;                              

} flags;

enum flag_list{PID, PIDNUM, STATE, STIME, VMEM, USER_T, CMDLINE};

flags * parseArgument(int argc, char * argv[]);

const char * openProcFile(int pid, int pidflag);






#endif
