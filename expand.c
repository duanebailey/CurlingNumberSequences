// Expand strings with 2->2232 and 3->322232223.
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
    int i;
    for (i = 0; i < n; i++) {
      if (v[i] == '2') printf("2232");
      else if (v[i] == '3') printf("322232223");
      else {
	putchar('x');
      }
    }
    putchar('\n');
  }
  return 0;
}
