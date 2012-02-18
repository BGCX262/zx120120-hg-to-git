/*
ID: zx120122
LANG: C
TASK: comehome
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
int hasCow[60];
int dist[60][60];

#ifdef ABVD
#define CC(a) (tolower(a)-'a' + isupper(a)?26:0)
#endif

int CC(char a)
{
	if(a>='A' && a<='Z')
	{
		return a - 'A' + 26;
	}
	else
	{
		return a - 'a';
	}
}

char DD(int i)
{
	if(i>=26)return i-26+'A';
	else return i + 'a';
}

int main()
{
	int i,j,k,n,d,i_min=CC('Z')+1;
	char a,b;
	FILE* fin = fopen("comehome.in","r");
	FILE* fout= fopen("comehome.out","w");
	fscanf(fin,"%i",&n);
	for(i=0;i<60;i++)
	{
		for(j=0;j<60;j++)dist[i][j] = 100000000;
		dist[i][i] = 0;
	}
	for(i=0;i<n;i++)
	{
		a = fgetc(fin);
		if(a== ' ')a= fgetc(fin);
		if(a=='\n')a= fgetc(fin);
		b = fgetc(fin);
		if(b== ' ')b= fgetc(fin);
		if(b=='\n')b= fgetc(fin);
		fscanf(fin,"%i",&d);
		
		if(a<='Z'&&a>='A')hasCow[CC(a)] = 1;
		if(b<='Z'&&b>='A')hasCow[CC(b)] = 1;
		
		if( d < dist[CC(a)][CC(b)] )
			dist[CC(a)][CC(b)] = dist[CC(b)][CC(a)] = d;
	}
	
	/* floyd */
	for(k=0;k<26*2;k++)
		for(i=0;i<26*2;i++)
			for(j=0;j<26*2;j++)
			if( dist[i][j] > dist[i][k] + dist[k][j] )
				dist[i][j] = dist[i][k] + dist[k][j];
	
	for(i=0;i<CC('Z');i++)if(hasCow[i]==1&&dist[i][CC('Z')] < dist[i_min][CC('Z')])
		i_min = i;
	fprintf(fout,"%c %i\n",DD(i_min),dist[i_min][CC('Z')]);
	fclose(fin);
	fclose(fout);
	return 0;
}