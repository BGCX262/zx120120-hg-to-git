/*
ID: zx120122
LANG: C
TASK: fracdec
*/
#include <stdio.h>
#include <string.h>

int m[1000000];
int a[100000];
int b[100000];
int main()
{

	int i=0,j,flag = 0,s = 2,e = 2,c;
	int n_c = 0;
	FILE* fin = fopen("fracdec.in","r");
	FILE* fout= fopen("fracdec.out","w");

	fscanf(fin,"%i%i",&a[0],&c);
	while(1)
	{
		if(a[i]==0)
		{
			e = i;
			break;
		}
		if(m[a[i]]>0)
		{
			s = m[a[i]];
			e = i;
			flag = 1;
		}
		if(flag)break;
		m[a[i]] = i;
		b[i] = a[i]/c;
		a[i+1] = a[i]%c*10;
		i++;
	}
	
	n_c+=fprintf(fout,"%i.",b[0]);
	for(i=1;i<s;i++)
		n_c += fprintf(fout,"%i",b[i]);
	if(flag)
		n_c += fprintf(fout,"(");
	for(i=s;i<e;i++)
	{
		if(n_c%76==0)fputc('\n',fout);
		n_c += fprintf(fout,"%i",b[i]);
	}
	if(flag)
		fprintf(fout,")");
	fprintf(fout,"\n");
	
	fclose(fin);
	fclose(fout);
	return 0;
}