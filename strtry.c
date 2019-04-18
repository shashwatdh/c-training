#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char a[]="asdcsdsvf";
	char b[]="sdffewfweefewfe";
	char *p=(char *)calloc(strlen(a)+strlen(b),sizeof(char));
	strcat(p,a);
	strcat(p,"/");
	strcat(p,b);
	printf("\n%s",p);
}
