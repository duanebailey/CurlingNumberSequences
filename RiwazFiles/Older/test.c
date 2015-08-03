//Find curl of a string.
//Attempt 2

#include <stdio.h>
#include <string.h>

/* find curl of str */

char* curlExt (char* str, int l);
int curl (char* str, int l);

int main()
{
	char str[BUFSIZ];
	
	while ( fgets (str, BUFSIZ, stdin)){

		int l = strlen(str);

		if (str[l-1] == '\n') {
			str[l-1] = '\0';
			l--;
		}

		fputs( curlExt (str, l), stdout );
		putchar('\n');
	}
}

char* curlExt (char* str, int l){

	while (str[l-1] != '1'){

		str[l] = curl ( str, l) + '0';
		str[++l] = '\0';
	}
	
	return str;
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
