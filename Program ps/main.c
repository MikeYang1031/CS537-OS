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
       
      
      strcat(path, "/stat");
      
      
      /* 
      gather information from proc file system according to each flag
      */    
      if (flag -> stateflag) {
          int spacecount = 0;
          char word;
          FILE * statfile = fopen(path, "r");
          
           while ((word = fgetc(statfile)) != EOF) {
              
                  if (spacecount == 2) {
                      // state field is located at 3rd section
                      char state = word;
                      /*
                      printf("state: %c\n", state);
                      */
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
      
      /* 
      gather utime from proc
      */
        
      if (flag -> utimeflag) {
          
         int spacecount = 0;
          char word;
          FILE * statfile = fopen(path, "r");
          
          /*
          Char array that stores the utime
          */
          char utime_read[10];
          int i = 0;
          
          while ((word = fgetc(statfile)) != EOF) {
              if (spacecount == 13) {
                  if (isspace(word)){
                      break;
                  }
                  char state = word;
                  utime_read[i] = word;
                  i++;        
              }              
              if (isspace(word)) {
                  spacecount ++;
              }
          }
          fclose(statfile);
          
          /*
          Copy the value to utime_value without empy spaces
          */
          char utime_value[i];
          int j;
          for (j = 0; j < i; j++){
              utime_value[j] = utime_read[j];
          }
          
          /*
          Execute and you will think like this. ??????????????
          Two values should be swapped but i don't know why
          */
          printf("Test for utime_read (with space): %s \n", utime_read);
          printf("Test for utime_value (with no space): %s \n", utime_value);
      }
      
       /* 
      gather stime from proc
      */
      if (flag -> stimeflag){
          int spacecount = 0;
          char word;
          FILE * statfile = fopen(path, "r");
          
          /*
          Char array that stores the stime
          */
          char stime_read[10];
          int i = 0;
          
          while ((word = fgetc(statfile)) != EOF) {
              if (spacecount == 14) {
                  if (isspace(word)){
                      break;
                  }
                  char state = word;
                  stime_read[i] = word;
                  i++;        
              }              
              if (isspace(word)) {
                  spacecount ++;
              }
          }
          fclose(statfile);
          printf("Test for stime_read: %s \n", stime_read);
      }
      
      if (flag->vmemflag)
    {
      char path[255];
      char vmem[255];
      char word;
      int i = 0;

      strcpy(path, "/proc/");
      strcat(path, flag->pid);
      strcat(path, "/statm");

      FILE *statmfile = fopen(path, "r");

      while ((word = fgetc(statmfile)) != EOF)
      {
        if (!(isspace(word)))
        {
          vmem[i] = word;
          i++;
        }
        else
        {
          break;
        }
      }
      fclose(statmfile);
      printf("Test for vmem: %s \n", vmem);
    }
      
      
      if (flag -> cmdflag) {
          char path[255];
          char cmd[500];
          char word;
          int i = 0;
          
          strcpy(path, "/proc/");
          strcat(path, flag -> pid);
          strcat(path, "/cmdline");
          
          FILE* cmdfile = fopen(path, "r");
          
          while ((word = fgetc(cmdfile)) != EOF){
              if (word != NULL){
                  cmd[i] = word;
                  i++;
              }
          }
          fclose(cmdfile);
          printf("Test for cmdline: %s \n", cmd);
          
          
          
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
