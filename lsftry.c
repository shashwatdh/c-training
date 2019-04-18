#include<stdio.h>
#include<string.h>
void main()
{
   char str[10];
   char str1[10];
   gets(str);gets(str1);
   char *s,*s1;s=strlwr(str);s1=strlwr(str1);printf("\n%s",strcat(s,s1));
}
