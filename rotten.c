// Echo those strings that are rotten.
// (c) 2014 duane a. bailey
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int witness = 0;
int not = 0;

void Usage(char *pn)
{
  fprintf(stderr,"Usage: %s [-wc]\n",pn);
  fprintf(stderr,"\t-w\tPrint prefix(es) that shorten sequence.\n");
  fprintf(stderr,"\t-c\tPrint non-rotten sequences.\n");
  exit(1);
}

void parseArgs(int argc, char **argv)
{
  char *pn = *argv;
  while (argv++,--argc) {
    char *arg = *argv;
    if (*arg == '-') {
      switch (*++arg) {
      case 'w':
	witness = 1;
	not = 0;
	break;
      case 'c':
	witness = 0;
	not = 1;
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
  char *v;
  int n;
  int a = 512;
  char *work = (char*)malloc(a+1);
  parseArgs(argc,argv);
  while (readstr(readline(stdin),&v,&n)) {
    char *ve = ccurlext(v);
    char *buffer = (char*)malloc(n+2);
    int vel = strlen(ve)-n;
    strcpy(buffer,"2");
    strcat(buffer,v);
    char *ve2 = ccurlext(buffer);
    int ve2l = strlen(ve2)-(n+1);
    buffer[0] = '3';
    char *ve3 = ccurlext(buffer);
    int ve3l = strlen(ve3)-(n+1);
    if (ve2l < vel || ve3l < vel) {
      if (!not) {
	if (witness) {
	  int i;
	  putchar('\n');
	  putchar(' ');
	  for (i = 0; i < vel+n; i++) {
	    if (i+1 < n) putchar('-');
	    else if (i+1 == n) putchar(']');
	    else if (ve[i] != ve2[i+1] || ve[i] != ve3[i+1]) {putchar('v');putchar('\n'); break;}
	    else putchar('-');
	  }
	  printf(" %s\n",ve);
	  if (ve2l < vel) { printf("%s\n",ve2); }
	  if (ve3l < vel) { printf("%s\n",ve3); }
	} else {
	  printf("%s\n",v);
	}
      }
    } else {
      if (not) {
	printf("%s\n",v);	
      }
    }
  }
  return 0;
}
