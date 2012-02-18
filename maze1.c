/*
ID: zx120122
LANG: C
TASK: maze1
*/
#include <stdio.h>
#include <string.h>
char maze[300][300];
int  dist[300][300];

int quene[10000][3];
int head,rear;

void enquene(int ro,int co,int s)
{
	quene[rear][0] = ro;
	quene[rear][1] = co;
	quene[rear++][2] = s;
}

int pos_ro[4] = {-1,1,0,0};
int pos_co[4] = {0,0,-1,1};
int W,H;
int dig(int xro,int xco)
{
	int i;
	head = rear = 0;
	enquene(xro,xco,1);
	while(head!=rear)
	{
		int ro,co,s;
		ro = quene[head][0];
		co = quene[head][1];
		s  = quene[head++][2];
		
		if(s<dist[ro][co]) dist[ro][co] = s;
		else continue;
		
		for(i=0;i<4;i++)
		{
			if( maze[pos_ro[i] + 2*ro+1][pos_co[i] + 2*co+1] == ' ' && (pos_ro[i]+ro)<H && (pos_co[i]+co)<W)
				enquene(ro+pos_ro[i],co+pos_co[i],s+1);
		}
	}
	return 0;
}

int main()
{

	int i,j;
	int max_v = 0;
	FILE* fin = fopen("maze1.in","r");
	FILE* fout= fopen("maze1.out","w");
	/*get input*/
	fscanf(fin,"%i%i",&W,&H);
	fgetc(fin);
	for(i=0;i<(2*H+1);i++)
		fgets(maze[i],300,fin);

	/*init dist*/
	for(i=0;i<=H;i++)
		for(j=0;j<=W;j++)
			dist[i][j] = 99999999;
	for(i=0;i<=W;i++)
	{
		if(maze[0][2*i+1]  == ' ')dig(0,i);
		if(maze[2*H][2*i+1]== ' ')dig(H-1,i);
	}
	for(i=0;i<=H;i++)
	{
		if(maze[2*i+1][0] == ' ')dig(i,0);
		if(maze[2*i+1][2*W]==' ')dig(i,W-1);
	}
	
	for(i=0;i<H;i++)
		for(j=0;j<W;j++)
			if(dist[i][j]>max_v)max_v = dist[i][j];
	
	fprintf(fout,"%i\n",max_v);
	
	fclose(fin);
	fclose(fout);
	return 0;
}