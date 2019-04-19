#include<stdio.h>
#include<math.h>
#include<string.h>
int main()
{
	char str[10000];
	int i,len,flag=0,digits,dec_pos,ips=0;
	double no,princ,rate;
	float yrs,id;
	while(!feof(stdin))
	{
		printf("\n Enter space seperated i/p:");
		gets(str);
		//printf("\n");
		//puts(str);
		//printf("-%d",strlen(str));
		len=strlen(str);
		for(i=0;i<len;i++)
		{
			if(str[i]>='0' && str[i]<='9')
			{
				if(!flag)
				{
					flag=1;
					ips++;
					no=dec_pos=digits=0;
				}
				no=no*10+(str[i]-'0');
				++digits;
			}
			else if(str[i]=='.')
			{
				if(ips==1)
				{
					printf("\n id can onlt be integer!");
					break;
				}
				dec_pos=digits;
			}
			else if(str[i]==' '||str[i]=='\t')
			{
				if(flag)
				{
					switch(ips)
					{
						case 1:id=no;printf("\n processed id!-%lf",id);break;
						case 2:princ=(!dec_pos)?no:no/pow(10,(digits-dec_pos));printf("\n processed princ!-%lf",princ);break;
						case 3:rate=(!dec_pos)?no:no/pow(10,(digits-dec_pos));printf("\n processed rate!-%lf",rate);break;
						//case 4:yrs=no/pow(10,(digits-dec_pos));printf("\n processed yrs!");break;
						default:printf("\n random-%d",ips);break;
					}
				}
				flag=0;
				digits=0;
			}
			else
			{
				printf("\n no other characters except 0-9 & . are allowed!");
				break;
			}
		}
		if(ips==4)
		{
			yrs=(!dec_pos)?no:no/pow(10,(digits-dec_pos));printf("\n processed yrs!");
			printf("\n id:%.0f",id);
			printf("\n princ:%lf",princ);
			printf("\n rate:%lf",rate);
			printf("\n yrs:%f",yrs);
		}
		else
		 printf("\n no. of args should be 4");
		ips=0;flag=0;
	}
}
