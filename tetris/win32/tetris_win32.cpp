#include <Windows.h>
#include <stdlib.h>
#include "block_def.h"

HBRUSH block_color[10],background_color,empty_block_color,predict_block_color;
int n_block_color = 1;

/* Game Logic */
const int board_width = 10,board_height = 20;
struct GameStatus
{
	int board[board_width][board_height];
	int db_id,db_state,nx_db_id;
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
	
	if(!gs->nx_db_id)
		gs->nx_db_id = rand()%n_shape + 1;
	gs->db_id = gs->nx_db_id - 1;
	gs->nx_db_id = rand()%n_shape + 1;

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
}block_postion[board_width][board_height],nx_block_postion[4][4];
const int block_width=25,block_heigh=25,block_gap=2;

int pre_calc_position()
{
	int i,j;
	
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		{
			nx_block_postion[i][j].x = 330 + i * block_width + i * block_gap;
			nx_block_postion[i][j].y = 120 + j * block_heigh + j * block_gap;
		}

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
	empty_block_color   = CreateSolidBrush(RGB(80,80,80));
	background_color    = CreateSolidBrush(RGB(100,100,100));
	predict_block_color = CreateSolidBrush(RGB(110,110,110));

	block_color[n_block_color++] = CreateSolidBrush(RGB(170,200,200));/* Grey */
	block_color[n_block_color++] = CreateSolidBrush(RGB(100,159,241));/* Blue */
	block_color[n_block_color++] = CreateSolidBrush(RGB(66,206,115));/* Green RGB(115,230,115) */
	block_color[n_block_color++] = CreateSolidBrush(RGB(238,180,180));/*Pink*/
	block_color[n_block_color++] = CreateSolidBrush(RGB(222,222,134));/*Brown?*/
	//block_color[n_block_color++] = CreateSolidBrush(RGB(238,210,5));/*Orange*/
	//block_color[n_block_color++] = CreateSolidBrush(RGB(230,100,100));/*Red*/
	return 0;
}

int render_block(HDC hdc,int x,int y,HBRUSH hbColor)
{
	RECT b;
	b.left = block_postion[x][y].x;
	b.right = block_postion[x][y].x + block_width;
	
	b.top = block_postion[x][y].y;
	b.bottom = block_postion[x][y].y + block_heigh;

	FillRect(hdc,&b,hbColor);

	return 0;
}

int render_block_at(HDC hdc,int abs_x,int abs_y,int b_width,int b_heigh,HBRUSH hbColor)
{
	RECT b;
	b.left = abs_x;
	b.right = abs_x + b_width;

	b.top = abs_y;
	b.bottom = abs_y + b_heigh;

	FillRect(hdc,&b,hbColor);
	return 0;
}

int draw_scene(GameStatus *gs,HDC hdc)
{
	int x,y;
	for(y=0;y<board_height;y++)
	{
		for(x=0;x<board_width;x++)
		{
			if( has_dropping_block(gs,x,y) )
				render_block(hdc,x,y,block_color[get_block_color(gs,x,y)]);
			else if( has_predict_block(gs,x,y) )
				render_block(hdc,x,y,predict_block_color);
			else if( gs->board[x][y] )
				render_block(hdc,x,y,block_color[get_block_color(gs,x,y)]);
			else
				render_block(hdc,x,y,empty_block_color);
		}
	}

	for(x=0;x<4;x++)
		for(y=0;y<4;y++)if( (*shape[gs->nx_db_id-1])[0][x][y] )
		{
			render_block_at(hdc,nx_block_postion[x][y].x,nx_block_postion[x][y].y,
				block_width,block_heigh,block_color[gs->db_color]);
		}
		else render_block_at(hdc,nx_block_postion[x][y].x,nx_block_postion[x][y].y,
			block_width,block_heigh,background_color);
	
	return 0;
}

/* MainWindows and loops */
TCHAR szClassName [] = TEXT("TetrisWindow");
TCHAR szWindowName[] = TEXT("Tetris");
const int window_width = 500,window_heigh = 610;
GameStatus gstatus;

LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, 
				   HINSTANCE hPrevInstance, 
				   LPSTR lpCmdLine, 
				   int nShowCmd )
{
	pre_calc_position();
	init_color();
	drop_new_block(&gstatus);

	WNDCLASSEX wndc;
	wndc.cbClsExtra		= NULL;
	wndc.cbSize			= sizeof(WNDCLASSEX);
	wndc.cbWndExtra		= NULL;
	wndc.hbrBackground	= background_color;
	wndc.hCursor		= LoadCursor(NULL,MAKEINTRESOURCE(IDC_ARROW));
	wndc.hIcon			= LoadIcon(hInstance,MAKEINTRESOURCE(IDI_APPLICATION));
	wndc.hIconSm		= LoadIcon(hInstance,MAKEINTRESOURCE(IDI_APPLICATION));
	wndc.hInstance		= hInstance;
	wndc.lpfnWndProc	= WndProc;
	wndc.lpszClassName	= szClassName;
	wndc.lpszMenuName	= NULL;
	wndc.style			= CS_HREDRAW | CS_VREDRAW;

	if(!RegisterClassEx(&wndc))
	{
		MessageBox(NULL,TEXT("Error"),TEXT("RegisterClass Failed."),MB_OK);
	}

	HWND hWnd = CreateWindow(szClassName,szWindowName,WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,CW_USEDEFAULT,window_width,window_heigh,
		NULL,NULL,hInstance,NULL);

	UpdateWindow(hWnd);
	ShowWindow(hWnd,nShowCmd);

	MSG msg;
	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch(message)
	{
	case WM_CREATE:
		SetTimer(hWnd,1,500,NULL);
		break;
	case WM_TIMER:
		if(!next_step(&gstatus))
		{
			KillTimer(hWnd,(UINT)wParam);
			MessageBox(hWnd,TEXT("Notice"),TEXT("Game Over"),MB_OK);
		}
		InvalidateRect(hWnd,NULL,NULL);
		break;
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_SPACE:
			drop_block_direct(&gstatus);
			next_step(&gstatus);
			break;
		case VK_UP:
			rotate_block(&gstatus);
			break;
		case VK_LEFT:
			move_block_left(&gstatus);
			break;
		case VK_RIGHT:
			move_block_right(&gstatus);
			break;
		case VK_DOWN:
			if(!next_step(&gstatus))
			{
				KillTimer(hWnd,(UINT)wParam);
				MessageBox(hWnd,TEXT("Notice"),TEXT("Game Over"),MB_OK);
			}
			break;
		}
		InvalidateRect(hWnd,NULL,NULL);
		break;
	case WM_PAINT:
		HDC hdc;
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd,&ps);
		draw_scene(&gstatus,hdc);
		EndPaint(hWnd,&ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd,message,wParam,lParam);
	}
	return 0;
}