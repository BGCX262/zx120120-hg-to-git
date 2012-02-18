/*
ID: zx120122
LANG: C
TASK: lamps
*/
#include <stdio.h>

int op[4] = {63,21,42,9};
int st[16];
int n_st;
int s_off=0,s_on=0;

int enState(int a,int b,int c,int d)
{
	int state = 63;
	if(a)state^=op[0];
	if(b)state^=op[1];
	if(c)state^=op[2];
	if(d)state^=op[3];
	
	if((state&s_off)!=0)return 0;
	if((state&s_on)!=s_on)return 0;
	st[n_st++]=state;
	return 0;
}

int re(int n)
{
	int k=0,i=6;
	while(i--)
	{
		k*=2;
		k+=n%2;
		n/=2;
	}
	return k;
}

int ncmp(const void* a,const void* b)
{
	return *(int*)a-*(int*)b;
}

int main()
{
	int counter,n_lamp,i_st,i;

	FILE* fin = fopen("lamps.in" ,"r");
	FILE* fout= fopen("lamps.out","w");
	fscanf(fin,"%i",&n_lamp);
	fscanf(fin,"%i",&counter);
	while(1)
	{
		fscanf(fin,"%i",&i);
		if(i==-1)break;
		s_on = s_on | 1<<((i-1)%6);
	}
	
	while(1)
	{
		fscanf(fin,"%i",&i);
		if(i==-1)break;
		s_off = s_off | 1<<((i-1)%6);
	}
	while(counter>=0)
	{
		switch(counter)
		{
			case 4:
				enState(1,1,1,1);
				break;
			case 3:
				enState(1,1,1,0);
				enState(1,1,0,1);
				enState(1,0,1,1);
				enState(0,1,1,1);
				break;
			case 2:
				enState(1,1,0,0);
				enState(0,0,1,1);
				enState(1,0,1,0);
				enState(0,1,0,1);
				enState(0,1,1,0);
				enState(1,0,0,1);
				break;
			case 1:
				enState(0,0,0,1);
				enState(0,0,1,0);
				enState(0,1,0,0);
				enState(1,0,0,0);
				break;
			case 0:
				enState(0,0,0,0);
				break;
		}
		counter-=2;
	}
	for(i=0;i<n_st;i++)
	{
		st[i] = re(st[i]);
	}
	qsort(st,n_st,sizeof(st[0]),ncmp);

	for(i=0;i<n_st;i++)
	{
		st[i] = re(st[i]);
	}
	
	for(i_st=0;i_st<n_st;i_st++)
	{
		int s[6],k=st[i_st],j=0;
		while(j<6)
		{
			s[j] = k%2;
			k/=2;
			j++;
		}
		for(i=0;i<n_lamp;i++)
		{
			fprintf(fout,"%i",s[i%6]);
		}
		fprintf(fout,"\n");
	}
	if(!n_st)fprintf(fout,"IMPOSSIBLE\n");
	
	fclose(fin);
	fclose(fout);
	return 0;
}