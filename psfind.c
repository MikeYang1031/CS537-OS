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
  int opt = 0;
  int i = 0;
  flags *f = malloc(sizeof(flags));
  if (f == NULL)
  {

    // erase this print line later
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
    // for debugging, TODO: erase this later
    printf("received option: %c\n", opt);
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
          fprintf(stderr, "ERROR: invalid input at PID number: %s\n", optarg);
          exit(EXIT_FAILURE);
        }
      }
      else
      {
        // print error message and exit
        fprintf(stderr, "ERROR: No PID number provided\n");
        exit(EXIT_FAILURE);
      }

      break;

    case 'S':

      if ((optarg != NULL) && (strcmp(optarg, "-") == 0))
      {
        stimeflag = 0;
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
      else
      {
        cmdflag = 1;
      }

      break;

    case '?':
      fprintf(stderr, "invalid input detected\n");
      exit(EXIT_FAILURE);
      break;

    default:
      fprintf(stderr, "invalid input detected\n");
      exit(EXIT_FAILURE);
      break;
    }
  }

  // for debugging, erase later
  if (pidflag)
  {
    printf("received pid num: %s\n", f->pid);
  }

  // for debugging
  printf("pidflag: %d, stateflag: %d, stimeflag: %d, vmemflag: %d, utimeflag: %d, cmdflag: %d\n", pidflag, stateflag, stimeflag, vmemflag, utimeflag, cmdflag);

  f->pidflag = pidflag;
  f->stateflag = stateflag;
  f->stimeflag = stimeflag;
  f->vmemflag = vmemflag;
  f->utimeflag = utimeflag;
  f->cmdflag = cmdflag;

  return f;
}

const char *openProcFile(int pid, int pidflag)
{

  return "hello";
}
