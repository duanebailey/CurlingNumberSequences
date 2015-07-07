/*
 * A dynamic-programming approach to computing curl with minimum recompute.
 * (c) 2015 duane a. bailey
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <assert.h>
#include <time.h>
/*
 * We assume that our work is on arrays with N or fewer entries.
 * The zero'th row is the string, S, under consideration.
 * The M[i][j], i > 0, is the number of repeats of S[j] that occur, going
 * backwards in jumps of i.
 */
#define N 500
char *M;
char *S;

char *progName;
int nbits = 0;
char *current = 0;
long count = 0;
int done = 0;

char *s2i(char *s);
char *i2s(char *s);
char *b2i(long i);

void Usage(char *prog)
{
  fprintf(stderr,"Usage: %s [-h] [-s start-string] [-n nbits] [-S start-int] [-c count]\n",prog);
  fprintf(stderr,"\t-h\tprint this help\n");
  fprintf(stderr,"\t-n\tset number of bits to nbits\n");
  fprintf(stderr,"\t-s\tinitialize with starting string.\n");
  fprintf(stderr,"\t-S\tinitialize with starting binary value.\n");
  fprintf(stderr,"\t-c\tcount of values to check (now %ld).\n",count);
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
	case 's':
	  current = s2i(strdup(*++argv));
	  argc--;
	  break;
	case 'S':
	  current = b2i(atol(*++argv));
	  argc--;
	  break;
	case 'n':
	  nbits = atoi(*++argv);
	  argc--;
	  if (!current) {
	    int i;
	    current = (char*)calloc(1,nbits+1);
	    for (i = 0; i < nbits; i++) current[i] = '\2';
	  }
	  break;
	case 'c':
	  count = atol(*++argv);
	  argc--;
	  break;
	case 'h':
	  Usage(progName);
	default:
	  fprintf(stderr,"Didn't parse switch %c.\n",*arg);
	  Usage(progName);
	}
      }
    } else {
      if (!nbits) nbits = atoi(arg);
      else if (!current) current = b2i(atol(arg));
      else if (!count) count = atol(arg);
      else Usage(progName);
    }
  }
  if (!nbits) nbits = 8;
  if (!current) {
    int i;
    current = (char*)malloc(nbits+1);
    for (i = 0; i < nbits; i++) current[i] = '\2';
    current[nbits] = 0;
  }
  if (nbits != strlen(current)) {
    fprintf(stderr,"start string has wrong number of bits.\n");
  }
  if (!count) count = 1L<<nbits;
}

char *ltos(long n)
// convert a long to a string of '2''s and '3''s
{
  char *buffer = (char*)malloc(nbits+1); // free me!
  char *bp = buffer;
  int i;
  for (i = nbits-1; i>=0; i--) {
    *bp++ = (n & (1<<i))? '3':'2';
  }
  *bp = 0;
  return buffer;
}

// Macro to compute array addresses for use in flat vector.  expensive?
#define X(r,c) ((r)*N+(c))

char *t_alloc()
// allocate dynamic programming array
{
  char *M = (char*)malloc(N*N);
  *M = '\0';
  return M;
}

char *i2s(char *s)
// convert int string to char string
{
  char *result = s;
  while (*s) { *s += '0'; s++; }
  return result;
}

char *s2i(char *s)
// convert char string to int string
{
  char *result = s;
  while (*s) { *s -= '0'; s++; }
  return result;
}

char *b2i(long i)
// convert long to int string
{
  char *result = (char*)calloc(1,nbits+1); // note: nul terminator; expensive?
  char *rp = result;
  long m;
  for (m = 1L << (nbits-1); m; m >>= 1) {
    *rp++ = (m&i) ? 3:2;
  }
  return result;
}

void t_print(char *t, int n)
// print DP table size n x n
{
  int r, c;
  putchar('\n');
  for (r = 0; r <= n; r++) {
    if (r == 1) putchar('\n');
    for (c = 0; c < n; c++) {
      if (c < r-1) putchar(' ');
      else putchar('0'+t[X(r,c)]);
    }
    putchar('\n');
  }
}

void t_update(char *start, char *t)
// build DP table from t, keeping first start columns
{
  char *s = t;
  char *tp,*rp,*u;
  char ch;
  int c; // current column
  int max, bound, r, min;
  int curling = 0;
  c = 0;
  while (start[c] && start[c] == s[c])c++; // skip over all pre-computed cols

  while (1) {
    //t_print(t,c);
    // compute s[c] = curl(s[0..c-1]) OR start[c] (if not curling)
    // 1. Compute the curl from existing matrix, if necessary.
    if ((!curling) && start[c] == 0) curling = 1;
    if (!curling) {
      s[c] = start[c];
    } else {
      if (c == 0) s[c] = 1;
      else {
	tp = t+X(1,c-1);
	max = *tp;
	bound = c/2;
	for (r = 2; r <= bound; r++) {
	  // on this row, find the minimum repeat among r:
	  tp = t+X(r,c-1);
	  rp = t+X(r,c-r);
	  for (min = *rp++; min > max && rp <= tp; rp++)
	    min = (*rp < min) ? *rp : min;
	  if (min > max) {
	    max = min;
	    bound = c/(max+1);
	  }
	}
	s[c] = max;
      }
      s[c+1] = 0;
      if (s[c] == 1) return;
    }
    // 2. If we've not hit 1, compute the column of repeat counts
    r = 1;
    char *p = t + N + c; // p points to t[1,c]
    u = s+c; // u points back r positions in string
    ch = s[c]; // *u to be compared with ch
    while (r <= c/2) {
      u--;
      *p = (ch == *u) ? p[-r]+1 : 1;

      r++;
      p += N; // p points to next row
    }
    while (r <= c) {
      u--;
      *p = 1+(ch == *u);
      p += N;
      r++;
    }
    c++;
  }
}

int rotten(char *t, int start, char *t2)
// determine if the sequence described by the table is rotten, based on
// analysis from position start
{
  char *s = t;
  int n = strlen(s);
  int c,max,mp1,l;
  int left;
  int result = 0;
  /*
   * We're looking for rows that end with l values
   *  mnnnn...n
   * where m == n-1 and l = (c+2)/n 
   * where S[c] = m.
   *
   * We need only check to column n-2 since rottenness at this point 
   * yields a tail that is at least 2 longer.
   */
  for (c = start; c < (n-2) ; c++) {
    max = s[c];
    mp1 = max+1;
    if ((c+1)%mp1 == 0) {
      l = (c+1)/mp1;
      left = c-l;
      if (t[X(l,left)] == max) {
	/*
	 * The value that makes this rotten, here, is the array value
	 * in the left column.
	 * If the current curl is 3, it will become 4 and the tail terminates
	 * If the current curl is 2, it depends; further checking is required
	 * signaled by a negative return value.
	 */
	result = (max == 2) ? -s[left] : s[left];
	for (left++; left < c; left++) {
	  if (t[X(l,left)] < mp1) {
	    result = 0;
	    break;
	  }
	}
	if (result) break;
      }
    }
  }

  //t_print(t,strlen(t));
  if (result) {
    result = (result < 0) ? -result : result;
    char *buffer = (char*)malloc(n+2);
    // WARNING: ONSET OF HACK
    buffer[0] = result;
    strncpy(buffer+1,t,start);
    buffer[start+1] = '\0';
    // sadly, we compute the tail of the possibly sequence
    // happily, we don't do this frequently
    t_update(buffer,t2);
    free(buffer);
    if (strlen(t2)-1 < n) return result;
    else {
      char xxx[N];
      strncpy(xxx,t,start);
      xxx[start] = 0;
      i2s(xxx);
      printf("\nCounter example: %s.\n",xxx);
    }
  }
  return 0;
}

void inc(char *s)
{
  char *p = s+(nbits-1);
  while (p >= s) {
    if (*p == 2) {
      *p = 3;
      break;
    }
    *p-- = 2;
  }
}

int main(int argc, char **argv)
{
  char *t,*t2;
  int l;
  long i;
  int first = 1;
  // deal with switches
  parseArgs(argc,argv);
  // allocate two arrays. we're very careful of memory leaks because
  // everything happens zillions of times
  t = t_alloc();
  t2 = t_alloc();
  l = nbits;
  printf("[");fflush(stdout);
  for (i = 0L; i < count; i++) {
    // fill out table
    t_update(current,t);
    // check for rottenness
    if (rotten(t,l,t2)) {
      i2s(current);
      printf("%s'%s'",(first?"":","),current); fflush(stdout);
      first = 0;
      s2i(current);
    }
    inc(current);
  }
  printf("]\n");
  // AMEN.
  return 0;
}
