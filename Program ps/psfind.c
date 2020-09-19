/***********************************************************************
* FILENAME :       psfind.c             
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

#include "psfind.h"

flags *parseArgument(int argc, char *argv[])
{
  // variables for option and PID number
  int opt = 0, i = 0;
  flags *f = malloc(sizeof(flags));
  if (f == NULL)
  {
    fprintf(stderr, "unavailable to allocate memory for flags\n");
    exit(EXIT_FAILURE);
  }

  /*
  declaring flags
  */
  int pidflag = 0, stateflag = 0, stimeflag = 0, vmemflag = 0; // flags with default value False
  int utimeflag = 1, cmdflag = 1;                              // flags with default value True

  //  If there is an error in the command line, print and error and exit.  Don't try to go forward on questionable information.
  while ((opt = getopt(argc, argv, "p:S::s::U::v::c::")) != -1)
  {
    // turn off error message
    opterr = 0;
    
    //printf("received option: %c\n", opt);
    switch (opt)
    {

    case 'p':
      if (optarg != NULL)
      {
        int valid = 1, size = strlen(optarg);

        for (i = 0; i < size; i++)
        {
          if (!isdigit(optarg[i]))
          {
            valid = 0;
          }
        }

        if (valid)
        {
          f->pid = optarg;
          pidflag = 1;
        }
        else
        {
          fprintf(stderr, "error: process ID list syntax error\n");
          exit(EXIT_FAILURE);
        }
      }
      else
      {
        // print error message and exit
        fprintf(stderr, "error: list of process IDs must follow -p\n");
        exit(EXIT_FAILURE);
      }

      break;

    case 'S':

      if ((optarg != NULL) && (strcmp(optarg, "-") == 0))
      {
        stimeflag = 0;
      }
      else if (optarg != NULL)
      {
          fprintf(stderr, "error: option syntax error\n");
          exit(EXIT_FAILURE);
      }
      else
      {
        stimeflag = 1;
      }

      break;

    case 's':

      if ((optarg != NULL) && (strcmp(optarg, "-") == 0))
      {
        stateflag = 0;
      }
      else if (optarg != NULL)
      {
          fprintf(stderr, "error: option syntax error\n");
          exit(EXIT_FAILURE);
      }
      else
      {
        stateflag = 1;
      }

      break;

    case 'v':

      if ((optarg != NULL) && (strcmp(optarg, "-") == 0))
      {
        vmemflag = 0;
      }
      else if (optarg != NULL)
      {
          fprintf(stderr, "error: option syntax error\n");
          exit(EXIT_FAILURE);
      }
      else
      {
        vmemflag = 1;
      }
      break;

    case 'U':

      if ((optarg != NULL) && (strcmp(optarg, "-") == 0))
      {
        utimeflag = 0;
      }
      else if (optarg != NULL)
      {
          fprintf(stderr, "error: option syntax error\n");
          exit(EXIT_FAILURE);
      }
      else
      {
        utimeflag = 1;
      }
      break;

    case 'c':
      if ((optarg != NULL) && (strcmp(optarg, "-") == 0))
      {
        cmdflag = 0;
      }
      else if (optarg != NULL)
      {
          fprintf(stderr, "error: option syntax error\n");
          exit(EXIT_FAILURE);
      }
      else
      {
        cmdflag = 1;
      }

      break;
    /*
    case '?':
      fprintf(stderr, "error: unsupported option\n");
      exit(EXIT_FAILURE);
      break;
    */
    default:
      fprintf(stderr, "error: unsupported option\n");
      exit(EXIT_FAILURE);
      break;
    }
  }

  // for debugging, erase later
  /*
  if (pidflag)
  {
    printf("received pid num: %s\n", f->pid);
  }
  */
  // for debugging
  //printf("pidflag: %d, stateflag: %d, stimeflag: %d, vmemflag: %d, utimeflag: %d, cmdflag: %d\n", pidflag, stateflag, stimeflag, vmemflag, utimeflag, cmdflag);

  f->pidflag = pidflag;
  f->stateflag = stateflag;
  f->stimeflag = stimeflag;
  f->vmemflag = vmemflag;
  f->utimeflag = utimeflag;
  f->cmdflag = cmdflag;

  return f;
}

/*(
void openProcFile(flags *flag)
{
  
}
*/

int findDigit(int num) {
    int digit = 0;
    do
    {
        digit ++;
        num /= 10;
    } while(num != 0);
    
    return digit;
}

void scanDirectory(flags *flag){
      const char * proc = "/proc/";
      const char * status = "/status";
      
      int id = getuid();
      int digit = findDigit(id);
      /** Allocate Heap memory **/
      char * userId = calloc(sizeof(digit),sizeof(char));
      sprintf(userId, "%d", id);
      //printf("current user id: %s\n", userId);
      
      DIR * directory = opendir(proc);
      struct dirent * file;
      if (directory == NULL) 
      {
          fprintf(stderr, "error opening virtual file system directory\n");
          exit(EXIT_FAILURE);
      }
      
      while ((file = readdir(directory))) 
      {
          int is_process = -1;
          int size = strlen(file->d_name);
          for (int i = 0; i < size; i++)
          {
              if (!isdigit(file->d_name[i]))
              {
                  is_process = 0;
                  break;
              }
          }
          
          if (is_process) 
          {
              /** Allocate Heap memory **/
              char *path = calloc((sizeof(proc)+sizeof(file->d_name)+sizeof(status)), sizeof(char));
              sprintf(path, "%s%s%s", proc, file->d_name, status);
              
              //printf("%s\n", path);
              FILE * fp = fopen(path, "r");
              
              char word[255];
              char * pid;
              
              int userProcess = 0, getpid = 0;
              while ((fscanf(fp, "%s", word)) == 1) 
              {
                  
                  if(userProcess)
                  {
                      readPidandPrint(flag, pid);
                      break;
                  }
                  else if (getpid)
                  {
                      //printf("number of digits of pid: %ld\n", strlen(word));
                      pid = calloc(sizeof(strlen(word)),sizeof(char));
                      sprintf(pid, "%s", word);
                      //printf("pid: %s\n", pid);
                      getpid = 0;
                  }
                  else
                  {
                      if (strcmp(word, "Pid:") == 0)
                      {
                          getpid = 1;
                      }
                      if (strcmp(word, userId) == 0)
                      {
                          userProcess = 1;   
                      }
                  }
              }
              
              /**** FREE MEMORY ****/
              free(path);
              fclose(fp);
          }
      }
      
      if (closedir(directory) != 0) {
          fprintf(stderr, "error closing the virtual file system directory\n");
          exit(EXIT_FAILURE);
      }
      /**** FREE MEMORY ****/
      free(userId);
}


void readPidandPrint(flags *flag, char * pid) {
    const char * proc = "/proc/";
    const char * stat = "/stat";
    const char * statm ="/statm";
    const char * cmdline = "/cmdline";
    
    char state;
    char * userTime;
    char * stime;
    char * vmem;
    char * cmd;

    char * path = calloc((sizeof(proc) + sizeof(pid) + sizeof(stat)), sizeof(char));
    sprintf(path, "%s%s%s", proc, pid, stat);
    printf("PID: %s\n", pid);
    printf("%s\n", path);
    /**** OPENING STAT FILE ******/
    FILE * fp = fopen(path, "r");
    char line[255];
    int count = 0;
    while (fscanf(fp, "%s", line) == 1)
    {
        //printf("%s\n", word);
        count++;
        if (count == 3 && flag->stateflag)
        {
            state = line[0];
            printf("state: %c\n", state);
            memset(line, 0, 255);
        }
        
        if (count == 14 && flag->utimeflag)
        {
            userTime = line;
            //printf("usertime: %s\n", line);
            printf("usertime: %s\n", userTime);
            memset(line, 0, 255);
        }
                   
        if (count == 15 && flag->stimeflag)
        {
            stime = line;
            printf("stime: %s\n", stime);
            memset(line, 0, 255);
        }
    }
    
    /**** FREE MEMORY ****/
    free(path);
    /**** CLOSE FILE ****/
    fclose(fp);
    
    path = calloc((sizeof(proc) + sizeof(pid) + sizeof(statm)), sizeof(char));
    sprintf(path, "%s%s%s", proc, pid, statm);
    
    /**** OPENING STATM FILE ****/
    fp = fopen(path, "r");
    
    if (fscanf(fp, "%s", line) == 1 && flag->vmemflag)
    {
        vmem = line;
        printf("vmem: %s\n", vmem); 
        memset(line, 0, 255);
    }

    /**** CLOSE FILE ****/
    fclose(fp);
    /**** FREE MEMORY ****/
    free(path);
    
    /*** Opening CmdLine file ***/
    if(flag->cmdflag){
        path = calloc((sizeof(proc) + sizeof(pid) + sizeof(cmdline)), sizeof(char));
        sprintf(path, "%s%s%s", proc, pid, cmdline);
        /**** OPENING CMDLINE FILE ****/
        fp = fopen(path, "r");
        char word;
        int i = 0;
        while ((word = fgetc(fp)) != EOF){
            if (word !='\0'){
                line[i] = word;
                i++;
            }
        }
        printf("commandline: %s\n", line);
        memset(line, 0, 255);
    
    /**** CLOSE FILE ****/
        fclose(fp);
    
    /**** FREE MEMORY ****/
    free(path);
    }
    
    printf("****************************\n");
    printf("\n");
    
    
    
}
