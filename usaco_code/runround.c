/*
ID: zx120122
LANG: C
TASK: runround
*/
#include <stdio.h>

int m[100];
int s[100];
int len;

int isle()
{
	int i;
	for(i=0;i<len;i++)
	{
		while(s[i]!=1)return 0;
	}
	return 1;
}

int isro(unsigned long int n)
{
	int step,i=0,k=0;
	/* Conver to String */
	len=0;
	do{
		if(n%10==0)return 0;
		for(i=0;i<len;i++)
			if(n%10==m[i])return 0;
		s[len] = 0;
		m[len++]=n%10;
	}while(n/=10);

	k = len*10-1;
	for(i=0;i<len;i++)
	{
		step=m[k%len];
		s[k%len]++;
		k-=step;
		if(k%len==len-1&&isle())return 1;
	}
	return 0;
}

int main()
{
	unsigned long int N,i;
	FILE* fin = fopen("runround.in" ,"r");
	FILE* fout= fopen("runround.out","w");
	fscanf(fin,"%lud",&N);
	N++;
	while(1)
	{
		if(!isro(N))N++;
		else break;
	}
	
	fprintf(fout,"%i\n",N);
	fclose(fin);
	fclose(fout);
	return 0;
}