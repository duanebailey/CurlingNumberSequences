//
// This implementation of curl tail computation makes use of a n^2 table.
// If n is the size of the prefix of a squence S, then M(r,c),
// 1 <= r <= c <= n, identifies the number of times S[c] repeats, looking
// backwards by jumps of r.  In otherwords if S[c-r] != S[c], then M(r,c) = 1.

// S      = 2 3 2 3 2 3 2 3
// c      = 0 1 2 3 4 5 6 7
// M[1,-] = - 1 1 1 1 1 1 1
// M[2,-] = - - 2 2 3 3 4 4
// M[3,-] = - - - 1 1 1 1 1
// M[4,-] = - - - - 2 2 2 2
// M[5,-] = - - - - - 1 1 1
// M[6,-] = - - - - - - 2 2
// M[7,-] = - - - - - - - 1

/*
We can detect rottenness occurring in this matrix if the following
conditions are true:
1. the curl computed into column n (origin 0) is 2 or 3; let's call this c.
   this curl will become S[n].  [origin 0 => column n is the (n+1)st column.]
2. (n+1) is divisible by c+1.  We're looking for the generation of curl that
   might possibly be (c+1) when we ply on a new column on the left.
   Set l=(n+1)/(c+1).  This is the length of the Y we expect to use when
   the sequence is pre-pended with a value.  This is also the row number
   (the "delta", origin 1) where rottenness will be witnessed.
3. Only if the above holds, do we check to for the witness:
   a. column (n-l) of row l is c.  If so, we check
   b. columns (n-(l-1))..(n-1) of row l are all > c (in fact, they are c+1).
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "utils.h"

void printMat(int n, char *S)
{
  int r,c;
  printf("n=%d\n",n);
  printf("S=\n");
  for (c = 0; c < n; c++) {
    printf("%c",S[c]);
  }
  putchar('\n');
  printf("M=\n");
  for (r = 1; r < n; r++) {
    for (c = 0; c < n; c++) {
      if (c < r) { printf("1"); }
      else {printf("%c",M[r][c]);}
    }
    putchar('\n');
  }
}

int main(int argc, char **argv)
{
  char s[BUFSIZ];
  int rottenness = 0;
  
  if (argc == 1) {
    while (1 == scanf("%s",s)) {
      char *e = ccurlext2(s,&rottenness);
      if (rottenness) {
	if (rottenness < 0) { // the string is *possibly rotten; verify
	  char *e2;
	  char *head = (rottenness == -2) ? "2" : "3";
	  e2 = ccurlext2(catenate(head,s),0);
	  if (strlen(e2) <= strlen(e)) {
	    puts(s);
	  }
	} else {
	  puts(s);
	}
      }
    }
  } else if (strcmp(argv[1],"old")==0) {
    while (1 == scanf("%s",s)) {
      ccurlext(s);
    }
  } else if (strcmp(argv[1],"mat")==0) {
    while (1 == scanf("%s",s)) {
      char *e = ccurlext2(s,&rottenness);
      int l = strlen(e)-1;
      printMat(l,e);
    }
  } else if (strcmp(argv[1],"new")==0) {
    while (1 == scanf("%s",s)) {
      ccurlext2(s,&rottenness);
    }
  } else if (strcmp(argv[1],"check")==0) {
    while (1 == scanf("%s",s)) {
      if (strcmp(ccurlext(s),ccurlext2(s,&rottenness))) {
	printf("Fails on %s:\nold=%s\nnew=%s\n",s,ccurlext(s),ccurlext2(s,&rottenness));
      }
    }
  } else {
    while (1 == scanf("%s",s));
  }
  exit(0);
}

