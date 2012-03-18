/*
ID: zx120122
LANG: C
TASK: subset
*/

#include <stdio.h>
#include <string.h>
int N;
int target;
int cnt;

int state[45][810];

int di(int i,int j)
{
    if(state[i][j]>=0)return state[i][j];
    state[i][j]=(di(i-1,j)+di(i-1,j-i));
    return state[i][j];
}

int main()
{
    FILE* fin =fopen("subset.in","r");
    FILE* fout=fopen("subset.out","w");
    fscanf(fin,"%i",&N);
    target = N*(N+1)/2;
    memset(state,-1,sizeof(state));
    memset(state[1],0,sizeof(state[0]));
    state[1][1] = 1;
    if(target%2==0)
    {
	target/=2;
    	//digui(1,0);
	cnt = di(N,target);
    }
    fprintf(fout,"%i\n",cnt);
    fclose(fin);
    fclose(fout);
    return 0;
}
