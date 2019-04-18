#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<dirent.h>
#include<string.h>
#include<stdlib.h>
#include<pwd.h>
#include<grp.h>
void id_inf(char *user)
{
	int ngroups=9,j;
	 gid_t *groups;
	struct passwd *uinf;
	struct group *gr;
	if(strcmp(user," ")==0)
	{
		
		uinf=getpwuid(getuid());
		user=uinf->pw_name;
		
	}
	else
	  printf("\n%s",user);
	gr=getgrgid(uinf->pw_gid);
	printf("\nuid=%d(%s) gid=%d(%s)  groups=",uinf->pw_uid,uinf->pw_name,uinf->pw_gid,gr->gr_name);
	
    /* Retrieve group list */

    if(getgrouplist(user, uinf->pw_gid, groups, &ngroups) == -1) 
    {
        getgrouplist(user, uinf->pw_gid, groups, &ngroups);
    }
           
    /* Display list of retrieved groups, along with group names */

    for (j = 0; j < ngroups; j++) 
    {
        printf("%d", groups[j]);
        gr = getgrgid(groups[j]);
        if (gr != NULL)
            printf("(%s)", gr->gr_name);
        if (j!=ngroups-1)printf(",");
    }
	
}
void main(int argc,char *argv[])
{
	int i;
	
	if(argc>1)
	{
	  if(strcmp(argv[1],"id")==0)
	  {
		
		if(argc==3)
		{
		  id_inf(argv[2]);
		}
		else
		{
		  //uinf=getpwuid(getuid());uinf->pw_name
		  id_inf(" ");
		}
	  
	  }
	  else
	    printf("\n unknown command '%s'",argv[i]);
	}
	else
	 printf("\n enter id command");
}

