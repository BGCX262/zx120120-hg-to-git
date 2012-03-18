/*
ID: zx120122
LANG: C
TASK: humble
*/

/*I DON NOT UNDERSTAND*/
#include <stdio.h>
#include <string.h>

int m[1000000];
int n_m;

int mflag[1000000];

int st[1000000];
int n_st;

int main()
{
	int K,N,i,j,a;
	FILE* fin = fopen("humble.in","r");
	FILE* fout= fopen("humble.out","w");
	fscanf(fin,"%i%i",&K,&N);
	for(n_m=0;n_m<K;n_m++)
		fscanf(fin,"%i",&m[n_m]);
	st[0]=1;
	n_st=1;
	while(n_st<=N)
	{
		int min = 0x7FFFFFFF;
		for(i=0;i<n_m;i++)
		{
			while( (double)m[i]*st[mflag[i]] <= st[n_st-1] )mflag[i]++;
			if((double)m[i]*st[mflag[i]] < min )
				min = m[i]*st[mflag[i]];
		}
		st[n_st++] = min;
	}
	
	fprintf(fout,"%i\n",st[N]);
	fclose(fin);
	fclose(fout);
	return 0;
}