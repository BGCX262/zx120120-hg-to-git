/*
ID: zx120122
LANG: C
TASK: camelot
*/
#include <stdio.h>
#include <string.h>

#define INF (999999)
int king_x,king_y;
int knight_x[1000],knight_y[1000],n_knight;
int R,C;/* C for Delta X thus R Delta Y */

int kn_dx[] = {-2,-1, 1, 2,-2,-1, 1, 2};
int kn_dy[] = { 1, 2, 2, 1,-1,-2,-2,-1};

int ki_dx[] = {-1, 0, 1, 1, 1, 0,-1,-1};
int ki_dy[] = { 1, 1, 1, 0,-1,-1,-1, 0};

int dist[26][30][26][30];
int d_king[26][30];
int d_all[26][30];

int queue[3500],q_s,q_e;
int vis[26][30];
void enq(int p){
	queue[(q_e++)%3500] = p;
}
int deq(){
	return queue[(q_s++)%3500];
}
void p_map(int o[26][30]){
	int i,j;
	printf("\n");
	for(i=R-1;i>=0;i--){
		for(j=0;j<C;j++){
			printf("%i ",o[j][i]);
		}
		printf("\n");
	}
}

void bfs_knight(int px,int py){
	memset(vis,0,sizeof(vis));
	q_s = q_e = 0;
	enq(px);enq(py);enq(0);
	vis[px][py] = 1;
	while(q_s<q_e){
		int x,y,step,i;
		x = deq();y = deq();step = deq();
		dist[px][py][x][y] = step;
		for(i=0;i<8;i++){
			int tx = x + kn_dx[i],ty = y + kn_dy[i];
			if(	tx >= 0 && tx < C &&
				ty >= 0 && ty < R && !vis[tx][ty] ){
					enq(tx);enq(ty);enq(step+1);
					vis[tx][ty] = 1;
			}
		}
	}
}

void bfs_king(){
	memset(vis,0,sizeof(vis));
	q_s = q_e = 0;
	enq(king_x);enq(king_y);enq(0);
	vis[king_x][king_y] = 1;
	while(q_s<q_e){
		int x,y,step,i;
		x = deq();y = deq();step = deq();
		d_king[x][y] = step;
		for(i=0;i<8;i++){
			int tx = x + ki_dx[i],ty = y + ki_dy[i];
			if(	tx >= 0 && tx < C &&
				ty >= 0 && ty < R && !vis[tx][ty] ){
					enq(tx);enq(ty);enq(step+1);
					vis[tx][ty] = 1;
			}
		}
	}
}
int mi_s = INF;

inline  int calc_cost(int dx,int dy,int cx,int cy,int i){
	int old_knight_cost = dist[ knight_x[i] ][ knight_y[i] ][dx][dy];
	int new_knight_cost = dist[ knight_x[i] ][ knight_y[i] ][cx][cy] + dist[cx][cy][dx][dy];
	return new_knight_cost - old_knight_cost + d_king[cx][cy];
}

int find_ans(){
	int dx,dy,cx,cy,i;
	
	/* enum each point to be destinaon */
	for(dx=0;dx<C;dx++)for(dy=0;dy<R;dy++){
		int mi = d_king[dx][dy];/* the king's minimal cost to get to destination */
		/* enum each point that king get touch with knight */
		for(cx=0;cx<C;cx++)for(cy=0;cy<R;cy++)if( d_king[cx][cy] < mi ){
			for(i=0;i<n_knight;i++){/* which knight to get touch with */
				int cost = calc_cost(dx,dy,cx,cy,i);
				if(cost<mi)mi=cost;
			}
		}
		if( (d_all[dx][dy] + mi) < mi_s )
			mi_s = d_all[dx][dy] + mi;
	}
	
	return 0;
}

int main(){
	FILE* fin  = fopen("camelot.in" ,"r");
	FILE* fout = fopen("camelot.out","w");
#ifdef D
	fout = stdout;
#endif
	char c;
	int i,j,m,n;
	fscanf(fin,"%i %i\n",&R,&C);
	fscanf(fin,"%c %i\n",&c,&king_y);
	king_x = c -'A';king_y--;
	while(!feof(fin)){
		c = fgetc(fin);
		if(feof(fin))break;
		if( c == ' ' || c == '\n' )continue;
		knight_x[n_knight] = c - 'A';
		fscanf(fin,"%i",&knight_y[n_knight]);
		knight_y[n_knight++] --;
	}
	for(i=0;i<26;i++)for(j=0;j<30;j++){
		for(m=0;m<26;m++)for(n=0;n<30;n++)
			dist[i][j][m][n] = INF;
		dist[i][j][i][j] = 0;
	}
	/* do bfs */
	for(i=0;i<C;i++)for(j=0;j<R;j++)
		bfs_knight(i,j);
	bfs_king();
	/* sum all */
	for(m=0;m<n_knight;m++)
		for(i=0;i<26;i++)for(j=0;j<30;j++)
			d_all[i][j] += dist[knight_x[m]][knight_y[m]][i][j];
	#ifdef Ds
	p_map(dist[knight_x[0]][knight_y[0]]);
	p_map(d_all);
	#endif
	find_ans();
	fprintf(fout,"%i\n",mi_s);
	fclose(fin);
	fclose(fout);
	return 0;
}
