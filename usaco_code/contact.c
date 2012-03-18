/*
ID: zx120122
LANG: C
TASK: contact
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct counter
{
	int key,v;
}counter;
counter cnt[(1<<13)+50];

int m[201000];
int len=0;
int A,B,N;

inline int ccmp(const void * a,const void * b)
{
	return (*(counter*)b).v == (*(counter*)a).v?
		 ( (*(counter*)a).key - (*(counter*)b).key ):( (*(counter*)b).v - (*(counter*)a).v );
}

inline int print_it(FILE *f,int st)
{
	int mask = 1<<20;
	while(!(mask&st))mask>>=1;
	mask>>=1;
	while(mask)
	{
		fprintf(f,"%i",(st&mask)?1:0);
		mask>>=1;
	}
	return 0;
}

int main()
{
	int i,j,l_cnt=0,fst=1,t=-1;
	int ss[100] = {1,1,1,1,1,5,4,3,2};
	char c;
	FILE* fin = fopen("contact.in" ,"r");
	FILE* fout= fopen("contact.out","w");
	#ifdef D
	fout = stdout;
	#endif
	fscanf(fin,"%i%i%i",&A,&B,&N);
	while( (c=fgetc(fin))!=EOF )if(c=='1'||c=='0')
		m[len++] = c-'0';
	for(i=0;i<(1<<13);i++)cnt[i].key = i;
	for(i=0;i<len;i++)
	{
		int s = 1;
		for(j=0;j<A;j++)
			s = (s<<1)|m[i+j];
		if(j>len)break;
		for(;j<=B&&(i+j)<=len;j++)
		{
			cnt[s].v++;
			s = (s<<1)|m[i+j];
		}
	}
	qsort(cnt,1<<13,sizeof(cnt[0]),ccmp);
	for(i=0;cnt[i].v > 0;i++)
	{
		if(cnt[i].v != t)
		{
			if(!N)break;
			N--;
			t = cnt[i].v;
			l_cnt = 1;
			if(!fst)fprintf(fout,"\n");
			fst = 0;
			fprintf(fout,"%i\n",cnt[i].v);
			print_it(fout,cnt[i].key);
		}
		else
		{
			if(l_cnt==6)
			{
				l_cnt=0;
				fprintf(fout,"\n");
			}
			l_cnt++;
			if(l_cnt>1)fputc(' ',fout);
			print_it(fout,cnt[i].key);
		}
	}
	fprintf(fout,"\n");
	fclose(fin);
	fclose(fout);
	return 0;
}