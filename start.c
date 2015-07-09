// Compute a (possibly short) starting sequence for a binary curl string.
// (c) 2015 duane a. bailey
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int verbose = 0;

void Usage(char *pn)
{
  fprintf(stderr,"Usage: %s [-v]\n",pn);
  fprintf(stderr,"\t-v\tprint all attempts\n");
  exit(1);
}

void parseArgs(int argc, char **argv)
{
  char *pn = *argv;
  while (argv++,--argc) {
    char *arg = *argv;
    if (*arg == '-') {
      switch (*++arg) {
      case 'v':
	verbose = 1;
	break;
      default:
	Usage(pn);
	break;
      }
    }
  }
}

void inc(char *base)
{
  int sl = strlen(base);
  int l = sl-1;
  while (l >= 0) {
    if (base[l] == '2') {
      base[l] = '3';
      return;
    }
    base[l] = '2';
    l--;
  }
  base[0] = '2';
  base[sl++] = '2';
  base[sl] = 0;
}

int rightmostFlaw(char *s, char *t)
{
  int sl = strlen(s);
  int tl = strlen(t);
  int stl = sl+tl;
  char *combined = (char*)malloc(stl+1);
  strcpy(combined,s);
  strcat(combined,t);
  char *cls = curls(combined);
  int last = -1;
  int i;
  for (i = 0; i < stl; i++) {
    if (cls[i] != combined[i]) last = i;
  }
  free(combined);
  free(cls);
  return last - sl;
}

int main(int argc, char **argv)
{
  int n;
  char *v;
  char prefix[512];
  parseArgs(argc,argv);
  while (readstr(readline(stdin),&v,&n)) {
    prefix[0] = 0;
    int done = 0;
    while (!done) {
      int p = rightmostFlaw(prefix,v);
      if (p < 0 || verbose) {
	printf("flaw at %d in %s:%s\n",p,prefix,v);
	done = p<0;
      }
      if (!done) inc(prefix);
    }
  }
  return 0;
}
