// Compute the curling number -- the largest k for array pattern == XY^k.
// (c) 2014 duane a. bailey
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
  fprintf(stderr,"Usage: %s [-clnst]\n",pn);
  fprintf(stderr,"\n-s\tprint number of neutral start characters\n");
  fprintf(stderr,"\n-l\tprint tail length\n");
  fprintf(stderr,"\t-s\tprint just the seed\n");
  fprintf(stderr,"\t-t\tprint just the tail\n");
  fprintf(stderr,"\t-c\tprint values > 4 as 4\n");
  exit(1);
}

void parseArgs(int argc, char **argv)
{
  char *pn = *argv;
  while (argv++,--argc) {
    char *arg = *argv;
    if (*arg == '-') {
      switch (*++arg) {
      case 'c':
	canonical = 1;
	break;
      case 'l':
	length = 1;
	break;
      case 'n':
	neut = 1;
	break;
      case 't':
	tail = 1; seed = 0;
	break;
      case 's':
	seed = 1; tail = 0;
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
  int n,a,l,i;
  char val;
  char *v,*s;
  parseArgs(argc,argv);
  while (readstr(readline(stdin),&v,&n)) {
    l = n; // start length
    s = ccurlext(v);
    n = strlen(s); // extension length
    if (length) {
      printf("%d:",n-l-1);
    }
    if (neut) {
      int nt = cneutral(s,l,n);
      printf("%d:",nt);
    }
    for (i = 0; i < n; i++) {
      if ((i < l && seed) || ((i >= l) && tail)) {
     	printf("%c",s[i]<='3' || !canonical ? s[i]:'4');
       } 
     }
     putchar('\n');
  }
  return 0;
}
