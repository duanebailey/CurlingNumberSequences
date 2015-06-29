// Compute the curling number -- the largest k for array pattern == XY^k.
// (c) 2014 duane a. bailey
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
int ext = 0;
int size = 0;
int rep = 0;
void Usage(char *pn)
{
  fprintf(stderr,"Usage: %s [-e]\n",pn);
  fprintf(stderr,"\t-e\tGenerate extension of strings, first.\n");
  fprintf(stderr,"\t-r\tPrint strings repeated, only.\n");
  fprintf(stderr,"\t-z\tPrint curl span sizes.\n");
  exit(1);
}

void parseArgs(int argc, char **argv)
{
  char *pn = *argv;
  while (argv++,--argc) {
    char *arg = *argv;
    if (*arg == '-') {
      switch (*++arg) {
      case 'r':
	rep = 1;
	break;
      case 'e':
	ext = 1;
	break;
      case 'z':
	size = 1;
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
    if (rep) {
      for (i = 0; i < n; i++) {
	char c = ccurl(v,i);
	if (c == v[i]) {
	  int l = ccurlen(v,i);
	  char *s;
	  if (size) printf("%3d:",l);
	  printf("%s\n",s=strndup(v+i-l,l));
	  free(s);
	}
      }
    } else {
      printf("%s\n",v);
      for (i = 0; i < n; i++) {
	char c = ccurl(v,i);
	if (c != v[i]) {
	  tab(i);
	  putchar('x');
	  putchar('\n');
	} else {
	  int l=ccurlen(v,i);
	  int j;
	  int ic = (c-'0')*l; // the curl block size (less 1)
	  tab(i-ic);
	  for (j = 0; j < ic; j++) {
	    if (j < l) putchar(v[i-ic+j]);
	    else if ((i-ic+j)==(sn-1)) putchar('|');
	    else if (j%l == 0) putchar('+');
	    else if (((j%l)+1)%5 == 0) putchar('.');
	    else putchar('-');
	  }
	  putchar(c);
	  if (size)
	    printf(":%d",ic+1);
	  putchar('\n');
	}
      }
    }
  }
  return 0;
}
