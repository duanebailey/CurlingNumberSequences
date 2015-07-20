// Compute the curling number -- the largest k for array pattern == XY^k.
// (c) 2014 duane a. bailey
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
int ext = 0;
int size = 0;
int rep = 0;
int noTab = 0;
int intrude=0;
void Usage(char *pn)
{
  fprintf(stderr,"Usage: %s [-eirnz]\n",pn);
  fprintf(stderr,"\t-e\tGenerate extension of strings, first.\n");
  fprintf(stderr,"\t-i\tPrint only spans that intrude into flawed region.\n");
  fprintf(stderr,"\t-r\tPrint strings repeated, only.\n");
  fprintf(stderr,"\t-n\tDo not tab lines into position.\n");
  fprintf(stderr,"\t-z\tPrint curl span sizes.\n");

  exit(1);
}

void parseArgs(int argc, char **argv)
{
  char *pn = *argv;
  while (argv++,--argc) {
    char *arg = *argv;
    if (*arg == '-') {
      char ch;
      while ((ch = *++arg)) {
	  switch (ch) {
	  case 'r':
	    rep = 1;
	    break;
	  case 'i':
	    intrude = 1;
	    break;
	  case 'e':
	    ext = 1;
	    break;
	  case 'n':
	    noTab = 1;
	    break;
	  case 'z':
	    size = 1;
	    break;
	  default:
	    Usage(pn);
	    break;
	  }
      }
    }
  }
}


void tab(int i)
{
  int j;
  if (noTab) return;
  for (j = 0; j < i; j++) {
    putchar(' ');
  }
}
int main(int argc, char **argv)
{
  int n,i;
  char *v;
  parseArgs(argc,argv);
  while (readstr(readline(stdin),&v,&n)) {
    int sn = n;
    int fault = -1;
    char *cls;
    if (ext) {
      v = ccurlext(v);
      n = strlen(v);
    }
    cls = curls(v);
    for (i = 0; i < n; i++) {
      if (cls[i] != v[i]) fault = i;
    }
    if (rep) {
      for (i = 0; i < n; i++) {
	if (cls[i] == v[i]) {
	  int l = ccurlen(v,i);
	  char *s;
	  printf("%s@%d\n",s=strndup(v+i-l,l),i+1);
	  free(s);
	}
      }
    } else {
      for (i = 0; i < n; i++) {
	if (intrude && i <= fault) continue;
	if (cls[i] != v[i]) {
	  tab(i);
	  putchar('x');
	  printf("@%d",i+1);
	  putchar('\n');
	} else {
	  int l=ccurlen(v,i);
	  int j;
	  int ic = (cls[i]-'0')*l; // the curl block size (less 1)
	  if (i-ic <= fault || (!intrude)) {
	    tab(i-ic);
	    for (j = 0; j < ic; j++) {
	      if (j < l) putchar(v[i-ic+j]);
	      else if ((i-ic+j)==(sn-1)) putchar('|');
	      else if (j%l == 0) putchar('+');
	      else if (((j%l)+1)%5 == 0) putchar('.');
	      else putchar('-');
	    }
	    putchar(cls[i]);
	    if (size)
	      printf(":%d",ic+1);
            if (intrude) {
	      printf("@%d:%d%s",i+1-ic,i+1,(i+1-ic ==1)?"*":"");
	    }else {
	      printf("@%d",i+1);
	    }
	    putchar('\n');
	  }
	}
      }
    }
  }
  return 0;
}
