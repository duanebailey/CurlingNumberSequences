// For each sequence, print the location with correct curl computation.
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

char *curls(char *s)
{
  int n = strlen(s);
  char *cprofile = (char*)calloc(1,n+1);
  int i;
  for (i = 0; i < n; i++) {
    cprofile[i] = ccurl(s,i);
  }
  return cprofile;
}

int main(int argc, char **argv)
{
  int n;
  char *v;
  parseArgs(argc,argv);
  while (readstr(readline(stdin),&v,&n)) {
    printf("%s\n",v);
    char *p = curls(v);
    int i;
    for (i = 0; p[i]; i++) {
      if (p[i] == v[i]) putchar('+');
      if (p[i] < v[i]) putchar('-');
      if (p[i] > v[i]) putchar('x');
    }
    putchar('\n');
  }
  return 0;
}
