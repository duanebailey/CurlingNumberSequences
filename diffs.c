// Compute the differences of two strings.
// (c) 2015 duane a. bailey
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

char *s1=0;
char *s2=0;
void Usage(char *pn)
{
  fprintf(stderr,"Usage: %s s1 s2\n",pn);
  exit(1);
}

void parseArgs(int argc, char **argv)
{
  char *pn = *argv;
  while (argv++,--argc) {
    char *arg = *argv;
    if (*arg == '-') {
      switch (*++arg) {
      default:
	Usage(pn);
      }
    }
    if (s1 == 0) s1=arg;
    else if (s2 == 0) s2=arg;
    else Usage(pn);
  }
  if (s2 == 0) Usage(pn);
}

int main(int argc, char **argv)
{
  char *p1, *p2;
  parseArgs(argc,argv);
  if (strcmp(s1,s2)) {
  printf(" left=%s\n",s1);
  printf("      ");
  for (p1 = s1, p2 = s2; *p1 && *p2; p1++, p2++) {
    if (*p1 != *p2) {
      putchar('|');
    } else {
      putchar(' ');
    }
  }
  while (*p1 || *p2) {
    putchar((*p1)?'^':'v');
    if (*p1) p1++;
    else if (*p2) p2++;
  }
  putchar('\n');
  printf("right=%s\n",s2);
  }
  return 0;
}
