// COMMENTS
// (c) 2015 duane a. bailey
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void Usage(char *pn)
{
  fprintf(stderr,"Usage: %s\n",pn);
  exit(1);
}

void parseArgs(int argc, char **argv)
{
  char *pn = *argv;
  while (argv++,--argc) {
    char *arg = *argv;
    if (*arg == '-') {
      switch (*++arg) {
      default:
	Usage(pn);
	break;
      }
    }
  }
}

int main(int argc, char **argv)
{
  int n;
  char *v;
  parseArgs(argc,argv);
  while (readstr(readline(stdin),&v,&n)) {
  }
  return 0;
}
