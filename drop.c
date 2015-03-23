// Compute the curling number -- the largest k for array pattern == XY^k.
// (c) 2014 duane a. bailey
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int n = 4;
int reverse = 0;

void Usage(char *pn)
{
  fprintf(stderr,"Usage: %s [-r] n\n",pn);
  exit(1);
}

void parseArgs(int argc, char **argv)
{
  char *pn = *argv;
  int argn = 0;
  while (argv++,--argc) {
    char *arg = *argv;
    if (!strcmp(arg,"-r")) {
      reverse = 1;
      continue;
    }
    if (argn == 0)  {
      n = atoi(arg);
    } else {
      Usage(pn);
    }
    argn++;
  }
}

int main(int argc, char **argv)
{
  int c,i, first, end;
  int *v;
  parseArgs(argc,argv);
  while (readints(readline(stdin),&v,&c)) {
    if (n >= 0) {
      first = (c < n) ? c : n;
      end = c;
    } else {
      first = 0;
      end = (c+n < 0) ? 0: c+n;
    }
    if (reverse) {
      for (i = end-1; i >= first; i--) {
	printf("%d ",v[i]);
      }
    } else {
      for (i = first; i < end; i++) {
	printf("%d ",v[i]);
      }
    }
    putchar('\n');
  }
  return 0;
}
