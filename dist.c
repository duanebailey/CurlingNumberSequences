// COMMENTS
// (c) 2015 duane a. bailey
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int aenc[] = {2,3,4,6,7,8,10,11,13};
int benc[] = {1,5,9,12};
int dec = 0x1222;

char *s1 = 0, *s2 = 0;
int show = 0;
void Usage(char *pn)
{
  fprintf(stderr,"Usage: %s\n",pn);
  exit(1);
}

void parseArgs(int argc, char **argv)
{
  char c,*pn = *argv;
  while (argv++,--argc) {
    char *arg = *argv;
    if (*arg == '-') {
      while ((c = *++arg)) {
	switch (c) {
	case 's':
	  show = 1;
	  break;
	default:
	  Usage(pn);
	  break;
	}
      }
    } else {
      if (!s1) s1 = arg;
      else if (!s2) s2 = arg;
      else Usage(pn);
    }
  }
}

char *stoi(char *s)
{
  int l = strlen(s);
  char *ia,*ip;
  if (l&1) {
    fprintf(stderr,"\"%s\" is of wrong form.  Must have even number of characters.\n",s);
    exit(1);
  }
  ip = ia = (char *)calloc(l/2+1,sizeof(char));
  while (*s) {
    char c = *s++;
    int n = *s++-'0';
    if (c == 'a' || c == 'A') {
      if (n < 0 || n > 8) {
	fprintf(stderr,"Index of A (%d) is not in range.\n",n);
	exit(1);
      }
      *ip++ = aenc[n];
    } else if (c == 'b' || c == 'B') {
      if (n < 0 || n > 3) {
	fprintf(stderr,"Index of B (%d) is not in range.\n",n);
	exit(1);
      }
      *ip++ = benc[n];
    } else {
      fprintf(stderr,"Unrecognized character (%c) in string.\n",c);
      exit(1);
    }
  }
  *ip = 0;
  return ia;
}

void inc(char *s)
{
  int l = strlen(s);
  char *sp = s+l-1;
  for (;;) {
    *sp += 1;
    if (*sp != 10 && *sp != 14) break;
    sp--;
    if (sp < s) {
      fprintf(stderr,"Ran past end of addressing.\n");
      exit(1);
    }
  }
  sp++;
  while ((sp-s) < l) {
    if ((1 << sp[-1]) & dec) {
      *sp++ = 1;
    } else {
      *sp++ = 10;
    }
  }
}

int main(int argc, char **argv)
{
  char *ia1,*ia2;
  parseArgs(argc,argv);
  ia1=stoi(s1);
  ia2=stoi(s2);
  int l;
  int l1 = strlen(ia1);
  int l2 = strlen(ia2);
  l = l1;
  if (l1 != l2) {
    fprintf(stderr,"Addresses must have same length (now %d and %d).\n",l1,l2);
    exit(1);
  }
  if (ia1[0] != ia2[0]) {
    fprintf(stderr,"Initial term in addresses must match to provide context.\n");
    exit(1);
  }
  if (strcmp(ia1,ia2) > 0) {
    char *t = ia1;
    ia1=ia2;
    ia2=t;
  }
  int d = 0;
  if (show) putchar("AB"[!!(dec & (1<<ia1[l1-1]))]);
  while (strcmp(ia1,ia2)) {
    inc(ia1);
    if (show) putchar("AB"[!!(dec & (1<<ia1[l1-1]))]);
    d++;
  }
  if (show) putchar('\n');
  printf("Distance is %d\n",d);
  return 0;
}
