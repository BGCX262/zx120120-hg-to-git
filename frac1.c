/*
ID: zx120122
LANG: C
TASK: frac1
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int sq[10000][2];
int n_sq;

int hasCommonFactor(int a,int b)
{
	int i;
	if(a==b)return 1;
	for(i=2;i<(a>b?a:b);i++)
	{
		if(a%i==0&&b%i==0)return 1;
	}
	return 0;
}


int sq_cmp(const void * x,const void * y)
{
	float a,b;
	a = (float)((const int*)x)[0];
	a/= (float)((const int*)x)[1];
	b = (float)((const int*)y)[0];
	b/= (float)((const int*)y)[1];
	if(a-b>0)return 1;
	if(a-b<0)return -1;
	return 0;
}

int main()
{
	int i,j,N;
	FILE* fin =fopen("frac1.in" ,"r");
	FILE* fout=fopen("frac1.out","w");
	fscanf(fin,"%i",&N);
	
	for(i=1;i<=N;i++)
	{
		for(j=1;j<i;j++)
		{
			if(hasCommonFactor(i,j))continue;/* DO NOT USE BREAK */
			sq[n_sq][0] = j;
			sq[n_sq][1] = i;
			n_sq++;
		}
	}
	
	qsort(sq,n_sq,sizeof(sq[0]),sq_cmp);
	
	fprintf(fout,"%i/%i\n",0,1);
	for(i=0;i<n_sq;i++)
	{
		fprintf(fout,"%i/%i\n",sq[i][0],sq[i][1]);
	}
	fprintf(fout,"%i/%i\n",1,1);
	
	fclose(fin);
	fclose(fout);
	return 0;
}