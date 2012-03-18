/*
ID: zx120122
LANG: C
TASK: spin
*/

#include <stdio.h>

int v[5];
int g[5][360];
int p[5];

int d(int l,int i)
{
	return g[l][(i+360-p[l])%360];
}

int check_ok()
{
	int i;
	for(i=0;i<360;i++)
	{
		if(5== (d(0,i) + d(1,i) + d(2,i) + d(3,i) + d(4,i)) )
			return 1;
	}
	return 0;
}

int main()
{
	FILE *fin,*fout;
	fin = fopen("spin.in","r");
	fout = fopen("spin.out","w");

	int i,t;
	for(i=0;i<5;i++)
	{
		int n;
		fscanf(fin,"%i%i",&v[i],&n);

		while(n--)
		{
			int s,e,j;
			fscanf(fin,"%i%i",&s,&e);
			for(j=0;j<=e;j++)
				g[i][(s+j)%360] = 1;
		}
	}
	int isok = 0;
	if(check_ok())
	{
		fprintf(fout,"%i\n",0);
		isok = 1;
	}
	else for(t=1;t<=360;t++)
	{
		for(i=0;i<5;i++)
		{
			p[i] += v[i];
			p[i] %= 360;
		}
		if(check_ok())
		{
			fprintf(fout,"%i\n",t);
			{
				isok = 1;
				break;
			}
		}
	}
	if(!isok)fprintf(fout,"none\n");
	
	fclose(fin);
	fclose(fout);
	return 0;
}