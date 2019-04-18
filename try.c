#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<dirent.h>
#define MAX 100
void main(int argc,char *argv[])
{
   char *source,*dest,*fname;
   char f_buf[MAX];
   int s_len,i,flag=0;
   struct stat buf,buf1; 
   FILE *fp,*fp1;
   if(argc==3)
   {
     	source=argv[1];
     	dest=argv[2];
     	if(lstat(source,&buf)!=-1)
     	{
     	   if(S_ISREG(buf.st_mode))
			{
				if(lstat(dest,&buf1)!=-1)
				{
					if(S_ISDIR(buf.st_mode))
					{
						//if correct arguments are entered, fetch filename from source
						s_len=strlen(source);
						for(i=len-1;i>=0;i--)
						{
							if(source[i]='/')
							{
								flag=1;
								break;
							}
						}
						if(!flag)
							fname=source;
						else
							fname=source+i+1;
						dest=(char *)realloc(dest,(strlen(dest)+strlen(fname)+1));
						strcat(dest,"/");
						strcat(dest,fname);
						if((fp=fopen(source,"r"))!=NULL && (fp1=fopen(dest,"w"))!=NULL)
						{
							printf("\n opened both files");
							while(!feof(fp))
	  			            {
	  			           	    if(fgets(f_buf,MAX,fp)!=NULL)
	  			           	    {
	  			           	  	 	if(fputs(f_buf,fp1)==EOF)
							     	{
							  	   		printf("\n error writing the file!");
	  			           	  	   		break;
							     	}
							    }
							  
							}
							 printf("\n finished rw");
						}
						
					}
					else
					   printf("\n invalid arguments");
				}
			}
			else
			   printf("\n invalid arguments [file][folder]");	
		}
   }	
}
