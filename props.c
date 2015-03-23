#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int p2(int *v, int n)
{
  return n>0 && v[0] == 2;
}

int p3(int *v, int n)
{
  int i;
  if (n < 2) return 1;
  for (i = 1; i < n; i++) {
    if (v[i-1] == 3 && v[i] == 3) return 0;
  }
  return 1;
}

int p4(int *v, int n)
{
  int m, l, y, k, p;
  for (m = 4; m <= n; m++) {
    for (l = 1; l <= m/4; l++) {
      y = m-l;
      k = 1;
      for (p = y-l; p >= 0 && k < 4; p -= l) {
	if (ncmp(v+p,v+y,l)) break;
	k++;
      }
      if (k >=4) return 0;
    }
  }
  return 1;
}

int main()
{
  int *v; 
  int n,i;
  while (readints(readline(stdin),&v,&n)) {
    if (!(p2(v,n) && p3(v,n) && p4(v,n))) continue;
    for (i = 0; i < n; i++) { printf("%d ",v[i]); }
    putchar('\n');
  }
  return 0;
}
