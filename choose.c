// Generate combinations of 2's and 3's.
// (c) 2014 duane a. bailey
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long n;
long nv = 0;
int v[100];

void Usage(char *pn)
{
  fprintf(stderr,"Usage: %s n v0 v1 [...]\n",pn);
  exit(1);
}

void parseArgs(int argc, char **argv)
{
  char *pn = *argv;
  int argn = 0;
  while (argv++,--argc) {
    char *arg = *argv;
    if (*arg == '-') {
      Usage(pn);
    } else { 
      if (argn == 0)  {
	n = atol(arg);
      } else {
	v[nv++] = atoi(arg);
      }
      argn++;
    }
  }
}

long p(long n, long m)
{
  long result = 1;
  long i;
  for (i = 0; i < m; i++) result *= n;
  return result;
}

void printb(long n, int digs, long base)
{
  if (digs > 1) {
    printb(n/base, digs-1, base);
  }
  printf("%d",v[n%base]);
}

int main(int argc, char **argv)
{
  long i, k, max;

  parseArgs(argc,argv);
  if (n == 0) Usage(argv[0]);
  if (nv < 1) Usage(argv[0]);
  max = p(nv,n);
  for (i = 0; i < max; i++) {
    k = i;
    printb(i,n,nv);
    putchar('\n');
  }
  return 0;
}
