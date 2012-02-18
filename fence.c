/*
ID: zx120122
LANG: C
TASK: fence
*/
#include <stdio.h>
#include <string.h>

int m[501][501];
int hit[501];
int ans[1500],n_ans=0;
int F,m_min=501,m_max=1;

int get_neighbor(int p,int *s){
	int i;
	for(i=(*s);i<=m_max;i++)if(m[p][i])
		return (*s=i+1)-1;
	return 0;
}

void travel(int p){
	int q,s=m_min;
	while( (q = get_neighbor(p,&s)) ){
		m[p][q]--;
		m[q][p]--;
		travel(q);
	}
	ans[n_ans++] = p;
}

int main(){
	FILE* fin  = fopen("fence.in" ,"r");
	FILE* fout = fopen("fence.out","w");
	#ifdef D
	fout = stdout;
	#endif
	int i;
	fscanf(fin,"%i",&F);
	for(i=1;i<=F;i++){
		int a,b;
		fscanf(fin,"%i%i",&a,&b);
		if(a>m_max)m_max=a;
		if(b>m_max)m_max=b;		
		if(a<m_min)m_min=a;
		if(b<m_min)m_min=b;
		hit[a]++;hit[b]++;
		m[a][b]++; 
		m[b][a]++;
	}
	for(i=m_min;i<=m_max&&!n_ans;i++)if(hit[i]%2==1)
		travel(i);
	if(!n_ans)travel(m_min);
	while(n_ans--)fprintf(fout,"%i\n",ans[n_ans]);
	fclose(fin);
	fclose(fout);
	return 0;
}