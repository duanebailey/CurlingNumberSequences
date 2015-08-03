// Determine all the prefixes of a patch.
// (c) 2015 duane a. bailey
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
int allstrings = 0;
int hoodwidth = 3;
void Usage(char *pn)
{
  fprintf(stderr,"Usage: %s [-a] [-h hoodsize]\n",pn);
  fprintf(stderr,"\t-a\tcompute neighborhoods over all collected inputs.\n");
  fprintf(stderr,"\t-h\tspecify the diameter of neighborhoods reported [currently %d].\n",hoodwidth);
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
      case 'h':
	hoodwidth = atoi(*++argv); argc--;
	break;
      default:
	Usage(pn);
	break;
      }
    } else {
      Usage(pn);
    }	
  }
}


int main(int argc, char **argv)
{
  int n,done,salloc,i,ns;
  char *v,*hood,*vp,**strings;
  parseArgs(argc,argv);
  salloc = 10;
  strings = (char**)malloc(salloc*sizeof(char*));
  ns = 0;
  while (readstr(readline(stdin),&v,&n)) {
    vp = v;
    done = 0;
    for (i = 0; i+hoodwidth <= n; i++) {
      hood = strndup(v+i,hoodwidth);
      if (ns == salloc) {
	salloc *= 2;
	strings = (char**)realloc(strings,salloc*sizeof(char*));
      }
      if (!sinq(strings,&ns,hood)) {
	free(hood);
      }
    }
    if (!allstrings) {
      for (i = 0; i < ns; i++) {
	printf("%s\n",strings[i]);
	free(strings[i]);
      }
      ns = 0;
    }
  }
  if (allstrings) {
    for (i = 0; i < ns; i++) {
      printf("%s\n",strings[i]);
      free(strings[i]);
    }
  }
  free(strings);
  return 0;
}

