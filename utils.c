// Compute the curling number -- the largest k for array pattern == XY^k.
// (c) 2014,2015 duane a. bailey
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define CHUNK BUFSIZ
#include "utils.h"

char M[MAX][MAX];

int ncmp(int *ap, int *bp, int n)
// compare two n entry arrays of integers
{
  int i,diff;
  for (diff = i = 0; i < n; i++) { if ((diff = ap[i]-bp[i])) return diff; }
  return diff;
}

char ccurl(char *s, int n)
{
  int l;
  int maxk = 1;
  int k;
  char *p;
  char *m;
  for (l = 1; l <= n; l++) {
    k = 1;
    m = s+(n-l);
    for (p = m-l; p >= s; p-=l) {
      if (strncmp(p,m,l)) break;
      k++;
    }
    if (k > maxk) maxk = k;
  }
  return maxk+'0';
}

int ccurlen(char *s, int n)
{
  int l;
  int maxk = 1;
  int reach = 0;
  int k;
  char *p;
  char *m;
  for (l = 1; l <= n; l++) {
    k = 1;
    m = s+(n-l);
    for (p = m-l; p >= s; p-=l) {
      if (strncmp(p,m,l)) break;
      k++;
    }
    if (k > maxk) { maxk = k; reach = l; }
  }
  return reach;
}

char *ccurlext(char *s)
{
  int n = strlen(s);
  int a = 5*n; // upper bound on length?
  char v;
  char *result = (char*)malloc(a+1);
  strcpy(result,s);
  do {
    v = ccurl(result,n);
    if (n == a) {
      a *= 2;
      result = (char*)realloc(result,a+1);
    }
    result[n++] = v;
    result[n] = '\0';
  } while (v != '1');
  return realloc(result,strlen(result)+1);
}

static char compS(int n, char *S, int *rotp)
{
  // we determine the next digit of S.
  // compute the minimum of the last r entries of row 1<= r < n.
  // the maximum value of these is S[n].
  int rotten = 0;
  if (n == 0) return '1';
  char max = '1', min;
  int r,c;
  int bound = n/2;
  max = M[1][n-1];
  for (r = 2; r <= bound; r++) {
    char *entry = &(M[r][n-r]);
    min = entry[0];
    for (c=1; min > max && c < r; c++) min = (entry[c] < min) ? entry[c] : min;
    if (min > max) {
      max = min;
      bound = n / (max-'0'+1);
    }
  }
  if (rotp) {
    if ((max == '2' || max == '3')) {
      char imax = max-'0';
      int l;
      int j;

      if ((n+1)%(imax+1) == 0){
	l = (n+1)/(imax+1);
	j = n-l;
      
	if (M[l][j] == max) {
	  rotten = S[j]-'0'; // the rottenness
	  if (imax == 2) rotten = -rotten;
	  for (j++; j < n; j++) {
	    if (M[l][j] <= max) {
	      rotten = 0;
	      break;
	    }
	  }
	}
      }
    }
    *rotp = rotten;
  }
  return max;
}

char *catenate(char *s, char *t)
{
  int l = 1+strlen(s)+strlen(t);
  char *result = (char*)malloc(l);
  strcpy(result,s);
  strcat(result,t);
  return result;
}

static void col(char *S, int c)
{
  int r=1;
  char ch=S[c];
  char *sbp = S+c;
  int cb = c;
  int rep;
  while (r <= c/2) {
    rep = M[r][--cb]+1;
    M[r++][c] = (ch == *--sbp)?rep : '1';
  }
  while (r <= c) {
    M[r++][c] = '1'+(ch == *--sbp);
  }
}

char *ccurlext2(char *s,int *rotp)
{
  int n = strlen(s);
  int a = 5*n; // upper bound on length?
  char v;
  char *result = (char*)malloc(a+1);
  int rot=0;
  strcpy(result,s);
  int c,rottenness=0;
  int rotcol = -1;
  for (c = 0; c < n; c++) {
    col(result,c);
  }
  do {
    if (n >= a) {
      a *= 2;
      result = (char*)realloc(result,a+1);
    }
    v = result[n] = compS(n,result,&rot);
    if (rot) {
      if (rottenness == 0) {
	rottenness = rot;
	rotcol = n;
      }
    }
    result[n+1] = '\0';
    if (v == '1') {
      if (rotcol == n-1) {
	rottenness = 0;
	rotcol = -1;
      }
      break;
    }
    col(result,n);
    n++;
  } while (v != '1');
  if (rotp) *rotp = rottenness;
  return realloc(result,strlen(result)+1);
}

int cneutral(char *s, int start, int n)
{
  int result = start;
  int l;
  int begin=n,maxk;
  int k;
  char *p;
  char *m;
  int x;
  for (x = start; x < n; x++) {
    maxk=1;
    for (l = 1; l <= x; l++) {
      k = 1;
      m = s+(x-l);
      for (p = m-l; p >= s; p-=l) {
	if (strncmp(p,m,l)) break;
	k++;
      }
      if (k > maxk) {
	maxk = k;
	begin = (p-s)+l;
      }
    }
    if (maxk>1 && begin < result) result = begin;
  }
  return result;
}

int curl(int a[], int n)
// compute the maximum k of an array with pattern XY^k values
{
  int l;
  int maxk = 1;
  int k;
  int p;
  int m;
  for (l = 1; l <= n; l++) {
    k = 1;
    m = n-l;
    for (p = m-l; p >= 0; p-=l) {
      if (ncmp(a+p,a+m,l)) break;
      k++;
    }
    if (k > maxk) maxk = k;
  }
  return maxk;
}

int neutral(int a[], int start, int n)
// compute the maximum k of an array with pattern XY^k values
{
  int result = start;
  int l;
  int begin=n,maxk;
  int k;
  int p;
  int m;
  int x;
  for (x = start; x < n; x++) {
    maxk=1;
    for (l = 1; l <= x; l++) {
      k = 1;
      m = x-l;
      for (p = m-l; p >= 0; p-=l) {
	if (ncmp(a+p,a+m,l)) break;
	k++;
      }
      if (k > maxk) {
	maxk = k;
	begin = p+l;
      }
    }
    if (maxk>1 && begin < result) result = begin;
  }
  return result;
}

char *buffer = 0;
int bufsiz = 0;
char *readline(FILE *f)
{
  if (!buffer) {
    bufsiz = BUFSIZ;
    buffer = (char*)malloc(bufsiz);
    if (!buffer) {
      perror("Allocation of readline buffer.");
      exit(1);
    }
  }
  char *bp = buffer;
  int c;
  for (;;) {
    c = fgetc(f);
    if (bp-buffer >= bufsiz) {
      bufsiz = (bp-buffer)*2;
      buffer = (char*)realloc(buffer,bufsiz);
      if (!buffer) {
	perror("Reallocation of readline buffer.");
	exit(1);
      }
    }
    if (c == EOF || c == '\n') {
      *bp = '\0';
      break;
    }
    *bp++ = c;
  }
  return ((c == EOF) && (bp = buffer)) ? 0 : buffer;
}

char *readline2(FILE *f)
{
  char *bp;
  int i, l;
  if (buffer == 0) {
    bufsiz = CHUNK;
    buffer = (char*)malloc(bufsiz);
    if (!buffer) {
      perror("allocation of buffer");
      return 0;
    }
  }
  bp = buffer;
  while (bp == fgets(bp,CHUNK,f)) {
    if (!bp) {
      perror("end of stream");
      exit(1);
    }
    l = strlen(bp);
    if (bp[l-1] == '\n') return buffer;
    bp += l;
    i = bp-buffer;
    if (i + CHUNK > bufsiz) {
      bufsiz += CHUNK;
      buffer = (char*)realloc(buffer,bufsiz);
      if (!buffer) {
	perror("reallocation of buffer");
	return 0;
      }
      bp = buffer+i;
    }
  }
  return 0;
}

int readints(char *line, int **bp, int *np)
{
  int a = 10;
  int n = 0;
  int *b = (int*)malloc(a*sizeof(int));
  int v;
  char *lp;
  if (line) {
  while ((lp = strsep(&line," \t"))) {
    if (1 != sscanf(lp,"%d",&v)) continue;
    if (n >= a) {
      a *= 2;
      b = (int*)realloc(b,a*sizeof(int));
    }
    b[n++] = v;
  }
  }
  *bp = b;
  *np = n;
  return n;
}

int readstr(char *line, char **bp, int *np)
// return number of digits in first number found in line
{
  if (line == 0) return 0;
  int n;
  char *b = (char*)malloc(strlen(line));
  char *in=line,*out=b;
  while (*in) {
    if (isdigit(*in)) *out++ = *in;
    in++;
  }
  *out++ = '\0';
  *bp = b;
  n = strlen(b);
  *np = n;
  return n;
}
