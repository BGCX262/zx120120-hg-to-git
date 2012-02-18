/*
ID: zx120122
LANG: C
TASK: money
*/
#include <stdio.h>
#include <string.h>

int m[30];
int n_m=0;
long long int ans[30][11000];
int hasAns[30][11000];

/*
 * f[i,j] = f[i-1,j-m[i-1]] + f[i-1,j]
 * return if j==0 or i==1
 */
long long int dp(int nt,int mon)
{
	int i;
	long long int s=0;
	if(hasAns[nt][mon])return ans[nt][mon];
	if(mon==0)return 1;
	if(nt==1)return mon%m[0]==0;
	for(i=0;i*m[nt-1]<=mon;i++)
		s+=dp(nt-1,mon-m[nt-1]*i);
	hasAns[nt][mon] = 1;
	return ans[nt][mon] = s;
}
 
int main()
{
	int v,n,i;
	FILE* fin = fopen("money.in" ,"r");
	FILE* fout= fopen("money.out","w");

	fscanf(fin,"%i %i",&v,&n);
	for(i=0;i<v;i++)
		fscanf(fin,"%i",&m[i]);

	fprintf(fout,"%lld\n",dp(v,n));
	fclose(fin);
	fclose(fout);
	return 0;
}