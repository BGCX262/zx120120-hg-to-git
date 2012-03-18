/*
ID: zx120122
LANG: C
TASK: ratios
*/

#include <stdio.h>

int a[3],b[3],c[3],t[3];

void gd(FILE* f,int *p)
{
	fscanf(f,"%i%i%i",p,p+1,p+2);
}

int isok(int x,int y,int z)
{
	int t0,t1,t2,ts,gs;
	t0 = x*a[0] + y*b[0] + z*c[0];
	t1 = x*a[1] + y*b[1] + z*c[1];
	t2 = x*a[2] + y*b[2] + z*c[2];
	
	ts = t0 + t1 + t2;
	gs = t[0] + t[1] + t[2];
	
	if( ts % gs == 0 )
	{
		int p = ts / gs;
		if(	p * t[0] == t0 && 
			p * t[1] == t1 &&
			p * t[2] == t2 )
		{
			return p;
		}
	}
	
	return 0;
}


int main()
{
	FILE *fin,*fout;
	fin = fopen("ratios.in","r");
	fout = fopen("ratios.out","w");

	gd(fin,t);gd(fin,a);gd(fin,b);gd(fin,c);

	int x,y,z;
	int mi = 0x7fff,mi_tp = -1;
	int mi_x,mi_y,mi_z;
	for(x=0;x<=100;x++)
	for(y=0;y<=100;y++)
	for(z=0;z<=100;z++)
	{
		int tp = isok(x,y,z);
		if( tp )
		{
			if( (x+y+z) < mi )
			{
				mi = x + y + z;
				mi_x = x;
				mi_y = y;
				mi_z = z;
				mi_tp = tp;
			}
		}
	}
	
	if(mi_tp > 0)
		fprintf(fout,"%i %i %i %i\n",mi_x,mi_y,mi_z,mi_tp);
	else 
		fprintf(fout,"NONE\n");

	fclose(fin);
	fclose(fout);
	return 0;
}