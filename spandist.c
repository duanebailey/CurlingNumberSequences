// Compute the curling number -- the largest k for array pattern == XY^k.
// (c) 2014 duane a. bailey
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
int ext = 0;
int off = 0;
void Usage(char *pn)
{
  fprintf(stderr,"Usage: %s [-e]\n",pn);
  fprintf(stderr,"\t-e\tGenerate extension of strings, first.\n");
  fprintf(stderr,"\t-o\tPrint offsets of spans.\n");
  exit(1);
}

void parseArgs(int argc, char **argv)
{
  char *pn = *argv;
  while (argv++,--argc) {
    char *arg = *argv;
    if (*arg == '-') {
      switch (*++arg) {
      case 'e':
	ext = 1;
	break;
      case 'o':
	off = 1;
	break;
      default:
	Usage(pn);
	break;
      }
    }
  }
}

void tab(int i)
{
  int j;
  for (j = 0; j < i; j++) {
    putchar(' ');
  }
}
int main(int argc, char **argv)
{
  int n,i;
  char *v;
  parseArgs(argc,argv);
  while (readstr(readline(stdin),&v,&n)) {
    int sn = n;
    if (ext) {
      v = ccurlext(v);
      n = strlen(v);
    }
    printf("%s\n",v);
    for (i = 0; i < n; i++) {
      char c = ccurl(v,i);
      if (c == v[i]) {
	int l=ccurlen(v,i);
	int j;
	int ic = (c-'0')*l+1; // the curl
	if (l < 0) {
	  printf("i=%d, c=%c, l=%d, ic=%d\n",i,c,l,ic);
	}
	if (off) printf("%d:",i);
	printf("%d\n",ic);
      }
    }
  }
  return 0;
}
