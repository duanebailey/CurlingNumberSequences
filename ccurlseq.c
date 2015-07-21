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
int terminal = 1;

void Usage(char *pn)
{
  fprintf(stderr,"Usage: %s [-clnst]\n",pn);
  fprintf(stderr,"\n-s\tprint number of neutral start characters\n");
  fprintf(stderr,"\n-l\tprint tail length\n");
  fprintf(stderr,"\t-s\tprint just the seed\n");
  fprintf(stderr,"\t-t\tprint just the tail\n");
  fprintf(stderr,"\t-1\tdon't print terminal 1\n");
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
      case '1':
	terminal = 0;
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
  int n,l,i;
  char c;
  char *v=0,*s;
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
    if (s[n-1] == '1' && !terminal) {
      n--;
      s[n] = 0;
    }
    for (i = 0; i < n; i++) {
      if ((i < l && seed) || ((i >= l) && tail)) {
	c = s[i];
	if (canonical && c > 4) c = '4';
     	printf("%c",c);
       } 
     }
     putchar('\n');
  }
  return 0;
}
