/*
ID: zx120122
LANG: C
TASK: castle
*/
#include <stdio.h>

FILE *fin,*fout;
int col,row;
int r[60][60];
int map[60][60];
int hasTravel[60][60];

int room_info[60*60];
int square;
int max_square;
int n_room;

int max_combine_s = 0;
int c_row,c_col;
char pos;

int travel(int ro,int co)
{
	int t;
	if(hasTravel[ro][co])return 0;
	else hasTravel[ro][co]=1;
	square++;
	t = r[ro][co];
	map[ro][co] = n_room;
	if(t%2==0)
	{
		if(!hasTravel[ro][co-1])travel(ro,co-1);
	}else t-=1;
	if(t%4==0)
	{
		if(!hasTravel[ro-1][co])travel(ro-1,co);
	}else t-=2;
	if(t%8==0)
	{
		if(!hasTravel[ro][co+1])travel(ro,co+1);
	}else t -= 4;
	if(t%16==0)
	{
		if(!hasTravel[ro+1][co])travel(ro+1,co);
	}else t-=8;
	return 0;
}

int main()
{
	int i,j,t;
	fin =fopen("castle.in" ,"r");
	fout=fopen("castle.out","w");

	fscanf(fin,"%i %i",&col,&row);
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
		{
			fscanf(fin,"%i",&r[i][j]);
		}
	
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
		{
			square = 0;
			travel(i,j);
			if(square!=0)
			{
				if(square>max_square)max_square=square;
				room_info[n_room++] = square;
			}	
		}

	for(j=0;j<col;j++)
	{
		for(i=row-1;i>=0;i--)
		{
			/*UP*/
			if(i-1>=0&&map[i][j]!=map[i-1][j])
			{
				int s = room_info[map[i][j]] + room_info[map[i-1][j]];
				if(s>max_combine_s)
				{
					max_combine_s = s;
					c_row = i;
					c_col = j;
					pos = 'N';
				}
			}
			/*LEFT*/
			if(j+1<col&&map[i][j]!=map[i][j+1])
			{
				int s = room_info[map[i][j]] + room_info[map[i][j+1]];
				if(s>max_combine_s)
				{
					max_combine_s = s;
					c_row = i;
					c_col = j;
					pos = 'E';
				}
			}
		}
	}
	
	fprintf(fout,"%i\n%i\n%i\n%i %i %c\n",n_room,max_square,max_combine_s,c_row+1,c_col+1,pos);
	
	fclose(fin);
	fclose(fout);
	return 0;
}