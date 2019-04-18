#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<dirent.h>
#include<string.h>
#include<stdlib.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#include<limits.h>
struct fname
{
	char name[PATH_MAX];
	struct stat *ptr;
};
struct node
{
   char *path;
   struct node *nxt;
};

struct node *head=NULL,*tmp,*start,*rear,*t;
int first=1;

void ls(char *);
char * procD(char *date)
{
	int i,len,nc=0;
	len=strlen(date);
	for(i=0;i<len;i++)
	{
		if(date[i]==':' && ++nc==2)
		{
			date[i]='\0';
			break;
		}
	}
	return date;
}
void display(int i,struct fname *f)
{
	struct passwd *user;
    struct group  *gr;
    char *fname=f[i].name;
    int f_len=strlen(fname),j,flag=0;
	for(j=f_len-1;j>=0;j--)
	{
		if(fname[j]=='/')
		{
			flag=1;
			break;
		}
	}
	if(flag)
		fname=fname+j+1;
	
	if(S_ISDIR(f[i].ptr->st_mode))
	{
		printf("d");
		if(strcmp(fname,".")!=0 && strcmp(fname,"..")!=0)
		{
			tmp=(struct node*)malloc(sizeof(struct node));
			tmp->nxt=NULL;
			tmp->path=f[i].name;

			if(t->nxt!=NULL)
			{
				tmp->nxt=t->nxt;
				t->nxt=tmp;
            	t=t->nxt;
			}
			else
			{
				t->nxt=tmp;
				t=t->nxt;
			 	rear=t;
			}	
		}
		
	}	
	else if(S_ISLNK(f[i].ptr->st_mode)) 
		printf("l");
	else
		printf("-");
    printf( (f[i].ptr->st_mode & S_IRUSR) ? "r" : "-");
    printf( (f[i].ptr->st_mode & S_IWUSR) ? "w" : "-");
    printf( (f[i].ptr->st_mode & S_IXUSR) ? "x" : "-");
    printf( (f[i].ptr->st_mode & S_IRGRP) ? "r" : "-");
    printf( (f[i].ptr->st_mode & S_IWGRP) ? "w" : "-");
    printf( (f[i].ptr->st_mode & S_IXGRP) ? "x" : "-");
    printf( (f[i].ptr->st_mode & S_IROTH) ? "r" : "-");
    printf( (f[i].ptr->st_mode & S_IWOTH) ? "w" : "-");
    printf( (f[i].ptr->st_mode & S_IXOTH) ? "x" : "-");
    printf( (f[i].ptr->st_mode & S_ISVTX) ? "t" : "-");
    printf(" %3u",f[i].ptr->st_nlink);
    user=getpwuid(f[i].ptr->st_uid);
    gr=getgrgid(f[i].ptr->st_gid);
    printf(" %15s",user->pw_name);
    printf(" %15s",gr->gr_name);
    printf(" %10ld",f[i].ptr->st_size);//file size;
    //strftime(date, 20, "%a %b %e %H:%M", localtime(&(f[i].ptr->st_ctime)));
    //date=ctime(&f[i].ptr->st_mtime);
    
    printf("   %20s",procD(ctime(&f[i].ptr->st_mtime)));//f[i].ptr->st_mtime);
  	printf(" %10s\n",f[i].name);
}

void main(int argc,char *argv[])
{
   if(argc==2)
   {
     tmp=(struct node*)malloc(sizeof(struct node));
     tmp->nxt=NULL;
     tmp->path=argv[1];
     head=start=rear=t=tmp;
     while(start!=NULL)
     {
     	printf("\n%s\n",start->path);
     	ls(start->path);
     	start=start->nxt;
     	free(head);
     	head=t=start;
     }	
   }
   else
   	printf("\n invalid argument");
}
void ls(char *arg)
{
	int maxfiles=1000,pos;char *c;
    DIR *dr;
    struct dirent *dir;
    struct stat *fptr=(struct stat *)calloc(maxfiles,sizeof(struct stat));
    struct fname *f=(struct fname *)calloc(maxfiles,sizeof(struct fname));
    struct fname tmp;
    struct passwd *user;
    struct group  *gr;
    int count=-1,i,j,plen;
    char *cwd,*path,*date,*name1,*name2;
    struct stat buf;
    int d_pos,dd_pos;
    dr=opendir(arg);
    if(dr)
    {
        path=(char*)calloc((strlen(arg)+2)*10,sizeof(char));
        strcat(path,arg);
        if(strlen(path)>1 || strcmp(path,"/")!=0)
        	strcat(path,"/");
        plen=strlen(path);
		while((dir=readdir(dr))!=NULL)
        {
            strcat(path,dir->d_name);
            //printf("\npath:%s",path);
                  //printf("\n%s",dir->d_name);
            if(++count>=maxfiles)
            {
                printf("\n memory allocation\n");
                maxfiles+=100;
                fptr=(struct stat *)realloc(fptr,maxfiles*sizeof(struct stat));
                f=(struct fname *)realloc(f,maxfiles*sizeof(struct fname));
                
			}
			
			strcpy(f[count].name,path);
			//printf("\npath:%s",f[count].name);
			if(strcmp(dir->d_name,".")==0)
			    d_pos=count;
			else if(strcmp(dir->d_name,"..")==0)
				dd_pos=count;    
			f[count].ptr=(fptr+count);
			if(lstat(path,&buf)!=-1)
			{   
				fptr[count].st_atime=buf.st_atime;
				fptr[count].st_ctime=buf.st_ctime;
				fptr[count].st_dev=buf.st_dev;
				fptr[count].st_gid=buf.st_gid;
				fptr[count].st_ino=buf.st_ino;
				fptr[count].st_mode=buf.st_mode;
				fptr[count].st_mtime=buf.st_mtime;
				fptr[count].st_rdev=buf.st_rdev;
				fptr[count].st_nlink=buf.st_nlink;
				fptr[count].st_size=buf.st_size;
				fptr[count].st_uid=buf.st_uid;
			}  
			else
            {
                printf("\n path doesn't exists");
                break;
            }
			path[plen]='\0';
        }
        /*printf("\n list:\n");
        for(i=0;i<=count;i++)
        {
  	    	printf("\n%s-%ld",f[i].name,fptr[i].st_size);
    	}*/
    	printf("\n after sorting..\n");
    	for(i=0;i<count;i++)
    	{
  	   		if(i==d_pos||i==dd_pos)
  	   		continue;
  	  		//name1=strlwr(f[i].name);
  	   		for(j=i+1;j<=count;j++)
  	   		{
  		    	if(j==d_pos||j==dd_pos)
  	      		continue;
  	      		//name2=strlwr(f[j].name);
  		    	if(strcmp(f[i].name,f[j].name)>0)
  		    	{
  			     	strcpy(tmp.name,f[i].name);
  			     	tmp.ptr=f[i].ptr;
  			     	strcpy(f[i].name,f[j].name);
  			     	f[i].ptr=f[j].ptr;
  			     	strcpy(f[j].name,tmp.name);
  			     	f[j].ptr=tmp.ptr;
		      	}
	     	}
    	}
    	display(d_pos,f);
    	display(dd_pos,f);
    	for(i=0;i<=count;i++)
    	{
  	   		if(i==d_pos || i==dd_pos)
  	   		continue;
  	   		display(i,f);
    	}     
    }
    else
    {
    	printf("\n error opening directory");
    }	
}