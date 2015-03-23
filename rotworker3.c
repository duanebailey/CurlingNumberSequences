/*
 * In this version of detection of rottenness, we attempt to re-use
 * calculations as much as possible.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
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
long start = -1, current;
long delta = 0;
int debug = 0;

void Usage(char *prog)
{
  fprintf(stderr,"Usage: %s [-hd] [bits [start [delta]]]\n",prog);
  fprintf(stderr,"\t-h\tprint this help\n");
  fprintf(stderr,"\t-d\tdebugging print\n");
  fprintf(stderr,"\tbits\tnumber of bits in representation (currently %d)\n",nbits);
  fprintf(stderr,"\tstart\tstarting pattern (currently 0x%lx)\n",start);
  fprintf(stderr,"\tdelta\tnumber of patterns to consider (currently %ld)\n",delta);
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
	case 'h':
	  Usage(progName);
	case 'd':
	  debug = 1;
	  break;
	default:
	  fprintf(stderr,"Didn't parse switch %c.\n",*arg);
	  Usage(progName);
	}
      }
    } else {
      if (!nbits) nbits = atoi(arg);
      else if (start == -1) start = atol(arg);
      else if (!delta) delta = atol(arg);
      else Usage(progName);
    }
  }
  if (!nbits) nbits = 8;
  if (start == -1) start = 0;
  if (!delta) delta = (1L<<nbits)-start;
  assert(start+delta <= (1L<<nbits));
}

char *ltos(long n)
// convert a long to a string of 2's and 3's
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

#define X(r,c) ((r)*N+(c))

char *t_alloc()
{
  char *M = (char*)malloc(N*N);
  *M = '\0';
  return M;
}

char *i2s(char *s)
{
  while (*s) { *s += '0'; s++; }
  return s;
}

char *s2i(char *s)
{
  while (*s) { *s -= '0'; s++; }
  return s;
}

void t_print(char *t, int n)
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
{
  char *s = t;
  char *tp,*rp,*u;
  char ch;
  int c,cb; // current column
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
    ch = s[c];
    u = s+c;
    for (r=1, cb = c-r; r <= c/2;cb--,r++) {
      int rep = t[X(r,cb)]+1;
      t[X(r,c)] = (ch == *--u)?rep:1;
    }
    for (; r <= c+1;r++) {
      t[X(r,c)] = 1+(ch == *--u);
    }
    c++;
  }
}

/*
 * determine if the sequence described by the table is rotten, based on
 * analysis from position start
 */
int rotten(char *t, int start, char *t2)
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
    buffer[0] = result;
    strncpy(buffer+1,t,start);
    buffer[start+1] = '\0';
    t_update(buffer,t2);
    if (strlen(t2)-1 < n) return result;
  }
  return 0;
}

int inc(char *s)
{
  int l = strlen(s);
  int p = l-1;
  while (p >= 0) {
    if (s[p] == 2) {
      s[p] = 3;
      return 1;
    }
    s[p--] = 2;
  }
  return 0;
}

int main(int argc, char **argv)
{
  char *t,*t2,*buffer;
  int l;
  parseArgs(argc,argv);
  t = t_alloc();
  t2 = t_alloc();
  buffer = ltos(0);
  l = strlen(buffer);
  s2i(buffer);
  while (1) {
    t_update(buffer,t);
    if (rotten(t,l,t2)) {
      i2s(buffer);
      puts(buffer);
      s2i(buffer);
    }
    if (!inc(buffer)) break;
  }
  return 0;
}
