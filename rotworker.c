#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "assert.h"

char *progName;
int nbits = 0;
long start = -1;
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
  for (i = 0; i < nbits; i++) {
    *bp++ = (n & 1)? '3':'2';
    n >>= 1;
  }
  *bp = 0;
  return buffer;
}

long rotten(long val)
{
  char *v = ltos(val);	// free me
  int n = strlen(v);
  char *ve = ccurlext(v);	// free me
  char *buffer = (char*)malloc(n+2); // free me
  int vel = strlen(ve)-n;
  strcpy(buffer,"2");
  strcat(buffer,v);
  char *ve2 = ccurlext(buffer);  // free me
  int ve2l = strlen(ve2)-(n+1);
  buffer[0] = '3';
  char *ve3 = ccurlext(buffer); // free me
  int ve3l = strlen(ve3)-(n+1);
  if (ve2l < vel || ve3l < vel) {
    if (ve2l < vel) 
      if (debug) printf("2-rotten sequence:\n starting %s:\n          %s\n         %s\n",
			v,ve, ve2);
    if (ve3l < vel)
      if (debug) printf("3-rotten sequence starting %s:\n  %s\n %s\n",
			v,ve, ve3);
  } else {
    val = -1;
  }
  free(v);
  free(ve);
  free(buffer);
  free(ve2);
  free(ve3);
  return val;
}

int main(int argc, char **argv)
{
  long current,end;
  int a = 10;
  int n = 0;
  int i;
  long *rotters = (long*)malloc(a*sizeof(long));
  parseArgs(argc,argv);
  end = start+delta;
  for (current = start; current < end; current++) {
    long v = rotten(current);
    if (v < 0) continue;
    if (n == a) {
      a *= 2;
      rotters = (long*)realloc(rotters,a*sizeof(long));
    }
    rotters[n++] = v;
  }
  printf("[");
  for (i = 0; i < n; i++) {
    if (debug) printf("(%ld,%s)",rotters[i],ltos(rotters[i]));
    else printf("%ld",rotters[i]);    
    if (i < n-1) putchar(',');
  }
  printf("]\n");
  free(rotters);
  return 0;
}
