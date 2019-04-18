#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<dirent.h>
#define MAX 100
void main(int argc,char *argv[])
{
	char buf[MAX];
	struct stat finf,finf1;
	FILE *fp,*fp1;
	if(argc==3)
	  {
	  	if(lstat(argv[1],&finf)!=-1)
	  	{
	  		if(S_ISREG(finf.st_mode))
	  		{
	  				if(lstat(argv[2],&finf1)!=-1)
	  				{		
	  					if(S_ISREG(finf1.st_mode))
	  					{
	  			            fp=fopen(argv[1],"r");
	  			            fp1=fopen(argv[2],"w");
	  			            while(!feof(fp))
	  			            {
	  			           	    if(fread(buf,sizeof(char),MAX,fp)<MAX &&(!feof(fp)))
	  			           	    {
	  			           	  	    printf("\n error reading the file!");
	  			           	  	    break;
							    }
							    if(fwrite(buf,sizeof(char),MAX,fp1)<MAX)
							    {
							  	    printf("\n error writing the file!");
	  			           	  	    break;
							    }
							}
							printf("\n finished rw");
							fclose(fp);
	                        fclose(fp1);
			  			}
			  			else
			  			{
			  				printf("\nonly regular can be copied!'");
			  			}
		  			}	
			  }
			  else
			  {
			  	printf("\nonly regular files can be copied!'");
			  }
		  }
	  }
	  else
	    printf("\n invalid command");
	    
}
