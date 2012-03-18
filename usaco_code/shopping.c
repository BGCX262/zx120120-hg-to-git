/*
ID: zx120122
LANG: C
TASK: shopping
*/
#include <stdio.h>
#define INF (0x1FFFFFFF)
int S,B;
typedef struct discount{
	int n;
	int c[5],k[5];
	int price;
}discount;

typedef struct st{
	int need[5];
}st;

st start;
discount m[100];
int id[5],need[5],price[5];
int tmpid[1000];

int val[6][6][6][6][6];
int vis[6][6][6][6][6];

int can(st s,int d_i){
	int i;
	for(i=0;i<m[d_i].n;i++){
		if( s.need[ m[d_i].c[i] ] < m[d_i].k[i] )return 0;
	}
	return 1;
}
int final(st s){
	int i;
	for(i=0;i<5;i++){
		if(s.need[i]!=0)return 0;
	}
	return 1;
}
st apply(st s,int d_i){
	int i;
	for(i=0;i<m[d_i].n;i++){
		s.need[ m[d_i].c[i] ] -= m[d_i].k[i];
	}
	return s;
}


int dp(st s){
	int i,tmi=INF;
	if(final(s))return 0;
	
	if(vis[s.need[0]][s.need[1]][s.need[2]][s.need[3]][s.need[4]])
		return val[s.need[0]][s.need[1]][s.need[2]][s.need[3]][s.need[4]];
	vis[s.need[0]][s.need[1]][s.need[2]][s.need[3]][s.need[4]] = 1;
	for(i=0;i<S;i++)if(can(s,i)){
		int t = dp(apply(s,i)) + m[i].price;
		if(t<tmi)tmi=t;
	}
	for(i=0;i<B;i++)if(s.need[i]){
		int t;
		st d = s;
		d.need[i] = 0;
		t = dp(d) + price[i]*s.need[i];
		if(t<tmi)tmi=t;
	}
	
	return val[s.need[0]][s.need[1]][s.need[2]][s.need[3]][s.need[4]] = tmi;
}

int main(){
	FILE* fin  = fopen("shopping.in" ,"r");
	FILE* fout = fopen("shopping.out","w");
	#ifdef D
	fout = stdout;
	#endif
	int i,j;
	fscanf(fin,"%i",&S);
	for(i=0;i<S;i++){
		int n;
		fscanf(fin,"%i",&n);
		m[i].n = n;
		for(j=0;j<n;j++)
			fscanf(fin,"%i%i",&m[i].c[j],&m[i].k[j]);
		fscanf(fin,"%i",&m[i].price);
	}
	fscanf(fin,"%i",&B);
	for(i=0;i<B;i++){
		fscanf(fin,"%i%i%i",&id[i],&start.need[i],&price[i]);
		tmpid[id[i]] = i;
	}
	for(i=0;i<S;i++){
		for(j=0;j<m[i].n;j++){
			m[i].c[j] = tmpid[m[i].c[j]];
		}
	}
	vis[0][0][0][0][0] = 1;
	val[0][0][0][0][0] = 1;
	fprintf(fout,"%i\n",dp(start));
	fclose(fin);
	fclose(fout);
	return 0;
}