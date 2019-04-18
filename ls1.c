#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<dirent.h>
#include<string.h>
#include<stdlib.h>
#include<pwd.h>
#include<grp.h>#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<dirent.h>
#include<string.h>
#include<stdlib.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
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
struct fname{
	char *name;
	struct stat *ptr;
};
int main(int argc, char *argv[])
{
	int maxfiles=1000,pos;char *c;
   DIR *dr;
   struct dirent *dir;
   struct stat *fptr=(struct stat *)calloc(maxfiles,sizeof(struct stat));
   struct fname f[maxfiles];
   struct fname tmp;
   struct passwd *user;
   struct group  *gr;
   int count=-1,i,j,plen;
   char *cwd,*path,*date;
   struct stat buf;
   
   printf("%s-%s-%s",argv[1],argv[2],argv[3]);
   if(argc==4)
   {
      if(strcmp(argv[1],"ls")==0 && (strcmp(argv[2],"-al")==0))
      {
         printf("\n hi-%s",argv[3]);
         dr=opendir(argv[3]);
         if(dr)
         {
            path=(char*)calloc((sizeof(argv[3])+2)*10,sizeof(char));
            strcat(path,argv[3]);
            if(strlen(path)>1)
            strcat(path,"/");
            plen=strlen(path);
			while((dir=readdir(dr))!=NULL)
             {
             	   strcat(path,dir->d_name);
             	   printf("\npath:%s",path);
                  //printf("\n%s",dir->d_name);
                  if(++count>=maxfiles)
                  {
                  	 printf("\n memory allocation\n");
                  	 fptr=(struct stat *)realloc(fptr,100*sizeof(struct stat));
                  	 maxfiles+=100;
					}
					    //fname[count]=dir->d_name;
					    //printf("\n--%s",c);
					    f[count].name=dir->d_name;
					   // printf(" %s\n",f[count].name);
					   
					    f[count].ptr=(fptr+count);
					if(lstat(path,&buf)!=-1)
					{   //printf("\njk");
					    //c=dir->d_name;
					    //printf("\n--%s",c);
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
                           		  {printf("\n path doesn't exists");break;}
					path[plen]='\0';
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
 
printf("\n list:\n");
  for(i=0;i<=count;i++)
  {
  	printf("\n%s-%ld",f[i].name,fptr[i].st_size);
  }
  printf("\n after sorting..\n");
  for(i=0;i<=count;i++)
  {
  	for(j=i+1;j<=count;j++)
  	{
  		if(strcmp(f[i].name,f[j].name)>0)
  		{
  			tmp.name=f[i].name;
  			tmp.ptr=f[i].ptr;
  			f[i].name=f[j].name;
  			f[i].ptr=f[j].ptr;
  			f[j].name=tmp.name;
  			f[j].ptr=tmp.ptr;
		  }
	  }
  }
  for(i=0;i<=count;i++)
  {
  	 printf( (S_ISDIR(f[i].ptr->st_mode)) ? "d" : (S_ISLNK(f[i].ptr->st_mode)) ? "l" :"-");
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
    printf(" %u",f[i].ptr->st_nlink);
    user=getpwuid(f[i].ptr->st_uid);
    gr=getgrgid(f[i].ptr->st_gid);
    printf(" %s",user->pw_name);
    printf(" %s",gr->gr_name);
    printf(" %ld",f[i].ptr->st_size);//file size;
    //strftime(date, 20, "%a %b %e %H:%M", localtime(&(f[i].ptr->st_ctime)));
    //date=ctime(&f[i].ptr->st_mtime);
    
    printf("   %s",procD(ctime(&f[i].ptr->st_mtime)));//f[i].ptr->st_mtime);
  	printf(" %s\n",f[i].name);
  }
   free(fptr);
   free(path);
   return 0;
}
#include<time.h>
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
struct fname{
	char *name;
	struct stat *ptr;
};
int main(int argc, char *argv[])
{
	int maxfiles=1000,pos;char *c;
   DIR *dr;
   struct dirent *dir;
   struct stat *fptr=(struct stat *)calloc(maxfiles,sizeof(struct stat));
   struct fname f[maxfiles];
   struct fname tmp;
   struct passwd *user;
   struct group  *gr;
   int count=-1,i,j,plen;
   char *cwd,*path,*date;
   struct stat buf;
   
   printf("%s-%s-%s",argv[1],argv[2],argv[3]);
   if(argc==4)
   {
      if(strcmp(argv[1],"ls")==0 && (strcmp(argv[2],"-al")==0))
      {
         printf("\n hi-%s",argv[3]);
         dr=opendir(argv[3]);
         if(dr)
         {
            path=(char*)calloc((sizeof(argv[3])+2)*10,sizeof(char));
            strcat(path,argv[3]);
            if(strlen(path)>1)
            strcat(path,"/");
            plen=strlen(path);
			while((dir=readdir(dr))!=NULL)
             {
             	   strcat(path,dir->d_name);
             	   printf("\npath:%s",path);
                  //printf("\n%s",dir->d_name);
                  if(++count>=maxfiles)
                  {
                  	 printf("\n memory allocation\n");
                  	 fptr=(struct stat *)realloc(fptr,100*sizeof(struct stat));
                  	 maxfiles+=100;
					}
					    //fname[count]=dir->d_name;
					    //printf("\n--%s",c);
					    f[count].name=dir->d_name;
					   // printf(" %s\n",f[count].name);
					   
					    f[count].ptr=(fptr+count);
					if(lstat(path,&buf)!=-1)
					{   //printf("\njk");
					    //c=dir->d_name;
					    //printf("\n--%s",c);
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
                           		  {printf("\n path doesn't exists");break;}
					path[plen]='\0';
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
 
printf("\n list:\n");
  for(i=0;i<=count;i++)
  {
  	printf("\n%s-%ld",f[i].name,fptr[i].st_size);
  }
  printf("\n after sorting..\n");
  for(i=0;i<=count;i++)
  {
  	for(j=i+1;j<=count;j++)
  	{
  		if(strcmp(f[i].name,f[j].name)>0)
  		{
  			tmp.name=f[i].name;
  			tmp.ptr=f[i].ptr;
  			f[i].name=f[j].name;
  			f[i].ptr=f[j].ptr;
  			f[j].name=tmp.name;
  			f[j].ptr=tmp.ptr;
		  }
	  }
  }
  for(i=0;i<=count;i++)
  {
  	 printf( (S_ISDIR(f[i].ptr->st_mode)) ? "d" : (S_ISLNK(f[i].ptr->st_mode)) ? "l" :"-");
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
    printf(" %u",f[i].ptr->st_nlink);
    user=getpwuid(f[i].ptr->st_uid);
    gr=getgrgid(f[i].ptr->st_gid);
    printf(" %s",user->pw_name);
    printf(" %s",gr->gr_name);
    printf(" %ld",f[i].ptr->st_size);//file size;
    //strftime(date, 20, "%a %b %e %H:%M", localtime(&(f[i].ptr->st_ctime)));
    //date=ctime(&f[i].ptr->st_mtime);
    
    printf("   %s",procD(ctime(&f[i].ptr->st_mtime)));//f[i].ptr->st_mtime);
  	printf(" %s\n",f[i].name);
  }
   free(fptr);
   free(path);
   return 0;
}
