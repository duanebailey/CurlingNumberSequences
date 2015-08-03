/* rotten.c
 * © 2015 Riwaz Poudyal 
 * Only print Sequences that are rotten/ not rotten (-c)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int curl (char* str, int l);

int main(int argc, char**argv)
{
  //Sequence and its 2-extension, 3-extention	
  char str[BUFSIZ], ext[BUFSIZ] ;

  while ( fgets (str, BUFSIZ, stdin)){
    
    int l = strlen(str);
    
     

    if (str[l-1] == '\n') {	  
      str[l-1] = '\0';
      l--;
    }
    

    int length = l*3+3;
    

      
    sprintf (ext, "2%s3%s3%s", str, str, str); //here

    
    if (curl(ext, length) == 2){
     
      
      sprintf (ext, "2%s3%s3%s2%s", str, str, str, str); //here
      length+=(l+1);
    
      if (curl (ext, length) == 3){
	
	sprintf (ext, "2%s3%s3%s2%s3%s", str, str, str, str, str); //here
	length+= (l+1);
	
	if (curl (ext, length) == 3){
	  fputs(str, stdout);
	  fputs(str, stdout);
	}

      }
    }
  }
	
}


int curl (char* str, int l){
  int sz, kurl = 1;

  for (sz = 1; sz <= l/2; sz++){

    char* rt = str + l - sz;
    char* lt = rt - sz;

    int k = 1;

    while (lt >= str) {

      if (strncmp(lt, rt, sz) == 0) {
	k++;
	lt -= sz;
      } else break;
    }

    if (k > kurl) kurl = k;
		
  }

  return kurl;

}
