/*
ID: zx120122
LANG: C
TASK: cowtour
*/

/*
 * Your program ('cowtour') produced all correct answers!  This is your
 * submission #15 for this problem.  Congratulations! 
 */

#include <stdio.h>
#include <string.h>
#include <math.h>

struct{
 int x;
 int y;
}vertex[200];
int n_vertex;

double edge[200][200];
double dist[200][200];
const double INF = 99999.9;
int  muqu[200];
int mq[200][200];
double mxDist[200];
int n_mq;

double get_dist(int a,int b)
{
	double dx = vertex[a].x - vertex[b].x;
	double dy = vertex[a].y - vertex[b].y;
	return sqrt( dx*dx + dy*dy );
}

void mark_it(int n,int flag)
{ 
	int i;
	muqu[n] = flag + 1;
	mq[flag][0]++;
	mq[flag][mq[flag][0]] = n;
	
	for(i=0;i<n_vertex;i++)if(edge[n][i]<INF&&!muqu[i])
	mark_it(i,flag);
}

void floyd()
{
	int i,j,k;
	double max_s = 0.0;
	for(i=0;i<n_vertex;i++)
	{
		for(j=0;j<n_vertex;j++)
		dist[i][j] = edge[i][j];
		dist[i][i] = 0;
	}
	for(k=0;k<n_vertex;k++)
		for(i=0;i<n_vertex;i++)
			for(j=0;j<n_vertex;j++)if (dist[i][k] + dist[k][j] < dist[i][j])
				dist[j][i] = dist[i][j] = dist[i][k] + dist[k][j];
}

int main()
{
	int i,j,k;
	int mq_a,mq_b;
	double s,min_s = INF,m = 0.0;
	FILE* fin = fopen("cowtour.in","r");
	FILE* fout= fopen("cowtour.out","w");
	fscanf(fin,"%i",&n_vertex);
	for(i=0;i<n_vertex;i++)
		fscanf(fin,"%i %i",&vertex[i].x,&vertex[i].y);
	for(i=0;i<n_vertex;i++)
		for(j=0;j<n_vertex;j++)
		{
			char c = fgetc(fin);
			if(c=='\n')c = fgetc(fin);
			if(c=='1')edge[i][j] = get_dist(i,j);
			else if(c=='0') edge[i][j] = INF;
		}
	k = 0;
	for(i=0;i<n_vertex;i++)
		if(!muqu[i])
			mark_it(i,n_mq++);
	floyd();
	for(i=0;i<n_vertex;i++)
	{
		mxDist[i] = 0.0;
		for(j=0;j<n_vertex;j++)
		if(dist[i][j] > mxDist[i] && dist[i][j] < INF)mxDist[i] = dist[i][j];
		if(mxDist[i]>m)m = mxDist[i];
	}

	for(mq_a=0;mq_a<n_mq;mq_a++)
	for(mq_b=0;mq_b<n_mq;mq_b++)if(mq_a!=mq_b)
	for(i=1;i<=mq[mq_a][0];i++)
		for(j=1;j<=mq[mq_b][0];j++)
		{
			int a = mq[mq_a][i];
			int b = mq[mq_b][j];
			double dis = get_dist(a,b),fa_a=0.0,fa_b=0.0;
			s = mxDist[a] + mxDist[b] + dis;
			if(s<min_s)min_s = s;
		}
	if(min_s<m)min_s = m;
	fprintf(fout,"%.6f\n",min_s);
	fclose(fin);
	fclose(fout);
	 return 0;
}
