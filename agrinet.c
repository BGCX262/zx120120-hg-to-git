/*
ID: zx120122
LANG: C
TASK: agrinet
*/
#include <stdio.h>
#include <string.h>

int N;
int m[150][150];
int c[150];
int po[100000][2];
int n_po = 0;

int s_cmp(const void* a,const void* b)
{
	return m[((int *)a)[0]][((int *)a)[1]] - m[((int *)b)[0]][((int *)b)[1]];
}

int main()
{
	int i,j,cost=0;
	FILE* fin = fopen("agrinet.in","r");
	FILE* fout= fopen("agrinet.out","w");
	fscanf(fin,"%i",&N);
	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
		{
			fscanf(fin,"%i",&m[i][j]);
			if(i<j)
			{
				po[n_po][0] = i;
				po[n_po++][1] = j;
			}
		}
	qsort(po,n_po,sizeof(po[0]),s_cmp);
	
	c[po[0][0]] = c[po[0][1]] =  1;
	cost += m[po[0][0]][po[0][1]];
	i=0;
	printf("(%i %i)%i\n",po[i][0],po[i][1],m[po[i][0]][po[i][1]]);

	for(i=1;i<n_po;i++)
	{
		//printf("(%i %i)%i\n",po[i][0],po[i][1],m[po[i][0]][po[i][1]]);	
		if( c[po[i][0]] == c[po[i][1]] )
			continue;
		c[po[i][0]] = c[po[i][1]] =  1;
		cost += m[po[i][0]][po[i][1]];
		i = 0;
	}

	fprintf(fout,"%i\n",cost);
	fclose(fin);
	fclose(fout);
	return 0;
}