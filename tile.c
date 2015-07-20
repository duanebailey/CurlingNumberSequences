// Rewrite string according to string replacements in dictionary.
// (c) 2015 duane a. bailey
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

char *dictFile = 0;

void Usage(char *pn)
{
  fprintf(stderr,"Usage: %s dictFile\n",pn);
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
	break;
      }
    } else {
      dictFile = arg;
    }
  }
  if (!dictFile) Usage(pn);
}

char *strip(char *s)
{
  int l = strlen(s);
  char *left = s;
  char *right = s+l-1;
  while (isspace(*left)) left++;
  while (left <= right && isspace(*right)) right--;
  char *result = s;
  while (left <= right) *s++ = *left++;
  *s = 0;
  return result;
}

typedef struct pair {
  char *sym;
  char *str;
  int strl;
} pair;

typedef struct dict {
  int alloc, size;
  pair **entry;
} dict;

int ecmp(const void *ap, const void *bp)
{
  pair *apr = *(pair**)ap;
  char *a = apr->str;
  int al = apr->strl;
  pair *bpr = *(pair**)bp;
  char *b = bpr->str;
  int bl = bpr->strl;
  if (al != bl) return al-bl;
  return strcmp(a,b);
}

dict *readDict(char *dictFile)
{
  FILE *f = fopen(dictFile,"r");
  char *buffer;
  dict *d;
  d = (dict*)calloc(1,sizeof(dict));
  d->size = 0;
  d->alloc = 10;
  d->entry = (pair**)calloc(d->alloc,sizeof(pair*));
		   
  while ((buffer = readline(f))) {
    buffer = strdup(strip(buffer));
    if (buffer[0] == '#') continue;
    char *p = index(buffer,'=');
    if (!p) {
      fprintf(stderr,"Error in dictionary line: missing '=' in %s\n",buffer);
      continue;
    }
    *p++ = 0;
    pair *pr = (pair*)calloc(1,sizeof(pair));
    pr->sym = buffer;
    pr->str = p;
    pr->strl = strlen(p);
    if (d->size == d->alloc) {
      d->alloc *= 2;
      d->entry = (pair**)realloc(d->entry,d->alloc*sizeof(pair*));
    }
    d->entry[d->size++] = pr;
  }
  
  qsort(d->entry,d->size,sizeof(pair*),ecmp);
  return d;
}

int see(char *s, dict *d)
{
  int i;
  for (i = d->size-1; i >= 0; i--) {
    if (0 == strncmp(s,d->entry[i]->str,d->entry[i]->strl)) break;
  }
  return i;
}

int main(int argc, char **argv)
{
  char *s;
  dict *d = 0;
  parseArgs(argc,argv);
  d = readDict(dictFile);
  while ((s = readline(stdin))) {
    strip(s);
    int l = strlen(s);
    int i = 0;
    while (i < l) {
      int e = see(s+i,d);
      if (e == -1) {
	printf("%c",s[i++]);
      } else {
	printf("%s",d->entry[e]->sym);
	i += d->entry[e]->strl;
      }
    }
    putchar('\n');
  }
  return 0;
}
