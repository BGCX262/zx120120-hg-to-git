/*
ID: zx120122
LANG: C
TASK: ttwo
*/
#include <stdio.h>
#include <string.h>


char maze[12][12];
int move[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
int f_i,f_j,f_pos=0;
int c_i,c_j,c_pos=0;

int main()
{
	int i,j,can = 0,t=0;
	FILE* fin = fopen("ttwo.in" ,"r");
	FILE* fout= fopen("ttwo.out","w");
	
	for(i=1;i<=10;i++)
		fscanf(fin,"%s",&maze[i][1]);
	for(i=0;i<=11;i++)
		maze[i][0] = maze[i][11] = maze[0][i] = maze[11][i] = '*';
	
	for(i=1;i<=10;i++)
		for(j=1;j<=10;j++)
		{
			if(maze[i][j]=='F')
			{
				f_i = i;
				f_j = j;
			}
			else if(maze[i][j] == 'C')
			{
				c_i = i;
				c_j = j;
			}
		}
	
	while(t<160000)/* 100*100*4 * 100*100*4 */
	{
		if(f_i==c_i&&f_j==c_j)
		{
			can = 1;
			break;
		}
		if( '*' != maze[c_i + move[c_pos%4][0]][c_j] && '*' != maze[c_i][c_j + move[c_pos%4][1]] )
		{
			c_i += move[c_pos%4][0];
			c_j += move[c_pos%4][1];
		}
		else c_pos++;
		if( '*' != maze[f_i + move[f_pos%4][0]][f_j] && '*' != maze[f_i][f_j + move[f_pos%4][1]] )
		{
			f_i += move[f_pos%4][0];
			f_j += move[f_pos%4][1];
 		}
		else f_pos++;
		t++;
		
	}
	if(can)fprintf(fout,"%i\n",t);
	else fprintf(fout,"0\n");
	fclose(fin);
	fclose(fout);
	return 0;
}