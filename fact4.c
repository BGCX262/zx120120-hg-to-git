/*
ID: zx120122
LANG: C
TASK: fact4
*/
#include <stdio.h>

int main()
{
	int i,N,s=1;
	freopen("fact4.in","r",stdin);
	freopen("fact4.out","w",stdout);
	scanf("%i",&N);
	for(i=1;i<=N;i++)
	{
		s*=i;
		while( s && s%10 ==0 )s/=10;
		s%=10000;
	}
	printf("%i\n",s%10);
	fclose(stdout);
	return 0;
}
