/*
 * A program to experiment with tails.
 * A shell, of sorts.
 * (c) 2015 duane a. bailey
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "utils.h"

char *ruler = "0----+----1----+----2----+----3----+----4----+----5----+----6----+----7...";
char *progName = "a.out";
char *tail = "1";

void Usage(char *prog)
{
  fprintf(stderr,"Usage: %s\n",prog);
  exit(1);
}

void parseArgs(int argc, char**argv)
{
  progName = *argv;
  while (++argv,--argc) {
    char *arg = *argv;
    if (*arg == '-') {
      while (*++arg) {
	switch (*arg) {
	default:
	  fprintf(stderr,"Didn't parse switch %c.\n",*arg);
	  Usage(progName);
	}
      }
    } else {
      tail = strdup(arg);
    }
  }
}

int rightmostFlaw(char *s)
{
  int l = strlen(s);
  for (l--; l >= 0; l--) {
    if (ccurl(s,l) != s[l]) {
      return l;
    }
  }
  return -1;
}

char *nCat(int k, char *Y)
{
  char *Yk = strdup(Y);
  int i;
  for (i=1; i < k; i++) {
    char *t = catenate(Yk,Y);
    free(Yk);
    Yk = t;
  }
  return Yk;
}

int isSuffix(char *lng, char *shrt)
{
  int l = strlen(lng);
  int s = strlen(shrt);
  return !strcmp(lng+(l-s),shrt);
}

char *fixPrefix(char *s, int p)
{
  char *head = strndup(s,p);
  char *result = 0;
  char *Y;
  int k = s[p]-'0';
  int l;
  for (l = (p+1)/k; l <= p; l++) {
    char *base = strdup(head+p-l);
    Y = nCat(k,base);
    free(base);
    if (isSuffix(Y,head)) {
      int j = strlen(Y);
      result = strndup(Y,j-p);
      free(Y);
      break;
    }
    free(Y);
  }
  return result;
}

int main(int argc, char **argv)
{
  int i, l;
  parseArgs(argc,argv);
  char *e = ccurlext(tail);
  puts(ruler);
  puts(e);
  l = strlen(e);
  for (i = 0; i < l; i++) {
    char c = ccurl(e,i);
    if (c == e[i]) {
      putchar('-');
    } else {
      putchar('x');
    }
  }
  putchar('\n');
  int fi = rightmostFlaw(e);
  printf("rightmost flaw @ %d\n",fi);
  printf("fix is: %s\n",fixPrefix(e,fi));
  return 0;
}
