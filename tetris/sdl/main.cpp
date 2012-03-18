#include <Windows.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "block_def.h"

Uint32 block_color[10],background_color,empty_block_color,predict_block_color;
int n_block_color = 1;

/* Game Logic */
const int board_width = 10,board_height = 20;
struct GameStatus
{
	int board[board_width][board_height];
	int db_id,db_state;
	int db_x,db_y;
	int db_color;/* db stands for Dropping Block */
	int pd_x,pd_y;/* pd stands for Predict Drop */
};

int has_block(int b_id,int b_state,
			  int block_x,int block_y,int query_x,int query_y)
{
	int dx,dy;
	dx = query_x - block_x;
	dy = query_y - block_y;
	if( dx >= 0 && dx < 4 &&
		dy >= 0 && dy < 4 )
	{
		return ( *shape[b_id] ) [b_state][dx][dy];
	}
	return 0;
}

int has_dropping_block(GameStatus *gs,int query_x,int query_y)
{
	return has_block(gs->db_id,gs->db_state,gs->db_x,gs->db_y,query_x,query_y);
}

int has_predict_block(GameStatus *gs,int query_x,int query_y)
{
	return has_block(gs->db_id,gs->db_state,gs->pd_x,gs->pd_y,query_x,query_y);
}

int get_block(GameStatus *gs,int query_x,int query_y)
{
	return gs->board [ query_x ][ query_y ];
}

int get_block_color(GameStatus *gs,int query_x,int query_y)
{
	if( has_dropping_block(gs,query_x,query_y) )
		return gs->db_color;
	else
		return gs->board [ query_x ][ query_y ];
}

int is_status_legal(GameStatus *gs)
{
	int i,j;

	/* check the last line */
	for(i=0;i<board_width;i++)
		if(has_dropping_block(gs,i,board_height))
			return 0;

	/* check the two side */
	for(j=-4;j<board_height;j++)
		if(has_dropping_block(gs,-1,j) || has_dropping_block(gs,board_width,j))
			return 0;

	/* check each pos */
	for(j=board_height-1;j>=0;j--)
		for(i=0;i<board_width;i++)if(get_block(gs,i,j))
			if(has_dropping_block(gs,i,j))
				return 0;
	return 1;
};

int is_movement_possible(GameStatus *gs,int dx,int dy,int ds)
{
	int o_x = gs->db_x,o_y = gs->db_y,o_s = gs->db_state;
	gs->db_x += dx;
	gs->db_y += dy;
	gs->db_state = (gs->db_state + ds)%4;

	if(!is_status_legal(gs))
	{
		gs->db_x = o_x;
		gs->db_y = o_y;
		gs->db_state = o_s;
		return 0;
	}
	gs->db_x = o_x;
	gs->db_y = o_y;
	gs->db_state = o_s;
	return 1;
}

int is_gameover(GameStatus *gs)
{
	int i;
	for(i=0;i<board_width;i++)if(get_block(gs,i,0))
		return 1;
	return 0;
}

int update_predict_pos(GameStatus *gs)
{
	int o_y = gs->db_y;

	while(is_movement_possible(gs,0,1,0))
		gs->db_y++;

	gs->pd_x = gs->db_x;
	gs->pd_y = gs->db_y;

	gs->db_y = o_y;
	return 0;
}

int drop_new_block(GameStatus *gs)
{
	static int p = 1;
	gs->db_id = rand()%n_shape;
	gs->db_state = rand()%4;
	gs->db_color = (p++)%(n_block_color-1) + 1;

	gs->db_x = ( board_width >> 1 ) - 2;
	gs->db_y = -4;

	update_predict_pos(gs);

	int t,i;
	for(t=0;t<4;t++)
	{
		gs->db_y ++;
		for(i=0;i<board_width;i++)if(has_dropping_block(gs,i,-1))
			return 0;
	}

	return 0;
}

int remove_row(GameStatus *gs,int y)
{
	int i,j;
	for(i=y;i>0;i--)
	{
		for(j=0;j<board_width;j++)
			gs->board[j][i] = gs->board[j][i-1];
	}
	return 0;
}

int clean_up(GameStatus *gs)
{
	int i,j;
	for(j=0;j<board_height;j++)
	{
		int need_clean = 1;
		for(i=0;i<board_width;i++)if(!get_block(gs,i,j))
		{
			need_clean = 0;
			break;
		}

		if(need_clean)
			remove_row(gs,j);
	}
	return 0;
}
int move_block_left(GameStatus *gs)
{
	if(is_movement_possible(gs,-1,0,0))
	{
		gs->db_x --;
		update_predict_pos(gs);
		return 1;
	}
	else return 0;
}

int move_block_right(GameStatus *gs)
{
	if(is_movement_possible(gs,1,0,0))
	{
		gs->db_x ++;
		update_predict_pos(gs);
		return 1;
	}
	else return 0;
}

int rotate_block(GameStatus *gs)
{
	if(is_movement_possible(gs,0,0,1))
	{
		gs->db_state ++;
		gs->db_state %= 4;
		update_predict_pos(gs);
		return 1;
	}
	else return 0;
}

int drop_block_direct(GameStatus *gs)
{
	gs->db_x = gs->pd_x;
	gs->db_y = gs->pd_y;
	return 0;
}


int fuse_block(GameStatus *gs)
{
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)if( (*shape[gs->db_id])[gs->db_state][i][j] )
		{
			if( ( gs->db_x + i) >= 0 && ( gs->db_x + i) < board_width &&
				( gs->db_y + j) >= 0 && ( gs->db_y + j) < board_height )
				gs->board[ gs->db_x + i ][ gs->db_y + j ] = gs->db_color;
		}
	}
	return 0;
}

int next_step(GameStatus *gs)
{
	if(!is_movement_possible(gs,0,1,0))
	{
		fuse_block(gs);
		clean_up(gs);
		if(is_gameover(gs))
			return 0;
		else
			drop_new_block(gs);
	}
	else gs->db_y++;
	return 1;
}

/* Render and Draw */

struct{
	int x,y;
}block_postion[board_width][board_height];
const int block_width=30,block_heigh=30,block_gap=1;
SDL_Surface *screen;

int pre_calc_position()
{
	int i,j;
	for(i=0;i<board_width;i++)
		for(j=0;j<board_height;j++)
		{
			block_postion[i][j].x = 20 + i * block_width + i * block_gap;
			block_postion[i][j].y = 20 + j * block_heigh + j * block_gap;
		}
		return 0;
}

int init_color()
{
	empty_block_color   = SDL_MapRGB(screen->format,80,80,80);
	background_color    = SDL_MapRGB(screen->format,100,100,100);
	predict_block_color = SDL_MapRGB(screen->format,110,110,110);

	block_color[n_block_color++] = SDL_MapRGB(screen->format,170,200,200);/* Grey */
	block_color[n_block_color++] = SDL_MapRGB(screen->format,100,159,241);/* Blue */
	block_color[n_block_color++] = SDL_MapRGB(screen->format,66,206,115);/* Green RGB(115,230,115) */
	block_color[n_block_color++] = SDL_MapRGB(screen->format,238,180,180);/*Pink*/
	block_color[n_block_color++] = SDL_MapRGB(screen->format,222,222,134);/*Brown?*/
	//block_color[n_block_color++] = SDL_MapRGB(screen->format,238,210,5);/*Orange*/
	//block_color[n_block_color++] = SDL_MapRGB(screen->format,230,100,100);/*Red*/
	return 0;
}

int render_block(SDL_Surface *surface,int x,int y,Uint32 color)
{
	SDL_Rect b;
	b.x = block_postion[x][y].x;
	b.w = block_width;
	
	b.y = block_postion[x][y].y;
	b.h = block_heigh;

	SDL_FillRect(surface,&b,color);

	return 0;
}

int draw_scene(GameStatus *gs,SDL_Surface *surface)
{
	int x,y;
	for(y=0;y<board_height;y++)
	{
		for(x=0;x<board_width;x++)
		{
			if( has_dropping_block(gs,x,y) )
				render_block(surface,x,y,block_color[get_block_color(gs,x,y)]);
			else if( has_predict_block(gs,x,y) )
				render_block(surface,x,y,predict_block_color);
			else if( gs->board[x][y] )
				render_block(surface,x,y,block_color[get_block_color(gs,x,y)]);
			else
				render_block(surface,x,y,empty_block_color);
		}
	}
	SDL_Flip(surface);
	return 0;
}

/* MainWindows and loops */

const int window_width = 600,window_heigh = 700;
GameStatus gstatus;

Uint32 cb_next_step(Uint32 interval, void *param)
{
	next_step(&gstatus);
	draw_scene(&gstatus,screen);
	return interval;
}

int main(int argc,char *argv[])
{
	int running = 1,counter = 100;
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(window_width,window_heigh,32,SDL_SWSURFACE);
	pre_calc_position();
	init_color();
	drop_new_block(&gstatus);
	SDL_FillRect(screen,NULL,background_color);
	draw_scene(&gstatus,screen);
	SDL_AddTimer(500,cb_next_step,NULL);
	while(running)
	{
		SDL_Event eve;
		while(SDL_PollEvent(&eve))
		{
			if( eve.type == SDL_QUIT )
				running = 0;
			else if( eve.type == SDL_KEYDOWN )
			{
				switch( eve.key.keysym.sym )
				{
				case SDLK_ESCAPE:
					running = 0;
					break;
				case SDLK_LEFT:
					move_block_left(&gstatus);
					break;
				case SDLK_RIGHT:
					move_block_right(&gstatus);
					break;
				case SDLK_UP:
					rotate_block(&gstatus);
					break;
				case SDLK_DOWN:
					if(!next_step(&gstatus))
						running = 0;
					break;
				case SDLK_SPACE:
					drop_block_direct(&gstatus);
					next_step(&gstatus);
					break;
				}
				draw_scene(&gstatus,screen);
			}
		}
		SDL_Delay(1);
	}

	return 0;
}