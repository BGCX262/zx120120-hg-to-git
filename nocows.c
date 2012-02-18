/*
ID: zx120122
LANG: C
TASK: nocows
*/
#include <stdio.h>
#include <string.h>

int ans[220][120];

int dp(int n_node,int n_level)
{
	int sum=0,i;
	if(ans[n_node][n_level]>=0)return ans[n_node][n_level];
	if(n_node==1)return 1;
	if(n_level<=1)return 0;
	for(i=1;i<=(n_node-2);i++)
		sum +=  dp(i,n_level-1)*dp(n_node-1-i,n_level-1);
	return ans[n_node][n_level]=sum%9901;
}

int main()
{
	int l,n;
	FILE* fin = fopen("nocows.in" ,"r");
	FILE* fout= fopen("nocows.out","w");
	memset(ans,-1,sizeof(ans));

	fscanf(fin,"%i %i",&n,&l);
	dp(n,l-1);
	fprintf(fout,"%i\n",(dp(n,l)-dp(n,l-1)+9901)%9901);
	fclose(fin);
	fclose(fout);
	return 0;
}