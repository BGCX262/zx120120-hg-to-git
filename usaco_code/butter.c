/*
ID: zx120122
LANG: C
TASK: butter
*/

#include <stdio.h>
#include <string.h>

#define INF (0xFFFFF)

int N,P,C;
int cow[550];
int m[801][801];
int dist_s[801];
int d[801];

int q[10000];
int q_s,q_e;
void enq(int v){
	q[q_e++] = v;
}
int deq(){
	return q[q_s++];
}
void spfa(int src){
	int i;
	short int inq[801] = {0};
	q_s = q_e = 0;
	for(i=1;i<=P;i++)d[i]=INF;
	d[src] = 0;
	enq(src);
	while(q_s<q_e){
		int k = deq();
		inq[k] = 0;
		for(i=1;i<=P;i++)if( (d[k]+m[k][i]) < d[i] ){
			if(!inq[i])enq(i);
			inq[i] = 1;
			d[i] = d[k]+m[k][i];
		}
	}
	for(i=1;i<=P;i++)m[src][i] = m[i][src] = d[i];
}

int main(){
	FILE *fin,*fout = stdout;
	fin = fopen("butter.in","r");
	fout = fopen("butter.out","w");
	#ifdef D
	fout = stdout;
	#endif
	int i,j,k;

	fscanf(fin,"%i%i%i",&N,&P,&C);
	for(i=0;i<=P;i++)for(j=0;j<=P;j++)
		m[i][j] = INF;
	for(i=0;i<=P;i++)m[i][i] = 0;
	for(i=1;i<=N;i++)
		fscanf(fin,"%i",&cow[i]);
	for(i=1;i<=C;i++){
		int a,b,l;
		fscanf(fin,"%i%i%i",&a,&b,&l);
		m[a][b] = m[b][a] = l;
	}

	for(i=1;i<=N;i++){
		spfa(cow[i]);
		for(k=1;k<=P;k++){
			dist_s[k] += d[k];
		}
	}
	
	int min = dist_s[1];
	for(i=2;i<=P;i++)if(dist_s[i]<min)
		min = dist_s[i];
	fprintf(fout,"%i\n",min);
	fclose(fin);
	fclose(fout);
	return 0;
}
