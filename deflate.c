// Deflate strings to equivalent 2232->2 and 322232223->3, eliminating junk.
// (c) 2015 duane a. bailey
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
int N = 1;
int right = 1;
int flawless = 0;
int pretty = 0;
int kernel = 0;
void Usage(char *pn)
{
  fprintf(stderr,"Usage: %s [-fkp]\n",pn);
  fprintf(stderr,"\t-l\tParse using left-handed grammar (a->abaa).\n");
  fprintf(stderr,"\t-r\tParse using right-handed grammar (a->aaba).\n");
  fprintf(stderr,"\t-k\tPrint the flawless parse-able kernel sequence.\n");
  fprintf(stderr,"\t-f\tAssume string is flawless; start at left in parse.\n");
  fprintf(stderr,"\t-p\tPrint pretty.\n");
  exit(1);
}

void parseArgs(int argc, char **argv)
{
  char *pn = *argv;
  while (argv++,--argc) {
    char *arg = *argv;
    if (*arg == '-') {
      switch (*++arg) {
      case 'f':
	flawless = 1;
	break;
      case 'p':
	pretty = 1;
	break;
      case 'k':
	kernel = 1;
	break;
      case 'r':
	right = 1;
	break;
      case 'l':
	right = 0;
	break;
      default:
	Usage(pn);
      }
    }
  }
}

int begins(char *s,char *prefix)
// return true if 's' has 'prefix' as prefix
{
  int l = strlen(prefix);
  return 0 == strncmp(s,prefix,l);
}

char *parse(char *left, char *align)
// parse string starting at left, with 'align' pointing to key point
{
  char *p,*q;
  char *result = malloc(strlen(left)+1);
  char *rp = result;
  int done;
  if (!flawless) {
    // 323 indicates one side of 'b' expansion; 3223 the other
    // p will point to last character of an expansion
    if (begins(align,"323")) p = align+right; // points to end of right 'a' or end of left 'b'
    else if (begins(align,"3223")) p = align+2*!right;
    else {
      fprintf(stderr,"Parsing misaligned.");
      return 0;
    }
    // first, move left, based on the current alignment character
    done = 0;
    while (!done) {
      // *p is 2 or 3.  Check if the pointer can be validly moved back.
      if (*p == '2') {
	q = p+1-4;
	if (q >= left && ((right ? begins(q,"2232") : begins(q,"2322")))) {
	  p = q-1;
	} else done = 1;
      } else if (*p == '3') {
	q = p+1-9;
	if (q >= left && begins(q,"322232223")) {
	  p = q-1;
	} else done = 1;
      } else { done = 1; continue; }
    }
    p++;
  } else {
    p = left;
  }
  if (pretty) {
    while (left < p) {
      *rp++ = '-';
      left++;
    }
  }
  // now print out parse, heading right
  done = 0;
  while (!done) {
    if (*p == '2' && (right ? begins(p,"2232") : begins(p,"2322"))) {
      if (pretty) {
	strcpy(rp,"<22>");
	rp += 4;
      } else if (kernel) {
	strncpy(rp,p,9);
	rp += 4;
      } else {
	*rp++ = '2';
      }
      p += 4;
    } else if (*p == '3' && begins(p,"322232223")) {
      if (pretty) {
	strcpy(rp,"<3333333>");
	rp += 9;
      } else if (kernel) {
	strncpy(rp,p,9);
	rp += 9;
      } else { 
	*rp++ = '3';
      }
      p += 9;
    } else done = 1;
  }
  if (pretty) {
    while (*p++) {*rp++ = '-';}
  }
  *rp++ = 0;
  return result;
}



int main(int argc, char **argv)
{
  int n,l,flaw;
  char *v,*v2,*AB,*BA,*c,*begin;
  parseArgs(argc,argv);
  while (readstr(readline(stdin),&v,&n)) {
    int i;
    v = strdup(v);
    l = strlen(v);
    if (pretty) puts(v);
    if (!flawless) {
      // first: find the valid curl locations; we'll search for the leftmost seed there.
      c = curls(v);
      flaw = -1;
      for (i = 0; i < l; i++) {
	if (v[i] != c[i]) flaw = i;
      }
      // flaw is the location of the rightmost flaw
      // we begin searching for 323 or 3223 as parsing location.
      begin = v+(flaw+1);
      AB = strstr(begin,"323");
      if (AB) {
	v2 = parse(v,AB);
      } else {
	BA = strstr(begin,"3223");
	if (BA) {
	  v2 = parse(v,BA);
	} else {
	  printf("No starting location found.\n");
	  continue;
	}
      }
    } else {
      v2 = parse(v,v);
    }
    puts(v2);
  }
  return 0;
}
