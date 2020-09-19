537ps
List of C library we are using:
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
Functions
typedef struct flags -> contains flag variables for each option

flags * parseArgument(int argc, char * argv[]);

void openProcFile(flags* flag);

void scanDirectory(flags *flag);

void readPidandPrint(flags *flag, char * pid);

int findDigit(int num);

TODO:
Finish writing readPidandPrint() and openProcFile()

BUGS
when executing 537ps file in UW-Madison Linux Machine, I get stack smashing error -> figuring out what is causing this error

-> found that recursive call on readPidandPrint in scanDirectory is causing stack buffer overflow, I am trying to figure out how to store all the pid numbers in an array and sent them to readPidandPrint

The maximum vale of Process ID = 32767 ref: http://linfo.org/pid.html#:~:text=This%20is%20because%20such%20numbers,exist%20simultaneously%20on%20a%20system.

when executing 537ps - l, it does not detect this.
