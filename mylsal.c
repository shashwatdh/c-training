#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<dirent.h>
#include<string.h>
#define MAXFILES 1000
int main(int argc, char *argv[])
{
   DIR *dr;
   struct dirent *dir;
   struct stat buf;
   struct dirent files[MAXFILES],*fptr;
   fptr=files;
   int count=0;
   char * cwd;
   printf("%s-%s-%s",argv[1],argv[2],argv[3]);
   if(argc==4)
   {
      if(strcmp(argv[1],"ls")==0 && (strcmp(argv[2],"-al")==0))
      {
         printf("\n hi-%s",argv[3]);
         dr=opendir(argv[3]);
         if(dr)
         {
            
            while((dir=readdir(dr))!=NULL)
             {
                  printf("\n%s",dir->d_name);
                  if(lstat(dir->d_name,&buf)!=-1)
			{
			printf("-%u\n",buf.st_mode);
}
else
{
  printf("qwerty0000\n");
}
                    
             }

             
         }
         else
           printf("\nerror");
      } 
   }
   else if(argc==3)
   {

   }
   else if(argc==2)
   {
 
   }
else 
 printf("pass some argument");

   return 0;
}
