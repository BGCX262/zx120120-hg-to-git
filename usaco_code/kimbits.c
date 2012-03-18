/*
ID: zx120122
LANG: C
TASK: kimbits
*/
#include <stdio.h>
#include <string.h>
unsigned int N,L,I;
int st[40][40];

int dp(int l,int nb)
{
	if(l==0||nb==0)return 1;
	if(st[l][nb]>=0)return st[l][nb];
	return st[l][nb] = dp(l-1,nb) + dp(l-1,nb-1);
}

int main()
{
	freopen("kimbits.in","r",stdin);
	freopen("kimbits.out","w",stdout);
	memset(st,-1,sizeof(st));
	scanf("%u%u%u",&N,&L,&I);
	I--;
	while(N--)
	{
		if( I && L && dp(N,L) <= I)
		{
			I-=dp(N,L);
			L--;
			putchar('1');
		}
		else putchar('0');
	}
	putchar('\n');
	fclose(stdout);
	return 0;
}
