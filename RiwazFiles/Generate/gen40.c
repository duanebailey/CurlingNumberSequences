#include <stdio.h>

int main() {

  //length of string to generate
  int n;
  long l1;
  long l2;

  scanf("%d", &n);
  scanf("%ld", &l1);
  scanf("%ld", &l2);

  //if counter<= (2^n)-1
  while (l1 < l2) {

    //String to create
    char str[BUFSIZ];
		
    int j;
		
    //jth character of str is either 2 or 3
    for(j = 0; j < n; j++){

      if((l1 & (1L<<j)) != 0 ){
	str[j] = '2';

      } else {
	str[j] = '3';
      }

    }

    str[n] = '\0';

    fputs(str, stdout);
    putchar('\n');

    l1++;
    
  }
}
