/*
ID: zx120122
LANG: C
TASK: preface
*/
#include <stdio.h>

int I,V,X,L,C,D,M;

int rome(int num)
{
	while(num>=1000)
	{
		M++;
		num-=1000;
	}
	while(num>=900)
	{
		C++;
		M++;
		num -= 900;
	}
	while(num>=500)
	{
		D++;
		num-=500;
	}
	while(num>=400)
	{
		C++;
		D++;
		num-=400;
	}
	while(num>=100)
	{
		C++;
		num-=100;
	}
	while(num>=90)
	{
		X++;
		C++;
		num-=90;
	}
	while(num>=50)
	{
		L++;
		num-=50;
	}
	while(num>=40)
	{
		X++;
		L++;
		num-=40;
	}
	while(num>=10)
	{
		X++;
		num-=10;
	}
	while(num>=9)
	{
		X++;
		I++;
		num -= 9;
	}
	while(num>=5)
	{
		V++;
		num -= 5;
	}
	while(num>=4)
	{
		I++;
		V++;
		num-=4;
	}
	while(num>=1)
	{
		I++;
		num-=1;
	}
	return 0;
}

int main()
{
	int i,num;
	FILE* fin = fopen("preface.in" ,"r");
	FILE* fout= fopen("preface.out","w");
	fscanf(fin,"%i",&num);
	for(i=0;i<=num;i++)
		rome(i);
	if(I)fprintf(fout,"I %i\n",I);
	if(V)fprintf(fout,"V %i\n",V);
	if(X)fprintf(fout,"X %i\n",X);
	if(L)fprintf(fout,"L %i\n",L);
	if(C)fprintf(fout,"C %i\n",C);
	if(D)fprintf(fout,"D %i\n",D);
	if(M)fprintf(fout,"M %i\n",M);
	fclose(fin);
	fclose(fout);
	return 0;
}