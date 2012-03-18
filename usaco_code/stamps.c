/*
ID: zx120122
LANG: C
TASK: stamps
*/
#include <stdio.h>

int K,N;
int m[60];
int o[2001000];
int lim = 0;

int main()
{
	int update=1,i,j,mx=0,len=0;
	freopen("stamps.in","r",stdin);
	freopen("stamps.out","w",stdout);
	scanf("%i%i",&K,&N);
	for(i=0;i<2001000;i++)o[i]=300;
	for(i=0;i<N;i++)
	{
		scanf("%i",&m[i]);
		o[m[i]] = 1;
		if(m[i]>lim)lim=m[i];
	}
	while(update)
	{
		update = 0;
		for(i=1;i<=lim;i++)if(o[i]<K)
		{
			for(j=0;j<N;j++)
			{
				if( (o[i]+1) < o[i+m[j]] )
				{
					o[i+m[j]] = o[i]+1;
					if((i+m[j])>lim)lim = i+m[j];
					update = 1;
				}
			}
		}
	}
	for(i=1;i<=lim;i++)if(o[i]<300)
	{
		if(o[i-1]<300)len++;
		else
		{
			if(len>mx)mx=len;
			len=1;
		}
	}
	if(len>mx)mx=len;
	printf("%i\n",mx);
	fclose(stdout);
	return 0;
}