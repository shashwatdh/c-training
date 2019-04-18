#include<stdio.h>
#include<math.h>
double ci(double p,double r,double t,double n)
{
	return (p*pow((1+(r/n)),(n*t)));
}
void main()
{
	double p,r,t,n;
	printf("Enter p,r,t,n");
	while(!feof(stdin))
	{
		scanf("%lf %lf %lf %lf",&p,&r,&t,&n);
		printf("\n%lf",ci(p,r,t,n));
	}
}