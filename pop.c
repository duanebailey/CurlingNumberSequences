// Compute statistics about input lines
// (c) 2015 duane a. bailey
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int tail = 1;
int seed = 1;
int canonical = 0;
int neut = 0;
int length = 0;

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
  int n,i;
  char *v;
  int hist[10];
  parseArgs(argc,argv);
  while (readstr(readline(stdin),&v,&n)) {
    for (i = 0; i < 10; i++) hist[i] = 0;
    printf("String %s:\n",v);
    printf(" length %d\n",n);
    while (*v) {
      hist[(*v++)-'0']++;
    }
    for (i = 0; i < 10; i++) {
      if (hist[i]) {
	printf(" '%d': count=%d (%.2f%%)\n",i,hist[i],100.0*hist[i]/n);
      }
    }
  }
  return 0;
}
