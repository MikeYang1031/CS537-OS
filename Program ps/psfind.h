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

#define MAX_PID 7
#define MAX_NUM_PID 100

typedef struct Flags{
    int pidflag;
    char * pid;
    int stateflag; 
    int stimeflag;
    int vmemflag; 
    int utimeflag;
    int cmdflag;                              

} flags;

flags * parseArgument(int argc, char * argv[]);

char ** scanDirectory(flags *flag);

void readPidandPrint(flags *flag, char * pid);

int findDigit(int num);

