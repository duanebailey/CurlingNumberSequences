// Expand strings with 2->2232 and 3->322232223.
// (c) 2015 duane a. bailey
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
int N = 1;
int right = 1;
void Usage(char *pn)
{
  fprintf(stderr,"Usage: %s [-r] [-n count]\n",pn);
  fprintf(stderr,"\t-n\texpand count times (currently %d).\n",N);
  fprintf(stderr,"\t-r\tright-handed expansion.\n");
  fprintf(stderr,"\t-l\tleft-handed expansion.\n");
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
	N = atoi(*++argv); argc--;
	break;
      case 'l':
	right = 0;
	break;
      case 'r':
	right = 1;
	break;
      default:
	Usage(pn);
	break;
      }
    }
  }
}

char *expand(char *s)
{
  int l = strlen(s);
  char *buffer = (char*)calloc(9*l,1);
  char *bp = buffer;
  int i;
  for (i = 0; i < l; i++) {
    if (s[i] == '2') { strcpy(bp,right?"2232":"2322"); bp += 4; }
    else if (s[i] == '3') { strcpy(bp,"322232223"); bp += 9; }
    else { strcpy(bp,"x"); bp++; }
  }
  bp = strdup(buffer);
  free(buffer);
  return bp;
}

int main(int argc, char **argv)
{
  int n;
  char *v;
  parseArgs(argc,argv);
  while (readstr(readline(stdin),&v,&n)) {
    int i;
    v = strdup(v);
    for (i = 0; i < N; i++) {
      char *s = expand(v);
      free(v);
      v = s;
    }
    puts(v);
  }
  return 0;
}
