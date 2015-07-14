// Compute the sequences that stem from the generalized projection technique with slope m=sqrt(6).
// (c) 2015 duane a. bailey
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "utils.h"

double b;
double m;
void Usage(char *pn)
{
  fprintf(stderr,"Usage: %s [-b offset] [-m slope]\n",pn);
  fprintf(stderr,"\t-m\tslope of the line used (currently %lf)\n",m);
  fprintf(stderr,"\t-b\tintersept of the line (currently %lf)\n",b);
  exit(1);
}

void parseArgs(int argc, char **argv)
{
  char *pn = *argv;
  while (argv++,--argc) {
    char *arg = *argv;
    if (*arg == '-') {
      switch (*++arg) {
      case 'm':
	sscanf(*++argv,"%lf",&m); argc--;
	break;
      case 'b':
	sscanf(*++argv,"%lf",&b); argc--;
	break;
      default:
	Usage(pn);
	break;
      }
    }
  }
}


int main(int argc, char **argv)
{
  int i,hwm=0;
  b = 0.0; m = 1/(sqrt(6.0)/(1+sqrt(6.0)));
  parseArgs(argc,argv);
  
  for (i = 0; i < 100; i++) {
    int iy= (int)(m*i+b);
    printf("%d (+%d)\n",iy,(iy-hwm));
    hwm = iy;
  }
  return 0;
}
