// Compute the curling number -- the largest k for array pattern == XY^k.
// (c) 2014 duane a. bailey
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n;
int debug = 0;
int nv = 2;
int v[] = {2,3};

void Usage(char *pn)
{
  fprintf(stderr,"Usage: %s n [...]\n",pn);
  exit(1);
}

void parseArgs(int argc, char **argv)
{
  char *pn = *argv;
  int argn = 0;
  while (argv++,--argc) {
    char *arg = *argv;
    if (*arg == '-') {
      switch (*++arg) {
      case 'd':
	debug = 1;
	break;
      default:
	Usage(pn);
	break;
      }
    } else { 
      if (argn == 0)  {
	n = atoi(arg);
      } else {
	Usage(pn);
      }
      argn++;
    }
  }
}

void pb(long n,int d)
{
  int i;
  printf("0b");
  for (i = d-1; i >= 0; i--) {
    printf("%d",(n&(1L<<i))?1:0);
  }
}

void p(long n, int d)
{
  int i;
  for (i = d-1; i >= 0; i--) {
    printf("%d ",(n&(1L<<i))?3:2);
  }
}

int main(int argc, char **argv)
{
  int j,k,dig, wit;
  long max, halfmax, mask, i, ib, ibar,m1,m2,m3,m,t;

  parseArgs(argc,argv);
  if (n == 0) Usage(argv[0]);
  if (nv < 1) Usage(argv[0]);
  max = 1L<<n;
  halfmax = 1L<<(n-1); // rule 2
  mask=max-1;
  for (i = 0; i < halfmax; i++) {
    if (i & (i<<1)) continue; // rule 3: if there are duplicate 3's, skip
    if (n > 3) {
      ib = (~i) & (max-1);
      /*
       * we now check for repeats of 4:
       * by xnor-ing i with itself, shifted by 1, 2, 3, ... digits
       * we find a 1 wherever digits correspond 1, 2, 3, ... digits apart
       * we can use this fact to make several comparisons at k, 2k, 3k, 4k digits
       * apart and finding a k digit sequence
       */
      if (debug) {
	printf("\n[Considering: "); p(i,n);
	printf("]\n");
      }
      for (k = 1; k <= n/4; k++) {
	if (debug) printf("k=%d\n",k);
	ibar = ib;
	ibar >>= k;
	if (debug) {printf("i:  "); pb(i,n); putchar('\n');}
	if (debug) {printf("~i: "); pb(ib,n); putchar('\n');}
	mask = (1L<<(n-k))-1L;
	m1 = (i ^ ibar)&mask; // 1's where digits match k apart
	if (debug) {printf("m1: "); pb(m1,n); putchar('\n');}
	ibar >>= k;
	mask = (1L<<(n-2*k))-1L;
	m2 = (i ^ ibar)&mask; // 1's where digits match 2k apart
	if (debug) {printf("m2: "); pb(m2,n); putchar('\n');}
	ibar >>= k;
	mask = (1L<<(n-3*k))-1L;
	m3 = (i ^ ibar)&mask; // 1's where digits match 3k apart
	if (debug) { printf("m3: "); pb(m3,n); putchar('\n'); }
	m = m1&m2&m3;  // 1's where digits match k, 2k, and 3k apart
	if (debug) {printf("m:  "); pb(m,n); putchar('\n');}
	t = m;
	for (j = 1; j < k; j++) {
	  t &= m>>j;
	}
	if (debug) { printf("t:  "); pb(t,n); putchar('\n');}
	// if there's a 1 in t, we have a repeating sequence of k digits:
	if (t) {
	  for (j = 0; j < n; j++) {
	    if (t & (1L<<j)) wit = j;
	  } 
	  if (debug) {printf("not (k=%d,wit=%d): ",k,wit);
	    p(i,n); putchar('\n');}
	  break;
	}
      }
      if (t) continue;
    }
    p(i,n); putchar('\n');
  }
  return 0;
}
