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

/*
 * compute whether or not a starting sequence, S, yields a longer tail
 * than 2S or 3S.
 * Result is the starting sequence, if rotten, or -1.
 */
long rotten(long val)
{
  char *v = ltos(val);	// free me
  int rottenness;
  char *e2,*head,*v2;
  char *e = ccurlext2(v,&rottenness);
  if (rottenness) {
    // it may be just *possibly* rotten (if rottenness < 0), which requires
    // further verification
    if (rottenness < 0) { // the string is *possibly rotten; verify
      head = (rottenness == -2) ? "2" : "3";
      v2 = catenate(head,v);
      e2 = ccurlext2(v2,0);
      //      printf("v = %s (len %ld)\ne = %s (len %ld)\ne2=%s (len %ld)\n",v,strlen(v),e,strlen(e),e2,strlen(e2));
      if ((strlen(e)+1) <= strlen(e2)) { // remember> |v|+1 = |v2|
	//	printf("(Not rotten.)\n");
	val = -1;
      }
      free(v2);
      free(e2);
    }
  } else {
    val = -1;
  }
  //  if (val != -1) printf("%s\n",v);
  free(v);
  free(e);
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
