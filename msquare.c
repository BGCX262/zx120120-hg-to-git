/*
ID: zx120122
LANG: C
TASK: msquare
*/

#include <stdio.h>
#include <string.h>

typedef struct state{
	int a[8];
}state;

typedef struct qs{
	state st;
	int n;
}qs;

typedef struct pre{
	int pre_h;
	char act;
}pre;

int fac[] = {0,1,2,6,24,120,720,5040,40320},vis[40320];
pre pr[40320];

state start = {{1,2,3,4,8,7,6,5}},target;
int target_h,start_h;

state A(state st){
	state s;
	s.a[0] = st.a[4];
	s.a[1] = st.a[5];
	s.a[2] = st.a[6];
	s.a[3] = st.a[7];
	s.a[4] = st.a[0];
	s.a[5] = st.a[1];
	s.a[6] = st.a[2];
	s.a[7] = st.a[3];
	return s;
}

state B(state st){
	state s;
	s.a[0] = st.a[3];
	s.a[1] = st.a[0];
	s.a[2] = st.a[1];
	s.a[3] = st.a[2];
	s.a[4] = st.a[7];
	s.a[5] = st.a[4];
	s.a[6] = st.a[5];
	s.a[7] = st.a[6];
	return s;
}

state C(state st){
	state s;
	s.a[0] = st.a[0];
	s.a[1] = st.a[5];
	s.a[2] = st.a[1];
	s.a[3] = st.a[3];
	s.a[4] = st.a[4];
	s.a[5] = st.a[6];
	s.a[6] = st.a[2];
	s.a[7] = st.a[7];
	return s;
}

int hash(state st){
	int code=0,n_low,i,j;
	int vist[9] = {0};
	for(i=0;i<7;i++){
		vist[ st.a[i] ] = 1;
		n_low = st.a[i] - 1;
		
		for(j=1;j<st.a[i];j++)if(vist[j])
			n_low --;
		code += n_low * fac[7-i];
	}
	return code;
}

#define Q_SIZE (40320*2)
state q[Q_SIZE];
int q_s,q_e;
void enq(state st){
	q[(q_e++)%Q_SIZE] = st;
}
state deq(){
	return q[(q_s++)%Q_SIZE];
}

int tryins(state st,char c,int preh)
{
	int st_h = hash(st);
	if( !vis[st_h] )
	{	
		vis[st_h] = 1;
		pr[st_h].pre_h = preh;
		pr[st_h].act = c;
		if( st_h == target_h )return 1;
		enq(st);
	}
	return 0;
}

char s[1000];
int len;
int get_ans()
{
	int id = target_h;
	while( id != start_h ){
		s[len++] = pr[id].act;
		id = pr[id].pre_h;
	}
	return 0;
}

int main()
{
	FILE *fin,*fout = stdout;
	fin = fopen("msquare.in","r");
	fout = fopen("msquare.out","w");
	
	int i;
	for(i=0;i<4;i++)
		fscanf(fin,"%i",&target.a[i]);
	for(i=7;i>3;i--)
		fscanf(fin,"%i",&target.a[i]);
	
	start_h = hash(start);
	target_h = hash(target);
	
	pr[start_h].pre_h = - 1;
	pr[start_h].act = -1;
	vis[start_h] = 1;

	enq(start);
	
	while( q_s < q_e ){
		state p = deq();
		int h = hash(p);
		if( h == target_h )break;
		
		if(tryins(A(p),'A',h))break;
		if(tryins(B(p),'B',h))break;
		if(tryins(C(p),'C',h))break;
	}
	get_ans();
	
	fprintf(fout,"%i\n",len);
	while(len--)fputc(s[len],fout);
	fputc('\n',fout);

	fclose(fin);
	fclose(fout);
	return 0;
}
