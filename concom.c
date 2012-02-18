/*
ID: zx120122
LANG: C
TASK: concom
*/
#include <stdio.h>
#include <string.h>

int own[110][110];
const int n_comp = 100;
int control[110][110];

int main()
{
	int i,j,k,g,n;
	int changed = 1;
	FILE* fin = fopen("concom.in" ,"r");
	FILE* fout= fopen("concom.out","w");
	fscanf(fin,"%i",&n);
	
	for(i=1;i<=n_comp;i++)control[i][i] = 1;
	while(n--)
	{
		fscanf(fin,"%i %i %i",&j,&k,&g);
		own[j][k] += g;
		if(g>50)control[j][k] = 1;
	}
	
	while(changed)
	{
		changed = 0;
		for(i=1;i<=n_comp;i++)
			for(j=1;j<=n_comp;j++)if(!control[i][j])
			{
				int sum = 0;
				/* try to make i control j */
				for(k=1;k<=n_comp;k++)if(k!=i&&control[i][k])
					sum += own[k][j];
				if((sum+own[i][j]) >50)
				{
					control[i][j] = 1;
					changed = 1;
				}
			}
	}
	for(i=1;i<=n_comp;i++)
		for(j=1;j<=n_comp;j++)if(j!=i&&control[i][j])
			fprintf(fout,"%i %i\n",i,j);
	fclose(fin);
	fclose(fout);
	return 0;
}