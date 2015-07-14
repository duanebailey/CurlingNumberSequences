// Determine all the prefixes of a patch.
// (c) 2015 duane a. bailey
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
int prefixlen = 10;
char *patch = "hello world";
void Usage(char *pn)
{
  fprintf(stderr,"Usage: %s [-n count] patch\n",pn);
  fprintf(stderr,"\tpatch\ta word [currently %s].\n",patch);
  fprintf(stderr,"\t-n\tspecify the prefix length expected [currently %d].\n",prefixlen);
  exit(1);
}

void parseArgs(int argc, char **argv)
{
  char *pn = *argv;
  while (argv++,--argc) {
    char *arg = *argv;
    if (*arg == '-') {
      switch (*++arg) {
      case 'n':
	prefixlen = atoi(*++argv); argc--;
	break;
      default:
	Usage(pn);
	break;
      }
    } else {
      patch = arg;
    }	
  }
}

int scmp(const void *ap, const void *bp)
{
  char *as = *(char**)ap;
  char *bs = *(char**)bp;
  return strcmp(as,bs);
}

int uniq(char **a, int n)
{
  char **inp, **outp;
  int i;
  for (i = 0; i < n; i++) {
    if (strcmp(*inp,*outp)) {
      outp++;
    }
    inp++;
  }
  return outp-a;
}

int suniq(char **a, int n)
{
  qsort(a,n,sizeof(char*),scmp);
  n = uniq(a,n);
  return n;
}

int main(int argc, char **argv)
{
  int n,done,salloc,i;
  char *v,*next,*prefix,*vp,**strings;
  parseArgs(argc,argv);
  salloc = 10;
  strings = (char**)malloc(salloc*sizeof(char*));
  while (readstr(readline(stdin),&v,&n)) {
    vp = v+prefixlen;
    done = 0;
    n = 0;
    while (!done) {
      next = strstr(vp,patch);
      if (next == 0) {
	done = 1;
	break;
      }
      prefix = strndup(next-prefixlen,prefixlen);
      if (n == salloc) {
	salloc *= 2;
	strings = (char**)realloc(strings,salloc*sizeof(char*));
      }
      strings[n++] = prefix;
      vp = next + 1;
    }
    n = suniq(strings,n);
    for (i = 0; i < n; i++) {
      puts(strings[i]);
      free(strings[i]);
    }
  }
  free(strings);
  return 0;
}

