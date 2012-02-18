/*
ID: zx120122
LANG: C
TASK: inflate
*/
#include <stdio.h>
#include <string.h>

int f[11000];

int main()
{
	int n,t;
	int i,j,k,score,cost,s,c;
	FILE* fin = fopen("inflate.in","r");
	FILE* fout= fopen("inflate.out","w");
	fscanf(fin,"%i %i",&t,&n);
	for(i=0;i<n;i++)
	{
		fscanf(fin,"%i%i",&s,&c);
		for(j=c;j<=t;j++)
		{
			/*for(score=0,cost=0;cost<=j;score+=s,cost+=c )
			{
				if(j>=cost)
					if( f[j-cost]+score > f[j] )
						f[j] =  f[j-cost]+score;
			}*/
			if( (f[j-c]+s)>f[j] )f[j] = f[j-c]+s;
		}
	}
	fprintf(fout,"%i\n",f[t]);
	fclose(fin);
	fclose(fout);
	return 0;
}