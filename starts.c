// For a sequence S as found on input, list the precursors for that sequence.
// -*- mode: c -*-
// (c) 2015 duane a. bailey
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

char *S = 0;
int justStart = 0;
int lens = 0;
int poss = 0;
void Usage(char *pn)
{
  fprintf(stderr,"Usage: %s [-slp] sequence\n",pn);
  fprintf(stderr,"\t-l\tprint length of starting sequence.\n");
  fprintf(stderr,"\t-p\tprint an offset position of starting sequence.\n");
  fprintf(stderr,"\t-s\tjust print starting sequence.\n");
  fprintf(stderr,"For every flawless occurance of sequence on input, prints supporting sequence.\n");
  exit(1);
}

void parseArgs(int argc, char **argv)
{
  char *pn = *argv;
  char c;
  while (argv++,--argc) {
    char *arg = *argv;
    if (*arg == '-') {
      while ((c = *++arg)) {
	switch (c) {
	case 's':
	  justStart = 1;
	  break;
	case 'l':
	  lens = 1;
	  break;
	case 'p':
	  poss = 1;
	  break;
	default:
	  Usage(pn);
	  break;
	}
      }
    } else {
      if (S) Usage(pn);
      S = strdup(arg);
    }
  }
  if (!S) Usage(pn);
}


int main(int argc, char **argv)
{
  char *v,*p,*si,*pref,**prefs;
  int n,f=0,i,*l,sl,beg,j,k,palloc,np,*begs;
  parseArgs(argc,argv);
  sl = strlen(S);
  
  palloc = 10;
  prefs = (char**)malloc(palloc*sizeof(char*));
  begs = (int*)malloc(palloc*sizeof(int));
  while (readstr(readline(stdin),&v,&n)) {
    p = (char*)calloc(n+1,1);
    l = (int*)calloc(n,sizeof(int));
    for (i = 0; i < n; i++) {
      ccurl2(v,i,p+i,l+i);
      if (p[i] != v[i]) f = i+1;
    }
    np = 0;
    // find an S instance:
    for (si = strstr(v+f,S); si; si = strstr(si+1,S)) {
      // location of instance
      j = si-v;
      beg = n+1;
      for (k = 0; k < sl; k++) {
	if (l[j+k] < beg) beg = l[j+k];
      }
      pref = strndup(v+beg,j-beg);
      if (np == palloc) {
	palloc *= 2;
	prefs = (char**)realloc(prefs,palloc*sizeof(char*));
	begs = (int*)realloc(begs,palloc*sizeof(int));
      }
      if (!sinq3(prefs,begs,&np,pref,beg)) {
	free(pref);
      }
    }
    
    for (i = 0; i < np; i++) {
      if (lens) printf("%ld:",strlen(prefs[i]));
      if (poss) printf("%d:",begs[i]);
      if (justStart) {
	printf("%s",prefs[i]);
      } else {
	printf("%s %s",prefs[i],S);
      }
      putchar('\n');
      free(prefs[i]);
      prefs[i] = 0;
    }
    free(p);
  }
  return 0;
}
