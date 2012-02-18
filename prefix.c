/*
ID: zx120122
LANG: C
TASK: prefix
*/
#include <stdio.h>
#include <string.h>

char elem[240][15];
int n_elem;

char s[201000];
int ischeck[201000];
int n_s;

int main()
{
	int i,j,k;
	FILE* fin = fopen("prefix.in" ,"r");
	FILE* fout= fopen("prefix.out","w");
	memset(elem,0,sizeof(elem));
	while(1)
	{
		fscanf(fin,"%s",&elem[n_elem]);
		if(elem[n_elem][0]=='.')break;
		else n_elem++;
	}

	while(1)
	{
		char c = fgetc(fin);
		if(c=='\n')continue;
		if(c==EOF)break;
		s[n_s++]=c;
	}
	
	for(i=0;i<n_elem;i++)
	{
		int len = strlen(elem[i]);
		for(j=0;j<n_s;j++)
		{
			int isok=1;
			for(k=0;k<len;k++)
			{
				if(elem[i][k]!=s[j+k]){isok=0;break;}
			}
			if(isok)for(k=0;k<len;k++)
				ischeck[j+k] = 1;
		}
	}
	
	for(i=0;i<n_s;i++)
		if(!ischeck[i])break;
	fprintf(fout,"%i\n",i);
	
	fclose(fin);
	fclose(fout);
	return 0;
}