/*
ID: zx120122
LANG: C
TASK: hamming
*/
#include <stdio.h>
#include <string.h>
int N,B,D;

int m[1000];
int len=0; 

int gethm(int a,int b)
{
	int t = a^b;
	int i = 0;
	while(t)
	{
		if(t%2==1)i++;
		t/=2;
	}
	return i;
}

int main()
{
	int lim,i,j;
	FILE* fin = fopen("hamming.in" ,"r");
	FILE* fout= fopen("hamming.out","w");
	fscanf(fin,"%i %i %i",&N,&B,&D);
	lim = 1<<B;
	
	for(i=0;i<lim;i++)
	{
		int isOk = 1;
		for(j=0;j<len&&isOk==1;j++)
		{
			if(gethm(i,m[j])<D)isOk=0;
		}
		if(!isOk)continue;
		else m[len++] = i;
		if(len>=N)break;
	}
	
	for(i=0;i<len-1;i++)
	{
		if((i+1)%10==0)fprintf(fout,"%i\n",m[i]);
		else fprintf(fout,"%i ",m[i]);
	}
	fprintf(fout,"%i\n",m[i]);
	
	fclose(fin);
	fclose(fout);
	return 0;
}