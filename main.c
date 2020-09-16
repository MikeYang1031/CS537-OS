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
  
  printf("%s ", flag -> pid);
  printf("%d ", flag -> pidflag);
  printf("%d ", flag -> stateflag);
  printf("%d ", flag -> stimeflag);
  printf("%d\n", flag -> utimeflag);
  
  
  

    
  /*
  reading part
  */

  // if there was a -p option  
  if (flag -> pidflag) {
      
      // buffers to store path and other information
      char path[255];
      char buff[255];
      
      // check if there is a process running with the given pid
      strcpy(path, "/proc/");
      strcat(path, flag -> pid);
      
      FILE * pidfile = fopen(path, "r");
      
      // exits and prints nothing if such process does not exist
      if (pidfile == NULL) {
          exit(EXIT_FAILURE);
      }
      
      fclose(pidfile);
      
      // for stat file,
      // https://stackoverflow.com/questions/39066998/what-are-the-meaning-of-values-at-proc-pid-stat

      /* 
      gather information from proc file system according to each flag
      */
      if (flag -> stateflag) {
          int spacecount = 0;
          char word;
          strcat(path, "/stat");
          FILE * statfile = fopen(path, "r");

          while ((word = fgetc(statfile)) != EOF) {
                  if (spacecount == 2) {
                      // state field is located at 3rd section
                      char state = word;
                      //printf("state: %c\n", state);
                      break;
                  }
                  else {
                      if (isspace(word)) {
                          spacecount ++;
                      }
                  }
          }

          fclose(statfile);
      }
      
      if (flag -> stimeflag || flag -> utimeflag) {
          int spacecount = 0;
          char word;  
          
      }
      
      
      if (flag -> vmemflag) {
          
          
      }
      
      
      if (flag -> cmdflag) {
          
          
      }
      
      
  }    
  else {
      DIR * directory;
      struct dirent * file;
      char * proc = "/proc/";
      directory = opendir(proc);
      
      if (directory) {
          while((file = readdir(directory))) {
              printf("%s\n", file -> d_name);
              if (strcmp(file -> d_name, flag -> pid)) {
                  //printf();
              }

          }
      }
      // write more specific error handling later
      else {
      
      }
                      
      closedir(directory);
  }
  
  
    
  free(flag);
  return 0;
}
