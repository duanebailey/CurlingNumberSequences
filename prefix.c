// Determine all the prefixes of a patch.
// (c) 2015 duane a. bailey
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
int prefixlen = 10;
int allstrings = 0;
char *patch = "hello world";
void Usage(char *pn)
{
  fprintf(stderr,"Usage: %s [-a] [-n count] patch\n",pn);
  fprintf(stderr,"\tpatch\ta word [currently %s].\n",patch);
  fprintf(stderr,"\t-a\tcompute over all strings on input.\n");
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
      case 'a':
	allstrings = 1;
	break;
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

int sinq(char **a, int *np, char *s)
{
  int n = *np;
  int ins = n,i; // ideal insertion point
  while (ins > 0) {
    int diff = strcmp(s,a[ins-1]);
    if (diff == 0) { return 0; } // not unique; no new entry
    if (diff < 0) { // string is less; change insertion
      ins--;
    } else { // string is bigger; insert at ins
      break;
    }
  }
  for (i = n; i > ins; i--) {
    a[i] = a[i-1];
  }
  a[ins] = s;
  *np = n+1;
  return 1;
}

int main(int argc, char **argv)
{
  int n,done,salloc,i,ns;
  char *v,*next,*prefix,*vp,**strings;
  parseArgs(argc,argv);
  salloc = 10;
  strings = (char**)malloc(salloc*sizeof(char*));
  ns = 0;
  while (readstr(readline(stdin),&v,&n)) {
    vp = v+prefixlen;
    done = 0;
    while (!done) {
      next = strstr(vp,patch);
      if (next == 0) {
	done = 1;
	break;
      }
      prefix = strndup(next-prefixlen,prefixlen);
      if (ns == salloc) {
	salloc *= 2;
	strings = (char**)realloc(strings,salloc*sizeof(char*));
      }
      if (!sinq(strings,&ns,prefix)) {
	free(prefix);
      }
      vp = next + 1;
    }
    if (!allstrings) {
      for (i = 0; i < ns; i++) {
	printf("%s %s\n",strings[i],patch);
	free(strings[i]);
      }
      ns = 0;
    }
  }
  if (allstrings) {
    for (i = 0; i < ns; i++) {
      printf("%s %s\n",strings[i],patch);
      free(strings[i]);
    }
  }
  free(strings);
  return 0;
}

