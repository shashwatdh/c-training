#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<dirent.h>
#include<string.h>
#include<sys/types.h>
int query(char *buf,int *ind)
{
	int i,len,start=0,count=0,out=1;
	len=strlen(buf);
	for(i=0;i<len;i++)
	{
		if(buf[i]!=' '&& buf[i]!='\t')
		{
			if(out)
			 {
			  out=0;
			  ind[count++]=i;
   			  //start=i;	
			 }
		}
		else
		{
			if(!out)
			 {
			 	out=1;
			 	buf[i]='\0';
			 }
		}
	}

	return count;
}
int main()
{
	int i,noa;
	char cwd[10000],buf[10000];
	int start[1000];
	char cmd[10];
	char op[10];
	char path[3000];
	DIR *d;
    struct dirent *dir;
    
    	 if (getcwd(cwd, sizeof(cwd)) != NULL) 
		 {
             printf("%s>", cwd);
            if( read(STDIN_FILENO,buf,10000)>0)
            {
            	noa=query(buf,start);
            	if(noa>0 && noa<=3)

            	{
            		if(noa==3)
            		{
            			if((strcmp((buf+start[0]),"ls")==0) && (strcmp((buf+start[1]),"-al")==0)  )
            			{
            				printf("hi %s",(buf+start[2]));
					char *ptr=(buf+start[2]);
					printf("hi %s",ptr);
            				d = opendir(ptr);
    						if(d)
    						{
    						  	printf("\n hi");
						    }
						else
                                                 printf("\n error");
					}
					else if(noa==2)
					{
						
					}
					else if(noa==1){}
				}
			}
         }
         else
          printf("\n Dir_error");
        /*while ((dir = readdir(d)) != NULL)
        {
           // printf("%s\n", dir->d_name);
        }
        closedir(d);*/
    }
    return(0);

}
