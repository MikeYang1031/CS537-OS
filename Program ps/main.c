/***********************************************************************
* FILENAME :       main.c             
*
* DESCRIPTION :
*       A simple 537 version of the Linux ps command
*
*
*
* AUTHOR :    Jiwon Song  HyukJoon Yang   
*
*
*
**/

#include "psfind.h"

/*
 * Function: main
 * --------------------
 * This is the main function that receives user inputs and processes outputs
 *
 *  argc: number of arguments passed to the program
 *  argv: a pointer array that points to each argument passed to the program
 *  
 *
 *  returns: 0
 */

int main(int argc, char *argv[])
{
    
  /*
  parsing part
  */
  flags * flag = parseArgument(argc, argv);

  /*
  reading part
  */
  
  if (flag->pidflag)
  {
      readPidandPrint(flag, flag->pid);
  }
  else {
      char ** pidList = scanDirectory(flag);     
      
      for(int i = 0; i < MAX_NUM_PID; i++)
      {
      
          if(pidList[i][0] != 0)
          {
              //printf("%s\n", pidList[i]);
              readPidandPrint(flag, pidList[i]);
          }
      }
      
      
      
      for(int i = 0; i < MAX_NUM_PID; i++)   
      {
         free(pidList[i]);
      }
      free(pidList);
  }
  
    
  
  
  free(flag);
  return 0;
}
