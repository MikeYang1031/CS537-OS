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

    int test1 = 0;
    
  //  If there is an error in the command line, print and error and exit.  Don't try to go forward on questionable information.
  while ((opt = getopt(argc, argv, "p:S::s::U::v::c::")) != -1)
  {
    // turn off error message
    opterr = 0;

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
            
         test1 = 1;
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

          test1=1;

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
        test1=1;
          
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
          test1=1;
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
          test1=1;
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
          test1=1;
      }

      break;
    case '?':
      fprintf(stderr, "error: unsupported option\n");
      exit(EXIT_FAILURE);
      break;
    default:
      fprintf(stderr, "error: unsupported option\n");
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
if (test1 == 1){
    
  f->pidflag = pidflag;
  f->stateflag = stateflag;
  f->stimeflag = stimeflag;
  f->vmemflag = vmemflag;
  f->utimeflag = utimeflag;
  f->cmdflag = cmdflag;

} else {
    fprintf(stderr, "error: unsupported option\n");
    exit(EXIT_FAILURE);
}
  return f;
}

int findDigit(int num) {
    int digit = 0;
    do
    {
        digit ++;
        num /= 10;
    } while(num != 0);
    
    return digit;
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

    /**** OPENING STAT FILE ******/
    FILE* fp;
    if (fp = fopen(path, "r")){
        printf("PID: %s\n", pid);
    }
    else {
        exit(EXIT_FAILURE);
    }
    char line[255];
    int count = 0;
    
    
    
    while (fscanf(fp, "%s", line) == 1)
    {
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

char ** scanDirectory(flags *flag){
      
      // set path variables
      const char * proc = "/proc/";
      const char * status = "/status";
      
      /** the most important variables **/
      char ** pid_list = (char**)calloc(MAX_NUM_PID, sizeof(char*));
      int list_count = 0;
      if (pid_list == NULL)
      {
          fprintf(stderr, "error: cannot allocate memory\n");
          exit(EXIT_FAILURE);
      }
    
      for (int i = 0; i < MAX_NUM_PID; i++)
      {
          pid_list[i] = (char*)calloc(MAX_PID, sizeof(char));
      }
      /**********************************/
       
      int id = getuid();
      int digit = findDigit(id);
      /** Allocate Heap memory for user ID**/
      char * userId = calloc(sizeof(digit),sizeof(char));
      
      if (userId == NULL)
      {
          fprintf(stderr, "error: cannot allocate memory\n");
          exit(EXIT_FAILURE);
      }
      sprintf(userId, "%d", id);
      
      /** open directory process **/
      DIR * directory = opendir(proc);
      struct dirent * file;
      
      // check return values
      if (directory == NULL) 
      {
          fprintf(stderr, "error opening virtual file system directory\n");
          exit(EXIT_FAILURE);
      }
      
      
      while ((file = readdir(directory))) 
      {
          // check each file name
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
          
          // if the file name is a process, open the file
          if (is_process) 
          {
              /** Allocate Heap memory **/
              char *path = calloc((sizeof(proc)+sizeof(file->d_name)+sizeof(status)), sizeof(char));
              sprintf(path, "%s%s%s", proc, file->d_name, status);
              
 
              FILE * fp = fopen(path, "r");
              
              char word[300];
              char * pid;
              int userProcess = 0, getpid = 0;
              
              while ((fscanf(fp, "%s", word)) == 1) 
              {
                  
                  if(userProcess)
                  {
                      if (digit < MAX_PID)
                      {
                          pid_list[list_count] = realloc(pid_list[list_count], digit);
                      }
                      pid_list[list_count++] = pid;
                      break;
                  }
                  else if (getpid)
                  {
                      int digit = strlen(word);
                      pid = (char*)calloc(digit,sizeof(char));
                      
                      if (pid == NULL)
                      {
                          fprintf(stderr, "error: cannot allocate memory\n");
                          exit(EXIT_FAILURE);
                      }
                      
                      sprintf(pid, "%s", word);
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
              memset(word, 0 , 300);
          }
      }

      if (closedir(directory) != 0) {
          fprintf(stderr, "error: cannot close the virtual file system directory\n");
          exit(EXIT_FAILURE);
      }
    
      /**** FREE MEMORY ****/
      free(userId);
      
      return pid_list;
}
