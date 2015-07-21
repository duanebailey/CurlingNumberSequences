// For each sequence, print the location with correct curl computation.
// (c) 2015 duane a. bailey
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int indices = 0;
void Usage(char *pn)
{
  fprintf(stderr,"Usage: %s [-i]\n",pn);
  fprintf(stderr,"\t-i\tprint indices of flaws.\n");
  exit(1);
}

void parseArgs(int argc, char **argv)
{
  char *pn = *argv;
  while (argv++,--argc) {
    char *arg = *argv;
    if (*arg == '-') {
      switch (*++arg) {
      case 'i':
	indices = 1;
	break;
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
    printf("%s\n",v);
    char *p = curls(v);
    int i;
    for (i = 0; i < n; i++) {
      if (p[i] == v[i]) putchar('+');
      if (p[i] < v[i]) putchar('-');
      if (p[i] > v[i]) putchar('x');
    }
    putchar('\n');
    if (indices) {
      printf("Length is %d\n",n);
      for (i = 0; i<n; i++) {
	if (p[i] == v[i]) continue;
	printf("%d\n",i);
      }
    }
    free(p);
  }
  return 0;
}
