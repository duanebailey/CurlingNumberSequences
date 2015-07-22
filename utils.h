// (c) 2014,2015 duane a. bailey
#ifndef UTILS_H
#define UTILS_H
#define MAX 500
extern char M[MAX][MAX];
extern int ncmp(int *ap, int *bp, int n);
extern char* curls(char *s);
extern int curl(int a[], int n);
extern int neutral(int a[], int start, int n);
extern char ccurl(char *a, int n);
extern void ccurl2(char *a, int n, char *result, int *startp);
extern int ccurlen(char *a, int n);
extern char *ccurlext(char *s);
extern char *ccurlext2(char *s,int *rotp);
extern char *ccurlext3(char *s,int *lp, int *np);
extern int cneutral(char *a, int start, int n);
extern char *readline(FILE *f);
extern int readints(char *line, int **bp, int *np);
extern int readstr(char *line, char **bp, int *np);
extern char *catenate(char *s, char *t);
#endif
