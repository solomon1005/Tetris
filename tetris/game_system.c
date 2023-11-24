#include "game_system.h"

char minos[7] = { 'I', 'S', 'Z', 'O', 'T', 'J', 'L' };
bool IsMinoFalling = false;
bool RollBack = false;
int softDropVal = 1;
int screen[100][100] = { 0 };

struct FallingMino fallingmino;

char Hold[20] = { '\0' };
char NextMino[20] = { '\0' };
int drop_count = 50;
int best_score = 0;

MCI_OPEN_PARMS game_count;
MCI_OPEN_PARMS game_single;
MCI_OPEN_PARMS game_double;
MCI_OPEN_PARMS game_triple;
MCI_OPEN_PARMS game_tetris;
MCI_OPEN_PARMS game_perfect;
MCI_OPEN_PARMS game_move;
MCI_OPEN_PARMS game_hold;
MCI_OPEN_PARMS game_harddrop;
MCI_OPEN_PARMS game_softdrop;
MCI_OPEN_PARMS game_rotate;
MCI_OPEN_PARMS game_landing;

int dwID_count;
int dwID_single;
int dwID_double;
int dwID_triple;
int dwID_tetris;
int dwID_perfect;
int dwID_move;
int dwID_hold;
int dwID_harddrop;
int dwID_softdrop;
int dwID_rotate;
int dwID_landing;

unsigned _stdcall Thread_Ingame(void* arg)
{
	while (IsGamePlaying)
	{
		if (GamePause)
		{
			continue;
		}
		Sleep(250);
		Drop_Mino(&fallingmino, screen);
	}

	return 0;
}

unsigned _stdcall Thread_AllClear(void* arg)
{
	Sleep(750);
	All_Clear++;
	Sleep(750);
	All_Clear++;
	Sleep(750);
	All_Clear++;
	Sleep(750);
	All_Clear = 0;
	return 0;
}


void softDrop(struct FallingMino* fallingmino, int screen[][100])
{
	DeleteMino(fallingmino->mino_x, fallingmino->mino_y, fallingmino->shape, fallingmino->direction, screen);
	bool flag = true;

	for (int k = 0; k < softDropVal && flag; k++)
	{
		for (int i = 1; i <= 4; i++)
		{
			switch (fallingmino->direction)
			{
			case UP:
				switch (fallingmino->shape)
				{
				case 'I':
					flag = flag && (screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 0 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 2 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'S':
					flag = flag && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'Z':
					flag = flag && (screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 0 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 2 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'O':
					flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'T':
					flag = flag && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'J':
					flag = flag && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'L':
					flag = flag && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				default:
					break;
				}
				break;
			case RIGHT:
				switch (fallingmino->shape)
				{
				case 'I':
					flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'S':
					flag = flag && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'Z':
					flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'O':
					flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'T':
					flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'J':
					flag = flag && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'L':
					flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				default:
					break;
				}
				break;
			case LEFT:
				switch (fallingmino->shape)
				{
				case 'I':
					flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'S':
					flag = flag && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'Z':
					flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'O':
					flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'T':
					flag = flag && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'J':
					flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'L':
					flag = flag && (screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 0 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 2 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				default:
					break;
				}
				break;
			case DOWN:
				switch (fallingmino->shape)
				{
				case 'I':
					flag = flag && (screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 0 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 2 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'S':
					flag = flag && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'Z':
					flag = flag && (screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 0 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 2 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'O':
					flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'T':
					flag = flag && (screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 0 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 2 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'J':
					flag = flag && (screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 0 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 2 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'L':
					flag = flag && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				default:
					break;
				}
				break;
			}
		}
		if (flag)
		{
			fallingmino->mino_y += 1;
			for (int i = 1; i <= 4; i++)
			{
				fallingmino->piece_y[i] += 1;
			}
		}
	}

	SetMino(fallingmino->mino_x, fallingmino->mino_y, fallingmino->shape, fallingmino->direction, screen);

	return;
}


bool IsMinoSetHere(int mino_x, int mino_y, int shape, int direction, int screen[][100])
{
	bool flag = true;

	switch (shape)
	{
	case 'I':
		switch (direction)
		{
		case UP:
			flag = flag && ((screen[mino_y + 1][mino_x + 0] == 0 || screen[mino_y + 1][mino_x + 0] == 2 || screen[mino_y + 1][mino_x + 0] == SHADOW) && mino_x + 0 >= SCREEN_START_X && mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 1] == 0 || screen[mino_y + 1][mino_x + 1] == 2 || screen[mino_y + 1][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 2] == 0 || screen[mino_y + 1][mino_x + 2] == 2 || screen[mino_y + 1][mino_x + 2] == SHADOW) && mino_x + 2 >= SCREEN_START_X && mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 3] == 0 || screen[mino_y + 1][mino_x + 3] == 2 || screen[mino_y + 1][mino_x + 3] == SHADOW) && mino_x + 3 >= SCREEN_START_X && mino_x + 3 <= SCREEN_END_X);
			break;
		case RIGHT:
			flag = flag && ((screen[mino_y + 0][mino_x + 2] == 0 || screen[mino_y + 0][mino_x + 2] == 2 || screen[mino_y + 0][mino_x + 2] == SHADOW) && mino_x + 2 >= SCREEN_START_X && mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 2] == 0 || screen[mino_y + 1][mino_x + 2] == 2 || screen[mino_y + 1][mino_x + 2] == SHADOW) && mino_x + 2 >= SCREEN_START_X && mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 2][mino_x + 2] == 0 || screen[mino_y + 2][mino_x + 2] == 2 || screen[mino_y + 2][mino_x + 2] == SHADOW) && mino_x + 2 >= SCREEN_START_X && mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 3][mino_x + 2] == 0 || screen[mino_y + 3][mino_x + 2] == 2 || screen[mino_y + 3][mino_x + 2] == SHADOW) && mino_x + 2 >= SCREEN_START_X && mino_x + 2 <= SCREEN_END_X);
			break;
		case DOWN:
			flag = flag && ((screen[mino_y + 2][mino_x + 0] == 0 || screen[mino_y + 2][mino_x + 0] == 2 || screen[mino_y + 2][mino_x + 0] == SHADOW) && mino_x + 0 >= SCREEN_START_X && mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 2][mino_x + 1] == 0 || screen[mino_y + 2][mino_x + 1] == 2 || screen[mino_y + 2][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 2][mino_x + 2] == 0 || screen[mino_y + 2][mino_x + 2] == 2 || screen[mino_y + 2][mino_x + 2] == SHADOW) && mino_x + 2 >= SCREEN_START_X && mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 2][mino_x + 3] == 0 || screen[mino_y + 2][mino_x + 3] == 2 || screen[mino_y + 2][mino_x + 3] == SHADOW) && mino_x + 3 >= SCREEN_START_X && mino_x + 3 <= SCREEN_END_X);
			break;
		case LEFT:
			flag = flag && ((screen[mino_y + 0][mino_x + 1] == 0 || screen[mino_y + 0][mino_x + 1] == 2 || screen[mino_y + 0][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 1] == 0 || screen[mino_y + 1][mino_x + 1] == 2 || screen[mino_y + 1][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 2][mino_x + 1] == 0 || screen[mino_y + 2][mino_x + 1] == 2 || screen[mino_y + 2][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 3][mino_x + 1] == 0 || screen[mino_y + 3][mino_x + 1] == 2 || screen[mino_y + 3][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			break;
		}
		break;
	case 'S':
		switch (direction)
		{
		case UP:
			flag = flag && ((screen[mino_y + 0][mino_x + 1] == 0 || screen[mino_y + 0][mino_x + 1] == 2 || screen[mino_y + 0][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 0][mino_x + 2] == 0 || screen[mino_y + 0][mino_x + 2] == 2 || screen[mino_y + 0][mino_x + 2] == SHADOW) && mino_x + 2 >= SCREEN_START_X && mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 0] == 0 || screen[mino_y + 1][mino_x + 0] == 2 || screen[mino_y + 1][mino_x + 0] == SHADOW) && mino_x + 0 >= SCREEN_START_X && mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 1] == 0 || screen[mino_y + 1][mino_x + 1] == 2 || screen[mino_y + 1][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			break;
		case RIGHT:
			flag = flag && ((screen[mino_y + 0][mino_x + 1] == 0 || screen[mino_y + 0][mino_x + 1] == 2 || screen[mino_y + 0][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 1] == 0 || screen[mino_y + 1][mino_x + 1] == 2 || screen[mino_y + 1][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 2] == 0 || screen[mino_y + 1][mino_x + 2] == 2 || screen[mino_y + 1][mino_x + 2] == SHADOW) && mino_x + 2 >= SCREEN_START_X && mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 2][mino_x + 2] == 0 || screen[mino_y + 2][mino_x + 2] == 2 || screen[mino_y + 2][mino_x + 2] == SHADOW) && mino_x + 2 >= SCREEN_START_X && mino_x + 2 <= SCREEN_END_X);
			break;
		case DOWN:
			flag = flag && ((screen[mino_y + 1][mino_x + 1] == 0 || screen[mino_y + 1][mino_x + 1] == 2 || screen[mino_y + 1][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 2] == 0 || screen[mino_y + 1][mino_x + 2] == 2 || screen[mino_y + 1][mino_x + 2] == SHADOW) && mino_x + 2 >= SCREEN_START_X && mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 2][mino_x + 0] == 0 || screen[mino_y + 2][mino_x + 0] == 2 || screen[mino_y + 2][mino_x + 0] == SHADOW) && mino_x + 0 >= SCREEN_START_X && mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 2][mino_x + 1] == 0 || screen[mino_y + 2][mino_x + 1] == 2 || screen[mino_y + 2][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			break;
		case LEFT:
			flag = flag && ((screen[mino_y + 0][mino_x + 0] == 0 || screen[mino_y + 0][mino_x + 0] == 2 || screen[mino_y + 0][mino_x + 0] == SHADOW) && mino_x + 0 >= SCREEN_START_X && mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 0] == 0 || screen[mino_y + 1][mino_x + 0] == 2 || screen[mino_y + 1][mino_x + 0] == SHADOW) && mino_x + 0 >= SCREEN_START_X && mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 1] == 0 || screen[mino_y + 1][mino_x + 1] == 2 || screen[mino_y + 1][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 2][mino_x + 1] == 0 || screen[mino_y + 2][mino_x + 1] == 2 || screen[mino_y + 2][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			break;
		}
		break;
	case 'Z':
		switch (direction)
		{
		case UP:
			flag = flag && ((screen[mino_y + 0][mino_x + 0] == 0 || screen[mino_y + 0][mino_x + 0] == 2 || screen[mino_y + 0][mino_x + 0] == SHADOW) && mino_x + 0 >= SCREEN_START_X && mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 0][mino_x + 1] == 0 || screen[mino_y + 0][mino_x + 1] == 2 || screen[mino_y + 0][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 1] == 0 || screen[mino_y + 1][mino_x + 1] == 2 || screen[mino_y + 1][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 2] == 0 || screen[mino_y + 1][mino_x + 2] == 2 || screen[mino_y + 1][mino_x + 2] == SHADOW) && mino_x + 2 >= SCREEN_START_X && mino_x + 2 <= SCREEN_END_X);
			break;
		case RIGHT:
			flag = flag && ((screen[mino_y + 0][mino_x + 2] == 0 || screen[mino_y + 0][mino_x + 2] == 2 || screen[mino_y + 0][mino_x + 2] == SHADOW) && mino_x + 2 >= SCREEN_START_X && mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 1] == 0 || screen[mino_y + 1][mino_x + 1] == 2 || screen[mino_y + 1][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 2] == 0 || screen[mino_y + 1][mino_x + 2] == 2 || screen[mino_y + 1][mino_x + 2] == SHADOW) && mino_x + 2 >= SCREEN_START_X && mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 2][mino_x + 1] == 0 || screen[mino_y + 2][mino_x + 1] == 2 || screen[mino_y + 2][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			break;
		case DOWN:
			flag = flag && ((screen[mino_y + 1][mino_x + 0] == 0 || screen[mino_y + 1][mino_x + 0] == 2 || screen[mino_y + 1][mino_x + 0] == SHADOW) && mino_x + 0 >= SCREEN_START_X && mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 1] == 0 || screen[mino_y + 1][mino_x + 1] == 2 || screen[mino_y + 1][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 2][mino_x + 1] == 0 || screen[mino_y + 2][mino_x + 1] == 2 || screen[mino_y + 2][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 2][mino_x + 2] == 0 || screen[mino_y + 2][mino_x + 2] == 2 || screen[mino_y + 2][mino_x + 2] == SHADOW) && mino_x + 2 >= SCREEN_START_X && mino_x + 2 <= SCREEN_END_X);
			break;
		case LEFT:
			flag = flag && ((screen[mino_y + 0][mino_x + 1] == 0 || screen[mino_y + 0][mino_x + 1] == 2 || screen[mino_y + 0][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 0] == 0 || screen[mino_y + 1][mino_x + 0] == 2 || screen[mino_y + 1][mino_x + 0] == SHADOW) && mino_x + 0 >= SCREEN_START_X && mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 1] == 0 || screen[mino_y + 1][mino_x + 1] == 2 || screen[mino_y + 1][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 2][mino_x + 0] == 0 || screen[mino_y + 2][mino_x + 0] == 2 || screen[mino_y + 2][mino_x + 0] == SHADOW) && mino_x + 0 >= SCREEN_START_X && mino_x + 0 <= SCREEN_END_X);
			break;
		}
		break;
	case 'T':
		switch (direction)
		{
		case UP:
			flag = flag && ((screen[mino_y + 0][mino_x + 1] == 0 || screen[mino_y + 0][mino_x + 1] == 2 || screen[mino_y + 0][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 0] == 0 || screen[mino_y + 1][mino_x + 0] == 2 || screen[mino_y + 1][mino_x + 0] == SHADOW) && mino_x + 0 >= SCREEN_START_X && mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 1] == 0 || screen[mino_y + 1][mino_x + 1] == 2 || screen[mino_y + 1][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 2] == 0 || screen[mino_y + 1][mino_x + 2] == 2 || screen[mino_y + 1][mino_x + 2] == SHADOW) && mino_x + 2 >= SCREEN_START_X && mino_x + 2 <= SCREEN_END_X);
			break;
		case RIGHT:
			flag = flag && ((screen[mino_y + 0][mino_x + 1] == 0 || screen[mino_y + 0][mino_x + 1] == 2 || screen[mino_y + 0][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 1] == 0 || screen[mino_y + 1][mino_x + 1] == 2 || screen[mino_y + 1][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 2] == 0 || screen[mino_y + 1][mino_x + 2] == 2 || screen[mino_y + 1][mino_x + 2] == SHADOW) && mino_x + 2 >= SCREEN_START_X && mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 2][mino_x + 1] == 0 || screen[mino_y + 2][mino_x + 1] == 2 || screen[mino_y + 2][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			break;
		case DOWN:
			flag = flag && ((screen[mino_y + 1][mino_x + 0] == 0 || screen[mino_y + 1][mino_x + 0] == 2 || screen[mino_y + 1][mino_x + 0] == SHADOW) && mino_x + 0 >= SCREEN_START_X && mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 1] == 0 || screen[mino_y + 1][mino_x + 1] == 2 || screen[mino_y + 1][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 2] == 0 || screen[mino_y + 1][mino_x + 2] == 2 || screen[mino_y + 1][mino_x + 2] == SHADOW) && mino_x + 2 >= SCREEN_START_X && mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 2][mino_x + 1] == 0 || screen[mino_y + 2][mino_x + 1] == 2 || screen[mino_y + 2][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			break;
		case LEFT:
			flag = flag && ((screen[mino_y + 0][mino_x + 1] == 0 || screen[mino_y + 0][mino_x + 1] == 2 || screen[mino_y + 0][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 0] == 0 || screen[mino_y + 1][mino_x + 0] == 2 || screen[mino_y + 1][mino_x + 0] == SHADOW) && mino_x + 0 >= SCREEN_START_X && mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 1] == 0 || screen[mino_y + 1][mino_x + 1] == 2 || screen[mino_y + 1][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 2][mino_x + 1] == 0 || screen[mino_y + 2][mino_x + 1] == 2 || screen[mino_y + 2][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			break;
		}
		break;
	case 'J':
		switch (direction)
		{
		case UP:
			flag = flag && ((screen[mino_y + 0][mino_x + 0] == 0 || screen[mino_y + 0][mino_x + 0] == 2 || screen[mino_y + 0][mino_x + 0] == SHADOW) && mino_x + 0 >= SCREEN_START_X && mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 0] == 0 || screen[mino_y + 1][mino_x + 0] == 2 || screen[mino_y + 1][mino_x + 0] == SHADOW) && mino_x + 0 >= SCREEN_START_X && mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 1] == 0 || screen[mino_y + 1][mino_x + 1] == 2 || screen[mino_y + 1][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 2] == 0 || screen[mino_y + 1][mino_x + 2] == 2 || screen[mino_y + 1][mino_x + 2] == SHADOW) && mino_x + 2 >= SCREEN_START_X && mino_x + 2 <= SCREEN_END_X);
			break;
		case RIGHT:
			flag = flag && ((screen[mino_y + 0][mino_x + 1] == 0 || screen[mino_y + 0][mino_x + 1] == 2 || screen[mino_y + 0][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 0][mino_x + 2] == 0 || screen[mino_y + 0][mino_x + 2] == 2 || screen[mino_y + 0][mino_x + 2] == SHADOW) && mino_x + 2 >= SCREEN_START_X && mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 1] == 0 || screen[mino_y + 1][mino_x + 1] == 2 || screen[mino_y + 1][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 2][mino_x + 1] == 0 || screen[mino_y + 2][mino_x + 1] == 2 || screen[mino_y + 2][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			break;
		case DOWN:
			flag = flag && ((screen[mino_y + 1][mino_x + 0] == 0 || screen[mino_y + 1][mino_x + 0] == 2 || screen[mino_y + 1][mino_x + 0] == SHADOW) && mino_x + 0 >= SCREEN_START_X && mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 1] == 0 || screen[mino_y + 1][mino_x + 1] == 2 || screen[mino_y + 1][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 2] == 0 || screen[mino_y + 1][mino_x + 2] == 2 || screen[mino_y + 1][mino_x + 2] == SHADOW) && mino_x + 2 >= SCREEN_START_X && mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 2][mino_x + 2] == 0 || screen[mino_y + 2][mino_x + 2] == 2 || screen[mino_y + 2][mino_x + 2] == SHADOW) && mino_x + 2 >= SCREEN_START_X && mino_x + 2 <= SCREEN_END_X);
			break;
		case LEFT:
			flag = flag && ((screen[mino_y + 0][mino_x + 1] == 0 || screen[mino_y + 0][mino_x + 1] == 2 || screen[mino_y + 0][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 1] == 0 || screen[mino_y + 1][mino_x + 1] == 2 || screen[mino_y + 1][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 2][mino_x + 0] == 0 || screen[mino_y + 2][mino_x + 0] == 2 || screen[mino_y + 2][mino_x + 0] == SHADOW) && mino_x + 0 >= SCREEN_START_X && mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 2][mino_x + 1] == 0 || screen[mino_y + 2][mino_x + 1] == 2 || screen[mino_y + 2][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			break;
		}
		break;
	case 'L':
		switch (direction)
		{
		case UP:
			flag = flag && ((screen[mino_y + 0][mino_x + 2] == 0 || screen[mino_y + 0][mino_x + 2] == 2 || screen[mino_y + 0][mino_x + 2] == SHADOW) && mino_x + 2 >= SCREEN_START_X && mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 0] == 0 || screen[mino_y + 1][mino_x + 0] == 2 || screen[mino_y + 1][mino_x + 0] == SHADOW) && mino_x + 0 >= SCREEN_START_X && mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 1] == 0 || screen[mino_y + 1][mino_x + 1] == 2 || screen[mino_y + 1][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 2] == 0 || screen[mino_y + 1][mino_x + 2] == 2 || screen[mino_y + 1][mino_x + 2] == SHADOW) && mino_x + 2 >= SCREEN_START_X && mino_x + 2 <= SCREEN_END_X);
			break;
		case RIGHT:
			flag = flag && ((screen[mino_y + 0][mino_x + 1] == 0 || screen[mino_y + 0][mino_x + 1] == 2 || screen[mino_y + 0][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 1] == 0 || screen[mino_y + 1][mino_x + 1] == 2 || screen[mino_y + 1][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 2][mino_x + 1] == 0 || screen[mino_y + 2][mino_x + 1] == 2 || screen[mino_y + 2][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 2][mino_x + 2] == 0 || screen[mino_y + 2][mino_x + 2] == 2 || screen[mino_y + 2][mino_x + 2] == SHADOW) && mino_x + 2 >= SCREEN_START_X && mino_x + 2 <= SCREEN_END_X);
			break;
		case DOWN:
			flag = flag && ((screen[mino_y + 1][mino_x + 0] == 0 || screen[mino_y + 1][mino_x + 0] == 2 || screen[mino_y + 1][mino_x + 0] == SHADOW) && mino_x + 0 >= SCREEN_START_X && mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 1] == 0 || screen[mino_y + 1][mino_x + 1] == 2 || screen[mino_y + 1][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 2] == 0 || screen[mino_y + 1][mino_x + 2] == 2 || screen[mino_y + 1][mino_x + 2] == SHADOW) && mino_x + 2 >= SCREEN_START_X && mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 2][mino_x + 0] == 0 || screen[mino_y + 2][mino_x + 0] == 2 || screen[mino_y + 2][mino_x + 0] == SHADOW) && mino_x + 0 >= SCREEN_START_X && mino_x + 0 <= SCREEN_END_X);
			break;
		case LEFT:
			flag = flag && ((screen[mino_y + 0][mino_x + 0] == 0 || screen[mino_y + 0][mino_x + 0] == 2 || screen[mino_y + 0][mino_x + 0] == SHADOW) && mino_x + 0 >= SCREEN_START_X && mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 0][mino_x + 1] == 0 || screen[mino_y + 0][mino_x + 1] == 2 || screen[mino_y + 0][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 1][mino_x + 1] == 0 || screen[mino_y + 1][mino_x + 1] == 2 || screen[mino_y + 1][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[mino_y + 2][mino_x + 1] == 0 || screen[mino_y + 2][mino_x + 1] == 2 || screen[mino_y + 2][mino_x + 1] == SHADOW) && mino_x + 1 >= SCREEN_START_X && mino_x + 1 <= SCREEN_END_X);
			break;
		}
		break;
	default:
		break;
	}

	return flag;
}


struct FallingMino Spin(struct FallingMino fallingmino, int count, int screen[][100])
{
	DeleteMino(fallingmino.mino_x, fallingmino.mino_y, fallingmino.shape, fallingmino.direction, screen);

	bool flag = false;

	switch (fallingmino.shape)
	{
	case 'I':
		if (count == 1)
		{
			switch (fallingmino.direction)
			{
			case UP:
				flag = IsMinoSetHere(fallingmino.mino_x - 2, fallingmino.mino_y + 0, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 2;
					fallingmino.piece_x[2] = fallingmino.mino_x + 2;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 3;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 0, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += 1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 2;
					fallingmino.piece_x[2] = fallingmino.mino_x + 2;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 3;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 2, fallingmino.mino_y + 1, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -2;
					fallingmino.mino_y += 1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 2;
					fallingmino.piece_x[2] = fallingmino.mino_x + 2;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 3;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y - 2, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 2;
					fallingmino.piece_x[2] = fallingmino.mino_x + 2;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 3;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				break;
			case RIGHT:

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 0, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 3;

					fallingmino.piece_y[1] = fallingmino.mino_y + 2;
					fallingmino.piece_y[2] = fallingmino.mino_y + 2;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 2, fallingmino.mino_y + 0, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += 2;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 3;

					fallingmino.piece_y[1] = fallingmino.mino_y + 2;
					fallingmino.piece_y[2] = fallingmino.mino_y + 2;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y - 2, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 3;

					fallingmino.piece_y[1] = fallingmino.mino_y + 2;
					fallingmino.piece_y[2] = fallingmino.mino_y + 2;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 2, fallingmino.mino_y + 1, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += 2;
					fallingmino.mino_y += 1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 3;

					fallingmino.piece_y[1] = fallingmino.mino_y + 2;
					fallingmino.piece_y[2] = fallingmino.mino_y + 2;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case DOWN:

				flag = IsMinoSetHere(fallingmino.mino_x + 2, fallingmino.mino_y + 0, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 2;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 3;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 0, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 3;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 2, fallingmino.mino_y - 1, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 2;
					fallingmino.mino_y += -1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 3;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 2, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 3;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case LEFT:

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 0, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 3;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 2, fallingmino.mino_y + 0, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += -2;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 3;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 2, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 3;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 2, fallingmino.mino_y - 1, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += -2;
					fallingmino.mino_y += -1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 3;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			default:
				break;
			}
		}
		else if (count == 3)
		{
			switch (fallingmino.direction)
			{
			case UP:

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 0, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 3;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 2, fallingmino.mino_y + 0, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 2;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 3;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y - 2, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 3;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 2, fallingmino.mino_y + 1, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 2;
					fallingmino.mino_y += +1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 3;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case RIGHT:

				flag = IsMinoSetHere(fallingmino.mino_x + 2, fallingmino.mino_y + 0, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += +2;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 3;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 0, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 3;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 2, fallingmino.mino_y - 1, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += +2;
					fallingmino.mino_y += -1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 3;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 2, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 3;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case DOWN:

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 0, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += 1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 2;
					fallingmino.piece_x[2] = fallingmino.mino_x + 2;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 3;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 2, fallingmino.mino_y + 0, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 2;
					fallingmino.piece_x[2] = fallingmino.mino_x + 2;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 3;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 2, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 2;
					fallingmino.piece_x[2] = fallingmino.mino_x + 2;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 3;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 2, fallingmino.mino_y - 1, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -2;
					fallingmino.mino_y += -1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 2;
					fallingmino.piece_x[2] = fallingmino.mino_x + 2;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 3;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case LEFT:

				flag = IsMinoSetHere(fallingmino.mino_x - 2, fallingmino.mino_y + 0, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += -2;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 3;

					fallingmino.piece_y[1] = fallingmino.mino_y + 2;
					fallingmino.piece_y[2] = fallingmino.mino_y + 2;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 0, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 3;

					fallingmino.piece_y[1] = fallingmino.mino_y + 2;
					fallingmino.piece_y[2] = fallingmino.mino_y + 2;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 2, fallingmino.mino_y + 1, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += -2;
					fallingmino.mino_y += 1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 3;

					fallingmino.piece_y[1] = fallingmino.mino_y + 2;
					fallingmino.piece_y[2] = fallingmino.mino_y + 2;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y - 2, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 3;

					fallingmino.piece_y[1] = fallingmino.mino_y + 2;
					fallingmino.piece_y[2] = fallingmino.mino_y + 2;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			default:
				break;
			}
		}
		break;
	case 'S':
		if (count == 1)
		{
			switch (fallingmino.direction)
			{
			case UP:

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 0, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y - 1, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += -1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y + 2, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 2, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case RIGHT:

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 0, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 2;
					fallingmino.piece_x[3] = fallingmino.mino_x + 0;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 1, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 2;
					fallingmino.piece_x[3] = fallingmino.mino_x + 0;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y - 2, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 2;
					fallingmino.piece_x[3] = fallingmino.mino_x + 0;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y - 2, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 2;
					fallingmino.piece_x[3] = fallingmino.mino_x + 0;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case DOWN:

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 0, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y - 1, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += -1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y + 2, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 2, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case LEFT:

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 0, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 2;
					fallingmino.piece_x[3] = fallingmino.mino_x + 0;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 0;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 1, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 2;
					fallingmino.piece_x[3] = fallingmino.mino_x + 0;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 0;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y - 2, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 2;
					fallingmino.piece_x[3] = fallingmino.mino_x + 0;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 0;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y - 2, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 2;
					fallingmino.piece_x[3] = fallingmino.mino_x + 0;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 0;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			default:
				break;
			}
		}
		else if (count == 3)
		{
			switch (fallingmino.direction)
			{
			case UP:

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 0, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y - 1, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += -1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y + 2, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 2, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case RIGHT:

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 0, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 2;
					fallingmino.piece_x[3] = fallingmino.mino_x + 0;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 0;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 1, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 2;
					fallingmino.piece_x[3] = fallingmino.mino_x + 0;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 0;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y - 2, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 2;
					fallingmino.piece_x[3] = fallingmino.mino_x + 0;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 0;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y - 2, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 2;
					fallingmino.piece_x[3] = fallingmino.mino_x + 0;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 0;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case DOWN:

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 0, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y - 1, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += -1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y + 2, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y - 2, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case LEFT:

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 0, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 2;
					fallingmino.piece_x[3] = fallingmino.mino_x + 0;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 1, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 2;
					fallingmino.piece_x[3] = fallingmino.mino_x + 0;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y - 2, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 2;
					fallingmino.piece_x[3] = fallingmino.mino_x + 0;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y - 2, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 2;
					fallingmino.piece_x[3] = fallingmino.mino_x + 0;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			default:
				break;
			}
		}
		break;
	case 'Z':
		if (count == 1)
		{
			switch (fallingmino.direction)
			{
			case UP:

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 0, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 2;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y - 1, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += -1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 2;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y + 2, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 2;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 2, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 2;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case RIGHT:

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 0, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 1, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y - 2, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y - 2, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case DOWN:

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 0, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 0;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y - 1, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += -1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 0;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y + 2, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 0;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 2, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 0;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case LEFT:

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 0, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 0;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 1, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 0;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y - 2, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 0;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y - 2, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 0;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			default:
				break;
			}
		}
		else if (count == 3)
		{
			switch (fallingmino.direction)
			{
			case UP:

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 0, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += +1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 0;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 1, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += +1;
					fallingmino.mino_y += 1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 0;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y + 2, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += +2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 0;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 2, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += +1;
					fallingmino.mino_y += +2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 0;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case RIGHT:

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 0, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 0;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 1, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 0;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y - 2, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 0;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y - 2, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 0;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case DOWN:

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 0, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 2;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y - 1, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += -1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 2;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y + 2, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 2;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 2, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 2;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case LEFT:

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 0, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 1, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y - 2, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y - 2, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			default:
				break;
			}
		}
		break;
	case 'T':
		if (count == 1)
		{
			switch (fallingmino.direction)
			{
			case UP:

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 0, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					T_Spin_Mini = true;
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y - 1, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += -1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y + 2, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 2, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case RIGHT:

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 0, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					T_Spin_Mini = true;
					fallingmino.direction = DOWN;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 1, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y - 2, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y - 2, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case DOWN:

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 0, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					T_Spin_Mini = true;
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y - 1, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += -1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y + 2, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 2, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case LEFT:

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 0, fallingmino.shape, UP, screen);

				if (flag)
				{
					T_Spin_Mini = true;
					fallingmino.direction = UP;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 1, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y + 2, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y - 2, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			default:
				break;
			}
		}
		else if (count == 3)
		{
			switch (fallingmino.direction)
			{
			case UP:

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 0, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					T_Spin_Mini = true;
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y - 1, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += -1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y + 2, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 2, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case RIGHT:

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 0, fallingmino.shape, UP, screen);

				if (flag)
				{
					T_Spin_Mini = true;
					fallingmino.direction = UP;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 1, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y - 2, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y - 2, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case DOWN:

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 0, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					T_Spin_Mini = true;
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 1, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y - 2, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y - 2, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case LEFT:

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 0, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					T_Spin_Mini = true;
					fallingmino.direction = DOWN;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 1, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y - 2, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y - 2, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			default:
				break;
			}
		}
		break;
	case 'J':
		if (count == 1)
		{
			switch (fallingmino.direction)
			{
			case UP:

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 0, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 2;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 0;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y - 1, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += -1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 2;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 0;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y + 2, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 2;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 0;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 2, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 2;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 0;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case RIGHT:

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 0, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 0;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 1, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 0;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y - 2, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 0;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y - 2, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 0;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case DOWN:

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 0, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 0;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y - 1, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += -1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 0;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y + 2, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 0;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case LEFT:

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 0, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 1, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y - 2, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y - 2, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			default:
				break;
			}
		}
		else if (count == 3)
		{
			switch (fallingmino.direction)
			{
			case UP:

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 0, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 0;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y - 1, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += -1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 0;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y + 2, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 0;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 2, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 0;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case RIGHT:

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 0, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 1, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y - 2, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y - 2, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case DOWN:

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 0, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 2;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 0;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y - 1, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += -1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 2;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 0;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y + 2, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 2;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 0;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 2, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 2;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 0;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case LEFT:

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 0, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 1, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y - 2, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y - 2, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			default:
				break;
			}
		}
		break;
	case 'L':
		if (count == 1)
		{
			switch (fallingmino.direction)
			{
			case UP:

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 0, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y - 1, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += -1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y + 2, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 2, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case RIGHT:

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 0, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 0;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 1, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 0;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y - 2, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 0;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y - 2, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 0;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case DOWN:

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 0, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 0;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y - 1, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += -1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 0;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y + 2, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 0;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 2, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 0;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case LEFT:

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 0, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 2;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 1, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 2;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y - 2, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 2;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y - 2, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 2;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			default:
				break;
			}
		}
		else if (count == 3)
		{
			switch (fallingmino.direction)
			{
			case UP:

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 0, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 0;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y - 1, fallingmino.shape, LEFT, screen);


				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += -1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 0;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y - 2, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 0;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y - 2, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 1;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 0;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case RIGHT:

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 0, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 2;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 1, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 2;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y + 2, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 2;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 1, fallingmino.mino_y + 2, fallingmino.shape, UP, screen);

				if (flag)
				{
					fallingmino.direction = UP;
					fallingmino.mino_x += 1;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 2;
					fallingmino.piece_x[2] = fallingmino.mino_x + 0;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 1;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case DOWN:

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 0, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y - 1, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += -1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y + 2, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 2, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 1;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 1;
					fallingmino.piece_x[4] = fallingmino.mino_x + 2;

					fallingmino.piece_y[1] = fallingmino.mino_y + 0;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 2;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			case LEFT:

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 0, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 0;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 0;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 1, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 1;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 0;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y - 2, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 0;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y - 2, fallingmino.shape, DOWN, screen);

				if (flag)
				{
					fallingmino.direction = DOWN; drop_count = drop_count < 30 ? 30 : drop_count;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += -2;
					fallingmino.piece_x[1] = fallingmino.mino_x + 0;
					fallingmino.piece_x[2] = fallingmino.mino_x + 1;
					fallingmino.piece_x[3] = fallingmino.mino_x + 2;
					fallingmino.piece_x[4] = fallingmino.mino_x + 0;

					fallingmino.piece_y[1] = fallingmino.mino_y + 1;
					fallingmino.piece_y[2] = fallingmino.mino_y + 1;
					fallingmino.piece_y[3] = fallingmino.mino_y + 1;
					fallingmino.piece_y[4] = fallingmino.mino_y + 2;
					drop_count = drop_count < 30 ? 30 : drop_count; return fallingmino;
				}
				break;
			default:
				break;
			}
		}
		break;

	default:
		break;
	}

	return fallingmino;
}


void erase_shadow(int screen[][100])
{
	for (int i = SCREEN_START_X; i <= SCREEN_END_X; i++)
	{
		for (int j = 1; j <= SCREEN_END_Y; j++)
		{
			if (screen[j][i] == SHADOW)
				screen[j][i] = j < 3 ? 0 : 2;
		}
	}

	return;
}


void shadow_mino(struct FallingMino fallingmino, int screen[][100])
{
	for (int i = 0; i <= SCREEN_END_Y; i++)
	{
		bool flag = false;

		for (int j = 1; j <= 4; j++)
		{
			if (fallingmino.piece_x[j] == fallingmino.piece_x[1] && fallingmino.piece_y[j] + i == fallingmino.piece_y[1]) continue;
			if (fallingmino.piece_x[j] == fallingmino.piece_x[2] && fallingmino.piece_y[j] + i == fallingmino.piece_y[2]) continue;
			if (fallingmino.piece_x[j] == fallingmino.piece_x[3] && fallingmino.piece_y[j] + i == fallingmino.piece_y[3]) continue;
			if (fallingmino.piece_x[j] == fallingmino.piece_x[4] && fallingmino.piece_y[j] + i == fallingmino.piece_y[4]) continue;

			if (screen[i + fallingmino.piece_y[j]][fallingmino.piece_x[j]] != 2 && screen[i + fallingmino.piece_y[j]][fallingmino.piece_x[j]] != 0 && screen[i + fallingmino.piece_y[j]][fallingmino.piece_x[j]] != SHADOW) flag = true;

		}

		if (flag)
		{
			switch (fallingmino.shape)
			{
			case 'I':
				SetMino(fallingmino.mino_x, fallingmino.mino_y + i - 1, SHADOW_I, fallingmino.direction, screen);
				break;
			case 'S':
				SetMino(fallingmino.mino_x, fallingmino.mino_y + i - 1, SHADOW_S, fallingmino.direction, screen);
				break;
			case 'Z':
				SetMino(fallingmino.mino_x, fallingmino.mino_y + i - 1, SHADOW_Z, fallingmino.direction, screen);
				break;
			case 'O':
				SetMino(fallingmino.mino_x, fallingmino.mino_y + i - 1, SHADOW_O, fallingmino.direction, screen);
				break;
			case 'T':
				SetMino(fallingmino.mino_x, fallingmino.mino_y + i - 1, SHADOW_T, fallingmino.direction, screen);
				break;
			case 'J':
				SetMino(fallingmino.mino_x, fallingmino.mino_y + i - 1, SHADOW_J, fallingmino.direction, screen);
				break;
			case 'L':
				SetMino(fallingmino.mino_x, fallingmino.mino_y + i - 1, SHADOW_L, fallingmino.direction, screen);
				break;
			default:
				break;
			}
			break;
		}
	}

	return;
}


struct FallingMino Turn_Right(struct FallingMino fallingmino, int count, int screen[][100])
{
	erase_shadow(screen);

	bool flag = true;
	DeleteMino(fallingmino.mino_x, fallingmino.mino_y, fallingmino.shape, fallingmino.direction, screen);


	switch ((fallingmino.direction + count) % 4)
	{

	case UP:
		switch (fallingmino.shape)
		{
		case 'I':
			for (int i = 1; i <= 4; i++)
			{
				flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + i - 1] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + i - 1] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + i - 1] == SHADOW) && fallingmino.mino_x + i - 1 >= SCREEN_START_X && fallingmino.mino_x + i - 1 <= SCREEN_END_X);
			}
			break;
		case 'Z':
			flag = flag && ((screen[fallingmino.mino_y + 0][fallingmino.mino_x + 0] == 0 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 0] == 2 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 0] == SHADOW) && fallingmino.mino_x + 0 >= SCREEN_START_X && fallingmino.mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == SHADOW) && fallingmino.mino_x + 2 >= SCREEN_START_X && fallingmino.mino_x + 2 <= SCREEN_END_X);
			break;
		case 'S':
			flag = flag && ((screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 0][fallingmino.mino_x + 2] == 0 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 2] == 2 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 2] == SHADOW) && fallingmino.mino_x + 2 >= SCREEN_START_X && fallingmino.mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 0] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 0] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 0] == SHADOW) && fallingmino.mino_x + 0 >= SCREEN_START_X && fallingmino.mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			break;
		case 'O':
			flag = flag && ((screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 0][fallingmino.mino_x + 2] == 0 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 2] == 2 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 2] == SHADOW) && fallingmino.mino_x + 2 >= SCREEN_START_X && fallingmino.mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == SHADOW) && fallingmino.mino_x + 2 >= SCREEN_START_X && fallingmino.mino_x + 2 <= SCREEN_END_X);
			break;
		case 'T':
			flag = flag && ((screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 0] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 0] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 0] == SHADOW) && fallingmino.mino_x + 0 >= SCREEN_START_X && fallingmino.mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == SHADOW) && fallingmino.mino_x + 2 >= SCREEN_START_X && fallingmino.mino_x + 2 <= SCREEN_END_X);
			break;
		case 'L':
			flag = flag && ((screen[fallingmino.mino_y + 0][fallingmino.mino_x + 2] == 0 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 2] == 2 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 2] == SHADOW) && fallingmino.mino_x + 2 >= SCREEN_START_X && fallingmino.mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 0] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 0] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 0] == SHADOW) && fallingmino.mino_x + 0 >= SCREEN_START_X && fallingmino.mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == SHADOW) && fallingmino.mino_x + 2 >= SCREEN_START_X && fallingmino.mino_x + 2 <= SCREEN_END_X);
			break;
		case 'J':
			flag = flag && ((screen[fallingmino.mino_y + 0][fallingmino.mino_x + 0] == 0 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 0] == 2 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 0] == SHADOW) && fallingmino.mino_x + 0 >= SCREEN_START_X && fallingmino.mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 0] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 0] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 0] == SHADOW) && fallingmino.mino_x + 0 >= SCREEN_START_X && fallingmino.mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == SHADOW) && fallingmino.mino_x + 2 >= SCREEN_START_X && fallingmino.mino_x + 2 <= SCREEN_END_X);
			break;
		default:
			break;
		}
		break;
	case RIGHT:
		switch (fallingmino.shape)
		{
		case 'I':
			flag = flag && ((screen[fallingmino.mino_y + 0][fallingmino.mino_x + 2] == 0 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 2] == 2 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 2] == SHADOW) && fallingmino.mino_x + 2 >= SCREEN_START_X && fallingmino.mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == SHADOW) && fallingmino.mino_x + 2 >= SCREEN_START_X && fallingmino.mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 2][fallingmino.mino_x + 2] == 0 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 2] == 2 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 2] == SHADOW) && fallingmino.mino_x + 2 >= SCREEN_START_X && fallingmino.mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 3][fallingmino.mino_x + 2] == 0 || screen[fallingmino.mino_y + 3][fallingmino.mino_x + 2] == 2 || screen[fallingmino.mino_y + 3][fallingmino.mino_x + 2] == SHADOW) && fallingmino.mino_x + 2 >= SCREEN_START_X && fallingmino.mino_x + 2 <= SCREEN_END_X);
			break;
		case 'Z':
			flag = flag && ((screen[fallingmino.mino_y + 0][fallingmino.mino_x + 2] == 0 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 2] == 2 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 2] == SHADOW) && fallingmino.mino_x + 2 >= SCREEN_START_X && fallingmino.mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == SHADOW) && fallingmino.mino_x + 2 >= SCREEN_START_X && fallingmino.mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			break;
		case 'S':
			flag = flag && ((screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == SHADOW) && fallingmino.mino_x + 2 >= SCREEN_START_X && fallingmino.mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 2][fallingmino.mino_x + 2] == 0 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 2] == 2 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 2] == SHADOW) && fallingmino.mino_x + 2 >= SCREEN_START_X && fallingmino.mino_x + 2 <= SCREEN_END_X);
			break;
		case 'O':
			flag = flag && ((screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 0][fallingmino.mino_x + 2] == 0 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 2] == 2 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 2] == SHADOW) && fallingmino.mino_x + 2 >= SCREEN_START_X && fallingmino.mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == SHADOW) && fallingmino.mino_x + 2 >= SCREEN_START_X && fallingmino.mino_x + 2 <= SCREEN_END_X);
			break;
		case 'T':
			flag = flag && ((screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == SHADOW) && fallingmino.mino_x + 2 >= SCREEN_START_X && fallingmino.mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			break;
		case 'L':
			flag = flag && ((screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 2][fallingmino.mino_x + 2] == 0 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 2] == 2 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 2] == SHADOW) && fallingmino.mino_x + 2 >= SCREEN_START_X && fallingmino.mino_x + 2 <= SCREEN_END_X);
			break;
		case 'J':
			flag = flag && ((screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 0][fallingmino.mino_x + 2] == 0 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 2] == 2 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 2] == SHADOW) && fallingmino.mino_x + 2 >= SCREEN_START_X && fallingmino.mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			break;
		default:
			break;
		}
		break;
	case DOWN:
		switch (fallingmino.shape)
		{
		case 'I':
			flag = flag && ((screen[fallingmino.mino_y + 2][fallingmino.mino_x + 0] == 0 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 0] == 2 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 0] == SHADOW) && fallingmino.mino_x + 0 >= SCREEN_START_X && fallingmino.mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 2][fallingmino.mino_x + 2] == 0 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 2] == 2 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 2] == SHADOW) && fallingmino.mino_x + 2 >= SCREEN_START_X && fallingmino.mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 2][fallingmino.mino_x + 3] == 0 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 3] == 2 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 3] == SHADOW) && fallingmino.mino_x + 3 >= SCREEN_START_X && fallingmino.mino_x + 3 <= SCREEN_END_X);
			break;
		case 'Z':
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 0] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 0] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 0] == SHADOW) && fallingmino.mino_x + 0 >= SCREEN_START_X && fallingmino.mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 2][fallingmino.mino_x + 2] == 0 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 2] == 2 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 2] == SHADOW) && fallingmino.mino_x + 2 >= SCREEN_START_X && fallingmino.mino_x + 2 <= SCREEN_END_X);
			break;
		case 'S':
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == SHADOW) && fallingmino.mino_x + 2 >= SCREEN_START_X && fallingmino.mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 2][fallingmino.mino_x + 0] == 0 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 0] == 2 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 0] == SHADOW) && fallingmino.mino_x + 0 >= SCREEN_START_X && fallingmino.mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			break;
		case 'O':
			flag = flag && ((screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 0][fallingmino.mino_x + 2] == 0 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 2] == 2 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 2] == SHADOW) && fallingmino.mino_x + 2 >= SCREEN_START_X && fallingmino.mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			break;
		case 'T':
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 0] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 0] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 0] == SHADOW) && fallingmino.mino_x + 0 >= SCREEN_START_X && fallingmino.mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == SHADOW) && fallingmino.mino_x + 2 >= SCREEN_START_X && fallingmino.mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			break;
		case 'L':
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 0] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 0] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 0] == SHADOW) && fallingmino.mino_x + 0 >= SCREEN_START_X && fallingmino.mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == SHADOW) && fallingmino.mino_x + 2 >= SCREEN_START_X && fallingmino.mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 2][fallingmino.mino_x + 0] == 0 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 0] == 2 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 0] == SHADOW) && fallingmino.mino_x + 0 >= SCREEN_START_X && fallingmino.mino_x + 0 <= SCREEN_END_X);
			break;
		case 'J':
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 0] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 0] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 0] == SHADOW) && fallingmino.mino_x + 0 >= SCREEN_START_X && fallingmino.mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == SHADOW) && fallingmino.mino_x + 2 >= SCREEN_START_X && fallingmino.mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 2][fallingmino.mino_x + 2] == 0 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 2] == 2 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 2] == SHADOW) && fallingmino.mino_x + 2 >= SCREEN_START_X && fallingmino.mino_x + 2 <= SCREEN_END_X);
			break;
		default:
			break;
		}
		break;
	case LEFT:
		switch (fallingmino.shape)
		{
		case 'I':
			flag = flag && ((screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 3][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 3][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 3][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			break;
		case 'Z':
			flag = flag && ((screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 0] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 0] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 0] == SHADOW) && fallingmino.mino_x + 0 >= SCREEN_START_X && fallingmino.mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 2][fallingmino.mino_x + 0] == 0 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 0] == 2 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 0] == SHADOW) && fallingmino.mino_x + 0 >= SCREEN_START_X && fallingmino.mino_x + 0 <= SCREEN_END_X);
			break;
		case 'S':
			flag = flag && ((screen[fallingmino.mino_y + 0][fallingmino.mino_x + 0] == 0 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 0] == 2 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 0] == SHADOW) && fallingmino.mino_x + 0 >= SCREEN_START_X && fallingmino.mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 0] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 0] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 0] == SHADOW) && fallingmino.mino_x + 0 >= SCREEN_START_X && fallingmino.mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			break;
		case 'O':
			flag = flag && ((screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 0][fallingmino.mino_x + 2] == 0 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 2] == 2 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 2] == SHADOW) && fallingmino.mino_x + 2 >= SCREEN_START_X && fallingmino.mino_x + 2 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 2] == SHADOW) && fallingmino.mino_x + 2 >= SCREEN_START_X && fallingmino.mino_x + 2 <= SCREEN_END_X);
			break;
		case 'T':
			flag = flag && ((screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 0] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 0] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 0] == SHADOW) && fallingmino.mino_x + 0 >= SCREEN_START_X && fallingmino.mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			break;
		case 'L':
			flag = flag && ((screen[fallingmino.mino_y + 0][fallingmino.mino_x + 0] == 0 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 0] == 2 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 0] == SHADOW) && fallingmino.mino_x + 0 >= SCREEN_START_X && fallingmino.mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			break;
		case 'J':
			flag = flag && ((screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 0][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 1][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 2][fallingmino.mino_x + 0] == 0 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 0] == 2 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 0] == SHADOW) && fallingmino.mino_x + 0 >= SCREEN_START_X && fallingmino.mino_x + 0 <= SCREEN_END_X);
			flag = flag && ((screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == SHADOW) && fallingmino.mino_x + 1 >= SCREEN_START_X && fallingmino.mino_x + 1 <= SCREEN_END_X);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}



	if (flag)
	{
		drop_count = drop_count < 30 ? 30 : drop_count;
		fallingmino.direction = (fallingmino.direction + count) % 4;

		if (fallingmino.direction == UP)
		{
			switch (fallingmino.shape)
			{
			case 'I':
				for (int i = 1; i <= 4; i++)
				{
					fallingmino.piece_x[i] = fallingmino.mino_x + i - 1;
					fallingmino.piece_y[i] = fallingmino.mino_y + 1;
				}
				break;
			case 'Z':
				fallingmino.piece_x[1] = fallingmino.mino_x + 0;
				fallingmino.piece_x[2] = fallingmino.mino_x + 1;
				fallingmino.piece_x[3] = fallingmino.mino_x + 1;
				fallingmino.piece_x[4] = fallingmino.mino_x + 2;

				fallingmino.piece_y[1] = fallingmino.mino_y + 0;
				fallingmino.piece_y[2] = fallingmino.mino_y + 0;
				fallingmino.piece_y[3] = fallingmino.mino_y + 1;
				fallingmino.piece_y[4] = fallingmino.mino_y + 1;
				break;
			case 'S':
				fallingmino.piece_x[1] = fallingmino.mino_x + 1;
				fallingmino.piece_x[2] = fallingmino.mino_x + 2;
				fallingmino.piece_x[3] = fallingmino.mino_x + 0;
				fallingmino.piece_x[4] = fallingmino.mino_x + 1;

				fallingmino.piece_y[1] = fallingmino.mino_y + 0;
				fallingmino.piece_y[2] = fallingmino.mino_y + 0;
				fallingmino.piece_y[3] = fallingmino.mino_y + 1;
				fallingmino.piece_y[4] = fallingmino.mino_y + 1;
				break;
			case 'O':
				fallingmino.piece_x[1] = fallingmino.mino_x + 1;
				fallingmino.piece_x[2] = fallingmino.mino_x + 2;
				fallingmino.piece_x[3] = fallingmino.mino_x + 1;
				fallingmino.piece_x[4] = fallingmino.mino_x + 2;

				fallingmino.piece_y[1] = fallingmino.mino_y + 0;
				fallingmino.piece_y[2] = fallingmino.mino_y + 0;
				fallingmino.piece_y[3] = fallingmino.mino_y + 1;
				fallingmino.piece_y[4] = fallingmino.mino_y + 1;
				break;
			case 'T':
				fallingmino.piece_x[1] = fallingmino.mino_x + 1;
				fallingmino.piece_x[2] = fallingmino.mino_x + 0;
				fallingmino.piece_x[3] = fallingmino.mino_x + 1;
				fallingmino.piece_x[4] = fallingmino.mino_x + 2;

				fallingmino.piece_y[1] = fallingmino.mino_y + 0;
				fallingmino.piece_y[2] = fallingmino.mino_y + 1;
				fallingmino.piece_y[3] = fallingmino.mino_y + 1;
				fallingmino.piece_y[4] = fallingmino.mino_y + 1;
				break;
			case 'L':
				fallingmino.piece_x[1] = fallingmino.mino_x + 2;
				fallingmino.piece_x[2] = fallingmino.mino_x + 0;
				fallingmino.piece_x[3] = fallingmino.mino_x + 1;
				fallingmino.piece_x[4] = fallingmino.mino_x + 2;

				fallingmino.piece_y[1] = fallingmino.mino_y + 0;
				fallingmino.piece_y[2] = fallingmino.mino_y + 1;
				fallingmino.piece_y[3] = fallingmino.mino_y + 1;
				fallingmino.piece_y[4] = fallingmino.mino_y + 1;
				break;
			case 'J':
				fallingmino.piece_x[1] = fallingmino.mino_x + 0;
				fallingmino.piece_x[2] = fallingmino.mino_x + 0;
				fallingmino.piece_x[3] = fallingmino.mino_x + 1;
				fallingmino.piece_x[4] = fallingmino.mino_x + 2;

				fallingmino.piece_y[1] = fallingmino.mino_y + 0;
				fallingmino.piece_y[2] = fallingmino.mino_y + 1;
				fallingmino.piece_y[3] = fallingmino.mino_y + 1;
				fallingmino.piece_y[4] = fallingmino.mino_y + 1;
				break;
			default:
				break;
			}
		}
		else if (fallingmino.direction == RIGHT)
		{
			switch (fallingmino.shape)
			{
			case 'I':
				fallingmino.piece_x[1] = fallingmino.mino_x + 2;
				fallingmino.piece_x[2] = fallingmino.mino_x + 2;
				fallingmino.piece_x[3] = fallingmino.mino_x + 2;
				fallingmino.piece_x[4] = fallingmino.mino_x + 2;

				fallingmino.piece_y[1] = fallingmino.mino_y + 0;
				fallingmino.piece_y[2] = fallingmino.mino_y + 1;
				fallingmino.piece_y[3] = fallingmino.mino_y + 2;
				fallingmino.piece_y[4] = fallingmino.mino_y + 3;
				break;
			case 'Z':
				fallingmino.piece_x[1] = fallingmino.mino_x + 2;
				fallingmino.piece_x[2] = fallingmino.mino_x + 1;
				fallingmino.piece_x[3] = fallingmino.mino_x + 2;
				fallingmino.piece_x[4] = fallingmino.mino_x + 1;

				fallingmino.piece_y[1] = fallingmino.mino_y + 0;
				fallingmino.piece_y[2] = fallingmino.mino_y + 1;
				fallingmino.piece_y[3] = fallingmino.mino_y + 1;
				fallingmino.piece_y[4] = fallingmino.mino_y + 2;
				break;
			case 'S':
				fallingmino.piece_x[1] = fallingmino.mino_x + 1;
				fallingmino.piece_x[2] = fallingmino.mino_x + 1;
				fallingmino.piece_x[3] = fallingmino.mino_x + 2;
				fallingmino.piece_x[4] = fallingmino.mino_x + 2;

				fallingmino.piece_y[1] = fallingmino.mino_y + 0;
				fallingmino.piece_y[2] = fallingmino.mino_y + 1;
				fallingmino.piece_y[3] = fallingmino.mino_y + 1;
				fallingmino.piece_y[4] = fallingmino.mino_y + 2;
				break;
			case 'O':
				fallingmino.piece_x[1] = fallingmino.mino_x + 1;
				fallingmino.piece_x[2] = fallingmino.mino_x + 2;
				fallingmino.piece_x[3] = fallingmino.mino_x + 1;
				fallingmino.piece_x[4] = fallingmino.mino_x + 2;

				fallingmino.piece_y[1] = fallingmino.mino_y + 0;
				fallingmino.piece_y[2] = fallingmino.mino_y + 0;
				fallingmino.piece_y[3] = fallingmino.mino_y + 1;
				fallingmino.piece_y[4] = fallingmino.mino_y + 1;
				break;
			case 'T':
				fallingmino.piece_x[1] = fallingmino.mino_x + 1;
				fallingmino.piece_x[2] = fallingmino.mino_x + 1;
				fallingmino.piece_x[3] = fallingmino.mino_x + 2;
				fallingmino.piece_x[4] = fallingmino.mino_x + 1;

				fallingmino.piece_y[1] = fallingmino.mino_y + 0;
				fallingmino.piece_y[2] = fallingmino.mino_y + 1;
				fallingmino.piece_y[3] = fallingmino.mino_y + 1;
				fallingmino.piece_y[4] = fallingmino.mino_y + 2;
				break;
			case 'L':
				fallingmino.piece_x[1] = fallingmino.mino_x + 1;
				fallingmino.piece_x[2] = fallingmino.mino_x + 1;
				fallingmino.piece_x[3] = fallingmino.mino_x + 1;
				fallingmino.piece_x[4] = fallingmino.mino_x + 2;

				fallingmino.piece_y[1] = fallingmino.mino_y + 0;
				fallingmino.piece_y[2] = fallingmino.mino_y + 1;
				fallingmino.piece_y[3] = fallingmino.mino_y + 2;
				fallingmino.piece_y[4] = fallingmino.mino_y + 2;
				break;
			case 'J':
				fallingmino.piece_x[1] = fallingmino.mino_x + 1;
				fallingmino.piece_x[2] = fallingmino.mino_x + 2;
				fallingmino.piece_x[3] = fallingmino.mino_x + 1;
				fallingmino.piece_x[4] = fallingmino.mino_x + 1;

				fallingmino.piece_y[1] = fallingmino.mino_y + 0;
				fallingmino.piece_y[2] = fallingmino.mino_y + 0;
				fallingmino.piece_y[3] = fallingmino.mino_y + 1;
				fallingmino.piece_y[4] = fallingmino.mino_y + 2;
				break;
			default:
				break;
			}
		}
		else if (fallingmino.direction == DOWN)
		{
			switch (fallingmino.shape)
			{
			case 'I':
				fallingmino.piece_x[1] = fallingmino.mino_x + 0;
				fallingmino.piece_x[2] = fallingmino.mino_x + 1;
				fallingmino.piece_x[3] = fallingmino.mino_x + 2;
				fallingmino.piece_x[4] = fallingmino.mino_x + 3;

				fallingmino.piece_y[1] = fallingmino.mino_y + 2;
				fallingmino.piece_y[2] = fallingmino.mino_y + 2;
				fallingmino.piece_y[3] = fallingmino.mino_y + 2;
				fallingmino.piece_y[4] = fallingmino.mino_y + 2;
				break;
			case 'Z':
				fallingmino.piece_x[1] = fallingmino.mino_x + 0;
				fallingmino.piece_x[2] = fallingmino.mino_x + 1;
				fallingmino.piece_x[3] = fallingmino.mino_x + 1;
				fallingmino.piece_x[4] = fallingmino.mino_x + 2;

				fallingmino.piece_y[1] = fallingmino.mino_y + 1;
				fallingmino.piece_y[2] = fallingmino.mino_y + 1;
				fallingmino.piece_y[3] = fallingmino.mino_y + 2;
				fallingmino.piece_y[4] = fallingmino.mino_y + 2;
				break;
			case 'S':
				fallingmino.piece_x[1] = fallingmino.mino_x + 1;
				fallingmino.piece_x[2] = fallingmino.mino_x + 2;
				fallingmino.piece_x[3] = fallingmino.mino_x + 0;
				fallingmino.piece_x[4] = fallingmino.mino_x + 1;

				fallingmino.piece_y[1] = fallingmino.mino_y + 1;
				fallingmino.piece_y[2] = fallingmino.mino_y + 1;
				fallingmino.piece_y[3] = fallingmino.mino_y + 2;
				fallingmino.piece_y[4] = fallingmino.mino_y + 2;
				break;
			case 'O':
				fallingmino.piece_x[1] = fallingmino.mino_x + 1;
				fallingmino.piece_x[2] = fallingmino.mino_x + 2;
				fallingmino.piece_x[3] = fallingmino.mino_x + 1;
				fallingmino.piece_x[4] = fallingmino.mino_x + 2;

				fallingmino.piece_y[1] = fallingmino.mino_y + 0;
				fallingmino.piece_y[2] = fallingmino.mino_y + 0;
				fallingmino.piece_y[3] = fallingmino.mino_y + 1;
				fallingmino.piece_y[4] = fallingmino.mino_y + 1;
				break;
			case 'T':
				fallingmino.piece_x[1] = fallingmino.mino_x + 0;
				fallingmino.piece_x[2] = fallingmino.mino_x + 1;
				fallingmino.piece_x[3] = fallingmino.mino_x + 2;
				fallingmino.piece_x[4] = fallingmino.mino_x + 1;

				fallingmino.piece_y[1] = fallingmino.mino_y + 1;
				fallingmino.piece_y[2] = fallingmino.mino_y + 1;
				fallingmino.piece_y[3] = fallingmino.mino_y + 1;
				fallingmino.piece_y[4] = fallingmino.mino_y + 2;
				break;
			case 'L':
				fallingmino.piece_x[1] = fallingmino.mino_x + 0;
				fallingmino.piece_x[2] = fallingmino.mino_x + 1;
				fallingmino.piece_x[3] = fallingmino.mino_x + 2;
				fallingmino.piece_x[4] = fallingmino.mino_x + 0;

				fallingmino.piece_y[1] = fallingmino.mino_y + 1;
				fallingmino.piece_y[2] = fallingmino.mino_y + 1;
				fallingmino.piece_y[3] = fallingmino.mino_y + 1;
				fallingmino.piece_y[4] = fallingmino.mino_y + 2;
				break;
			case 'J':
				fallingmino.piece_x[1] = fallingmino.mino_x + 0;
				fallingmino.piece_x[2] = fallingmino.mino_x + 1;
				fallingmino.piece_x[3] = fallingmino.mino_x + 2;
				fallingmino.piece_x[4] = fallingmino.mino_x + 2;

				fallingmino.piece_y[1] = fallingmino.mino_y + 1;
				fallingmino.piece_y[2] = fallingmino.mino_y + 1;
				fallingmino.piece_y[3] = fallingmino.mino_y + 1;
				fallingmino.piece_y[4] = fallingmino.mino_y + 2;
				break;
			default:
				break;
			}
		}
		else if (fallingmino.direction == LEFT)
		{
			switch (fallingmino.shape)
			{
			case 'I':
				fallingmino.piece_x[1] = fallingmino.mino_x + 1;
				fallingmino.piece_x[2] = fallingmino.mino_x + 1;
				fallingmino.piece_x[3] = fallingmino.mino_x + 1;
				fallingmino.piece_x[4] = fallingmino.mino_x + 1;

				fallingmino.piece_y[1] = fallingmino.mino_y + 0;
				fallingmino.piece_y[2] = fallingmino.mino_y + 1;
				fallingmino.piece_y[3] = fallingmino.mino_y + 2;
				fallingmino.piece_y[4] = fallingmino.mino_y + 3;
				break;
			case 'Z':
				fallingmino.piece_x[1] = fallingmino.mino_x + 1;
				fallingmino.piece_x[2] = fallingmino.mino_x + 0;
				fallingmino.piece_x[3] = fallingmino.mino_x + 1;
				fallingmino.piece_x[4] = fallingmino.mino_x + 0;

				fallingmino.piece_y[1] = fallingmino.mino_y + 0;
				fallingmino.piece_y[2] = fallingmino.mino_y + 1;
				fallingmino.piece_y[3] = fallingmino.mino_y + 1;
				fallingmino.piece_y[4] = fallingmino.mino_y + 2;
				break;
			case 'S':
				fallingmino.piece_x[1] = fallingmino.mino_x + 0;
				fallingmino.piece_x[2] = fallingmino.mino_x + 0;
				fallingmino.piece_x[3] = fallingmino.mino_x + 1;
				fallingmino.piece_x[4] = fallingmino.mino_x + 1;

				fallingmino.piece_y[1] = fallingmino.mino_y + 0;
				fallingmino.piece_y[2] = fallingmino.mino_y + 1;
				fallingmino.piece_y[3] = fallingmino.mino_y + 1;
				fallingmino.piece_y[4] = fallingmino.mino_y + 2;
				break;
			case 'O':
				fallingmino.piece_x[1] = fallingmino.mino_x + 1;
				fallingmino.piece_x[2] = fallingmino.mino_x + 2;
				fallingmino.piece_x[3] = fallingmino.mino_x + 1;
				fallingmino.piece_x[4] = fallingmino.mino_x + 2;

				fallingmino.piece_y[1] = fallingmino.mino_y + 0;
				fallingmino.piece_y[2] = fallingmino.mino_y + 0;
				fallingmino.piece_y[3] = fallingmino.mino_y + 1;
				fallingmino.piece_y[4] = fallingmino.mino_y + 1;
				break;
			case 'T':
				fallingmino.piece_x[1] = fallingmino.mino_x + 1;
				fallingmino.piece_x[2] = fallingmino.mino_x + 0;
				fallingmino.piece_x[3] = fallingmino.mino_x + 1;
				fallingmino.piece_x[4] = fallingmino.mino_x + 1;

				fallingmino.piece_y[1] = fallingmino.mino_y + 0;
				fallingmino.piece_y[2] = fallingmino.mino_y + 1;
				fallingmino.piece_y[3] = fallingmino.mino_y + 1;
				fallingmino.piece_y[4] = fallingmino.mino_y + 2;
				break;
			case 'L':
				fallingmino.piece_x[1] = fallingmino.mino_x + 0;
				fallingmino.piece_x[2] = fallingmino.mino_x + 1;
				fallingmino.piece_x[3] = fallingmino.mino_x + 1;
				fallingmino.piece_x[4] = fallingmino.mino_x + 1;

				fallingmino.piece_y[1] = fallingmino.mino_y + 0;
				fallingmino.piece_y[2] = fallingmino.mino_y + 0;
				fallingmino.piece_y[3] = fallingmino.mino_y + 1;
				fallingmino.piece_y[4] = fallingmino.mino_y + 2;
				break;
			case 'J':
				fallingmino.piece_x[1] = fallingmino.mino_x + 1;
				fallingmino.piece_x[2] = fallingmino.mino_x + 1;
				fallingmino.piece_x[3] = fallingmino.mino_x + 0;
				fallingmino.piece_x[4] = fallingmino.mino_x + 1;

				fallingmino.piece_y[1] = fallingmino.mino_y + 0;
				fallingmino.piece_y[2] = fallingmino.mino_y + 1;
				fallingmino.piece_y[3] = fallingmino.mino_y + 2;
				fallingmino.piece_y[4] = fallingmino.mino_y + 2;
				break;
			default:
				break;
			}
		}
	}
	else
	{
		fallingmino = Spin(fallingmino, count, screen);
	}



	if (fallingmino.shape == 'T')
	{
		if ((int)(screen[fallingmino.mino_y + 0][fallingmino.mino_x + 0] != 0 && screen[fallingmino.mino_y + 0][fallingmino.mino_x + 0] != 2 && screen[fallingmino.mino_y + 0][fallingmino.mino_x + 0] != SHADOW) + (int)(screen[fallingmino.mino_y + 2][fallingmino.mino_x + 0] != 0 && screen[fallingmino.mino_y + 2][fallingmino.mino_x + 0] != 2 && screen[fallingmino.mino_y + 2][fallingmino.mino_x + 0] != SHADOW) + (int)(screen[fallingmino.mino_y + 0][fallingmino.mino_x + 2] != 0 && screen[fallingmino.mino_y + 0][fallingmino.mino_x + 2] != 2 && screen[fallingmino.mino_y + 0][fallingmino.mino_x + 2] != SHADOW) + (int)(screen[fallingmino.mino_y + 2][fallingmino.mino_x + 2] != 0 && screen[fallingmino.mino_y + 2][fallingmino.mino_x + 2] != 2 && screen[fallingmino.mino_y + 2][fallingmino.mino_x + 2] != SHADOW) >= 3)
		{
			T_Spin = 2;
		}
		else
		{
			T_Spin = 0;
			T_Spin_Mini = 0;
			T_Spin_Print = 0;
		}
	}

	shadow_mino(fallingmino, screen);
	SetMino(fallingmino.mino_x, fallingmino.mino_y, fallingmino.shape, fallingmino.direction, screen);
	if (fallingmino.shape == 'T' && screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == 0 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == 2 || screen[fallingmino.mino_y + 2][fallingmino.mino_x + 1] == SHADOW)
		T_Spin_Mini = true;
	T_Spin_Print = 0;

	return fallingmino;
}


void Hard_Drop(struct FallingMino* fallingmino, int screen[][100])
{
	soundEffect("game_landing.mp3", &game_landing, &dwID_landing, true, false, false);
	bool flag = false;
	char memory = fallingmino->shape;

	DeleteMino(fallingmino->mino_x, fallingmino->mino_y, fallingmino->shape, fallingmino->direction, screen);
	for (int i = 1; i <= SCREEN_END_Y; i++)
	{
		if (screen[i + fallingmino->piece_y[1]][fallingmino->piece_x[1]] != 2 && screen[i + fallingmino->piece_y[1]][fallingmino->piece_x[1]] != 0 && screen[i + fallingmino->piece_y[1]][fallingmino->piece_x[1]] != SHADOW) flag = true;
		if (screen[i + fallingmino->piece_y[2]][fallingmino->piece_x[2]] != 2 && screen[i + fallingmino->piece_y[2]][fallingmino->piece_x[2]] != 0 && screen[i + fallingmino->piece_y[2]][fallingmino->piece_x[2]] != SHADOW) flag = true;
		if (screen[i + fallingmino->piece_y[3]][fallingmino->piece_x[3]] != 2 && screen[i + fallingmino->piece_y[3]][fallingmino->piece_x[3]] != 0 && screen[i + fallingmino->piece_y[3]][fallingmino->piece_x[3]] != SHADOW) flag = true;
		if (screen[i + fallingmino->piece_y[4]][fallingmino->piece_x[4]] != 2 && screen[i + fallingmino->piece_y[4]][fallingmino->piece_x[4]] != 0 && screen[i + fallingmino->piece_y[4]][fallingmino->piece_x[4]] != SHADOW) flag = true;

		if (flag)
		{
			if (fallingmino->shape != memory)
				return;
			SetMino(fallingmino->mino_x, fallingmino->mino_y + i - 1, fallingmino->shape, fallingmino->direction, screen);
			IsHolded = false;
			IsMinoFalling = false;
			SetMino(HOLD_X, HOLD_Y, Hold[0], UP, screen);
			break;
		}
	}
	return;
}


void Move_Mino(struct FallingMino* fallingmino, int direction, int screen[][100])
{

	bool flag = true;

	if (direction == LEFT)
	{
		switch (fallingmino->direction)
		{
		case UP:
			switch (fallingmino->shape)
			{
			case 'I':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == SHADOW) && fallingmino->piece_x[1] > SCREEN_START_X);
				break;
			case 'S':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == SHADOW) && fallingmino->piece_x[1] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == 0 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == 2 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == SHADOW) && fallingmino->piece_x[3] > SCREEN_START_X);
				break;
			case 'Z':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == SHADOW) && fallingmino->piece_x[1] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == 0 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == 2 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == SHADOW) && fallingmino->piece_x[3] > SCREEN_START_X);
				break;
			case 'O':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == SHADOW) && fallingmino->piece_x[1] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == 0 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == 2 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == SHADOW) && fallingmino->piece_x[3] > SCREEN_START_X);
				break;
			case 'T':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == SHADOW) && fallingmino->piece_x[1] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == 0 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == 2 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == SHADOW) && fallingmino->piece_x[2] > SCREEN_START_X);
				break;
			case 'J':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == SHADOW) && fallingmino->piece_x[1] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == 0 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == 2 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == SHADOW) && fallingmino->piece_x[2] > SCREEN_START_X);
				break;
			case 'L':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == SHADOW) && fallingmino->piece_x[1] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == 0 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == 2 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == SHADOW) && fallingmino->piece_x[2] > SCREEN_START_X);
				break;
			default:
				break;
			}
			break;
		case RIGHT:
			switch (fallingmino->shape)
			{
			case 'I':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == SHADOW) && fallingmino->piece_x[1] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == 0 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == 2 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == SHADOW) && fallingmino->piece_x[2] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == 0 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == 2 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == SHADOW) && fallingmino->piece_x[3] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == SHADOW) && fallingmino->piece_x[4] > SCREEN_START_X);
				break;
			case 'S':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == SHADOW) && fallingmino->piece_x[1] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == 0 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == 2 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == SHADOW) && fallingmino->piece_x[2] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == SHADOW) && fallingmino->piece_x[4] > SCREEN_START_X);
				break;
			case 'Z':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == SHADOW) && fallingmino->piece_x[1] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == 0 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == 2 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == SHADOW) && fallingmino->piece_x[2] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == SHADOW) && fallingmino->piece_x[4] > SCREEN_START_X);
				break;
			case 'O':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == SHADOW) && fallingmino->piece_x[1] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == 0 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == 2 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == SHADOW) && fallingmino->piece_x[3] > SCREEN_START_X);
				break;
			case 'T':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == SHADOW) && fallingmino->piece_x[1] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == 0 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == 2 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == SHADOW) && fallingmino->piece_x[2] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == SHADOW) && fallingmino->piece_x[4] > SCREEN_START_X);
				break;
			case 'J':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == SHADOW) && fallingmino->piece_x[1] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == 0 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == 2 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == SHADOW) && fallingmino->piece_x[3] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == SHADOW) && fallingmino->piece_x[4] > SCREEN_START_X);
				break;
			case 'L':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == SHADOW) && fallingmino->piece_x[1] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == 0 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == 2 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == SHADOW) && fallingmino->piece_x[2] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == 0 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == 2 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == SHADOW) && fallingmino->piece_x[3] > SCREEN_START_X);
				break;
			default:
				break;
			}
			break;
		case LEFT:
			switch (fallingmino->shape)
			{
			case 'I':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == SHADOW) && fallingmino->piece_x[1] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == 0 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == 2 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == SHADOW) && fallingmino->piece_x[2] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == 0 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == 2 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == SHADOW) && fallingmino->piece_x[3] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == SHADOW) && fallingmino->piece_x[4] > SCREEN_START_X);
				break;
			case 'S':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == SHADOW) && fallingmino->piece_x[1] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == 0 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == 2 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == SHADOW) && fallingmino->piece_x[2] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == SHADOW) && fallingmino->piece_x[4] > SCREEN_START_X);
				break;
			case 'Z':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == SHADOW) && fallingmino->piece_x[1] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == 0 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == 2 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == SHADOW) && fallingmino->piece_x[2] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == SHADOW) && fallingmino->piece_x[4] > SCREEN_START_X);
				break;
			case 'O':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == SHADOW) && fallingmino->piece_x[1] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == 0 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == 2 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == SHADOW) && fallingmino->piece_x[3] > SCREEN_START_X);
				break;
			case 'T':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == SHADOW) && fallingmino->piece_x[1] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == 0 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == 2 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == SHADOW) && fallingmino->piece_x[2] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == SHADOW) && fallingmino->piece_x[4] > SCREEN_START_X);
				break;
			case 'J':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == SHADOW) && fallingmino->piece_x[1] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == 0 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == 2 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] - 1] == SHADOW) && fallingmino->piece_x[2] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == 0 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == 2 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == SHADOW) && fallingmino->piece_x[3] > SCREEN_START_X);
				break;
			case 'L':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == SHADOW) && fallingmino->piece_x[1] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == 0 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == 2 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == SHADOW) && fallingmino->piece_x[3] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == SHADOW) && fallingmino->piece_x[4] > SCREEN_START_X);
				break;
			default:
				break;
			}
			break;
		case DOWN:
			switch (fallingmino->shape)
			{
			case 'I':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == SHADOW) && fallingmino->piece_x[1] > SCREEN_START_X);
				break;
			case 'S':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == SHADOW) && fallingmino->piece_x[1] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == 0 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == 2 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == SHADOW) && fallingmino->piece_x[3] > SCREEN_START_X);
				break;
			case 'Z':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == SHADOW) && fallingmino->piece_x[1] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == 0 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == 2 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == SHADOW) && fallingmino->piece_x[3] > SCREEN_START_X);
				break;
			case 'O':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == SHADOW) && fallingmino->piece_x[1] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == 0 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == 2 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] - 1] == SHADOW) && fallingmino->piece_x[3] > SCREEN_START_X);
				break;
			case 'T':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == SHADOW) && fallingmino->piece_x[1] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == SHADOW) && fallingmino->piece_x[4] > SCREEN_START_X);
				break;
			case 'J':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == SHADOW) && fallingmino->piece_x[1] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == SHADOW) && fallingmino->piece_x[4] > SCREEN_START_X);
				break;
			case 'L':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] - 1] == SHADOW) && fallingmino->piece_x[1] > SCREEN_START_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] - 1] == SHADOW) && fallingmino->piece_x[4] > SCREEN_START_X);
				break;
			default:
				break;
			}
			break;
		}

		if (flag)
		{
			soundEffect("game_move.mp3", &game_move, &dwID_move, true, false, false);
			erase_shadow(screen);
			DeleteMino(fallingmino->mino_x, fallingmino->mino_y, fallingmino->shape, fallingmino->direction, screen);
			for (int i = 1; i <= 4; i++)
			{
				fallingmino->piece_x[i]--;
			}
			fallingmino->mino_x--;
			shadow_mino(*fallingmino, screen);
			SetMino(fallingmino->mino_x, fallingmino->mino_y, fallingmino->shape, fallingmino->direction, screen);
		}
	}
	else if (direction == RIGHT)
	{
		switch (fallingmino->direction)
		{
		case UP:
			switch (fallingmino->shape)
			{
			case 'I':
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == SHADOW) && fallingmino->piece_x[4] < SCREEN_END_X);
				break;
			case 'S':
				flag = flag && ((screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == 0 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == 2 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == SHADOW) && fallingmino->piece_x[2] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == SHADOW) && fallingmino->piece_x[4] < SCREEN_END_X);
				break;
			case 'Z':
				flag = flag && ((screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == 0 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == 2 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == SHADOW) && fallingmino->piece_x[2] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == SHADOW) && fallingmino->piece_x[4] < SCREEN_END_X);
				break;
			case 'O':
				flag = flag && ((screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == 0 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == 2 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == SHADOW) && fallingmino->piece_x[2] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == SHADOW) && fallingmino->piece_x[4] < SCREEN_END_X);
				break;
			case 'T':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == SHADOW) && fallingmino->piece_x[1] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == SHADOW) && fallingmino->piece_x[4] < SCREEN_END_X);
				break;
			case 'J':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == SHADOW) && fallingmino->piece_x[1] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == SHADOW) && fallingmino->piece_x[4] < SCREEN_END_X);
				break;
			case 'L':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == SHADOW) && fallingmino->piece_x[1] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == SHADOW) && fallingmino->piece_x[4] < SCREEN_END_X);
				break;
			default:
				break;
			}
			break;
		case RIGHT:
			switch (fallingmino->shape)
			{
			case 'I':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == SHADOW) && fallingmino->piece_x[1] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == 0 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == 2 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == SHADOW) && fallingmino->piece_x[2] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == 0 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == 2 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == SHADOW) && fallingmino->piece_x[3] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == SHADOW) && fallingmino->piece_x[4] < SCREEN_END_X);
				break;
			case 'S':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == SHADOW) && fallingmino->piece_x[1] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == 0 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == 2 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == SHADOW) && fallingmino->piece_x[3] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == SHADOW) && fallingmino->piece_x[4] < SCREEN_END_X);
				break;
			case 'Z':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == SHADOW) && fallingmino->piece_x[1] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == 0 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == 2 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == SHADOW) && fallingmino->piece_x[3] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == SHADOW) && fallingmino->piece_x[4] < SCREEN_END_X);
				break;
			case 'O':
				flag = flag && ((screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == 0 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == 2 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == SHADOW) && fallingmino->piece_x[2] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == SHADOW) && fallingmino->piece_x[4] < SCREEN_END_X);
				break;
			case 'T':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == SHADOW) && fallingmino->piece_x[1] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == 0 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == 2 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == SHADOW) && fallingmino->piece_x[3] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == SHADOW) && fallingmino->piece_x[4] < SCREEN_END_X);
				break;
			case 'J':
				flag = flag && ((screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == 0 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == 2 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == SHADOW) && fallingmino->piece_x[2] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == 0 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == 2 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == SHADOW) && fallingmino->piece_x[3] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == SHADOW) && fallingmino->piece_x[4] < SCREEN_END_X);
				break;
			case 'L':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == SHADOW) && fallingmino->piece_x[1] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == 0 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == 2 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == SHADOW) && fallingmino->piece_x[2] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == SHADOW) && fallingmino->piece_x[4] < SCREEN_END_X);
				break;
			default:
				break;
			}
			break;
		case LEFT:
			switch (fallingmino->shape)
			{
			case 'I':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == SHADOW) && fallingmino->piece_x[1] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == 0 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == 2 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == SHADOW) && fallingmino->piece_x[2] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == 0 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == 2 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == SHADOW) && fallingmino->piece_x[3] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == SHADOW) && fallingmino->piece_x[4] < SCREEN_END_X);
				break;
			case 'S':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == SHADOW) && fallingmino->piece_x[1] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == 0 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == 2 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == SHADOW) && fallingmino->piece_x[3] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == SHADOW) && fallingmino->piece_x[4] < SCREEN_END_X);
				break;
			case 'Z':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == SHADOW) && fallingmino->piece_x[1] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == 0 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == 2 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == SHADOW) && fallingmino->piece_x[3] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == SHADOW) && fallingmino->piece_x[4] < SCREEN_END_X);
				break;
			case 'O':
				flag = flag && ((screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == 0 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == 2 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == SHADOW) && fallingmino->piece_x[2] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == SHADOW) && fallingmino->piece_x[4] < SCREEN_END_X);
				break;
			case 'T':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == SHADOW) && fallingmino->piece_x[1] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == 0 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == 2 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == SHADOW) && fallingmino->piece_x[3] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == SHADOW) && fallingmino->piece_x[4] < SCREEN_END_X);
				break;
			case 'J':
				flag = flag && ((screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == 0 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == 2 || screen[fallingmino->piece_y[1]][fallingmino->piece_x[1] + 1] == SHADOW) && fallingmino->piece_x[1] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == 0 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == 2 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == SHADOW) && fallingmino->piece_x[2] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == SHADOW) && fallingmino->piece_x[4] < SCREEN_END_X);
				break;
			case 'L':
				flag = flag && ((screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == 0 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == 2 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == SHADOW) && fallingmino->piece_x[2] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == 0 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == 2 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == SHADOW) && fallingmino->piece_x[3] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == SHADOW) && fallingmino->piece_x[4] < SCREEN_END_X);
				break;
			default:
				break;
			}
			break;
		case DOWN:
			switch (fallingmino->shape)
			{
			case 'I':
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == SHADOW) && fallingmino->piece_x[4] < SCREEN_END_X);
				break;
			case 'S':
				flag = flag && ((screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == 0 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == 2 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == SHADOW) && fallingmino->piece_x[2] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == SHADOW) && fallingmino->piece_x[4] < SCREEN_END_X);
				break;
			case 'Z':
				flag = flag && ((screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == 0 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == 2 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == SHADOW) && fallingmino->piece_x[2] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == SHADOW) && fallingmino->piece_x[4] < SCREEN_END_X);
				break;
			case 'O':
				flag = flag && ((screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == 0 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == 2 || screen[fallingmino->piece_y[2]][fallingmino->piece_x[2] + 1] == SHADOW) && fallingmino->piece_x[2] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == SHADOW) && fallingmino->piece_x[4] < SCREEN_END_X);
				break;
			case 'T':
				flag = flag && ((screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == 0 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == 2 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == SHADOW) && fallingmino->piece_x[3] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == SHADOW) && fallingmino->piece_x[4] < SCREEN_END_X);
				break;
			case 'J':
				flag = flag && ((screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == 0 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == 2 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == SHADOW) && fallingmino->piece_x[3] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == SHADOW) && fallingmino->piece_x[4] < SCREEN_END_X);
				break;
			case 'L':
				flag = flag && ((screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == 0 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == 2 || screen[fallingmino->piece_y[3]][fallingmino->piece_x[3] + 1] == SHADOW) && fallingmino->piece_x[3] < SCREEN_END_X);
				flag = flag && ((screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 0 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == 2 || screen[fallingmino->piece_y[4]][fallingmino->piece_x[4] + 1] == SHADOW) && fallingmino->piece_x[4] < SCREEN_END_X);
				break;
			default:
				break;
			}
			break;
		}

		if (flag)
		{
			soundEffect("game_move.mp3", &game_move, &dwID_move, true, false, false);
			erase_shadow(screen);
			DeleteMino(fallingmino->mino_x, fallingmino->mino_y, fallingmino->shape, fallingmino->direction, screen);
			for (int i = 1; i <= 4; i++)
			{
				fallingmino->piece_x[i]++;
			}
			fallingmino->mino_x++;
			shadow_mino(*fallingmino, screen);
			SetMino(fallingmino->mino_x, fallingmino->mino_y, fallingmino->shape, fallingmino->direction, screen);
		}
	}

	return;
}


void Clear_Line(int screen[][100])
{

	T_Spin_Print = 1;
	bool flag = true;
	int line_cnt = 0;

	for (int j = SCREEN_END_Y; j >= 0; j--)
	{
		flag = true;
		for (int i = SCREEN_START_X; i <= SCREEN_END_X; i++)
		{
			if (screen[j][i] == 2 || screen[j][i] == 0 || screen[j][i] == SHADOW)
				flag = false;
		}

		if (flag)
		{
			num_lines++;
			line_cnt++;
			for (int k = j; k >= 1; k--)
			{
				for (int i = SCREEN_START_X; i <= SCREEN_END_X; i++)
				{
					screen[k][i] = screen[k - 1][i];
					if (k == SCREEN_START_Y && screen[k][i] == 0)
						screen[k][i] = 2;
				}
			}
			for (int k = SCREEN_START_X; k <= SCREEN_END_X; k++)
				screen[0][k] = 0;
			j++;
		}
	}

	if (is40lines && num_lines >= 40)
	{
		endTime = time(NULL);
		record = endTime - startTime;
		if (best_record > record) best_record = record;
		IsGamePlaying = false;
		return;
	}

	if (T_Spin)
	{
		T_Spin_Print = true;
		T_Spin--;
	}
	else
	{
		T_Spin_Print = false;
		T_Spin_Mini = false;
	}

	if (cleared_line % 10 == 0) cleared_line = 0;

	if (line_cnt)
	{
		if (cleared_line % 10 >= 0) combo++;
		else combo = 0;
		cleared_line = line_cnt * 10 + 1;
		switch (line_cnt)
		{
		case 1:
			score += 100;
			if (T_Spin) score += 200;
			soundEffect("game_single.mp3", &game_single, &dwID_single, true, false, false);
			break;
		case 2:
			score += 200;
			if (T_Spin) score += 600;
			soundEffect("game_double.mp3", &game_double, &dwID_double, true, false, false);
			break;
		case 3:
			score += 400;
			if (T_Spin) score += 1200;
			soundEffect("game_triple.mp3", &game_triple, &dwID_triple, true, false, false);
			break;
		case 4:
			score += 800;
			soundEffect("game_tetris.mp3", &game_tetris, &dwID_tetris, true, false, false);
			break;
		default:
			break;
		}
	}
	else
	{
		combo = -1;
	}

	score += (combo / 2) * 150;

	cleared_line--;
	flag = true;

	for (int j = SCREEN_END_Y; j >= 0; j--)
	{
		for (int i = SCREEN_START_X; i <= SCREEN_END_X; i++)
		{
			flag = flag && (screen[j][i] == 2 || screen[j][i] == 0 || screen[j][i] == SHADOW);
			if (!flag) return;
		}
	}

	All_Clear = 1;
	_beginthreadex(NULL, 0, Thread_AllClear, 0, 0, NULL);
	soundEffect("game_perfect.mp3", &game_perfect, &dwID_perfect, true, false, false);
	score += 2000;

	return;
}


void Drop_Mino(struct FallingMino* fallingmino, int screen[][100])
{

	bool flag = true;
	char memory = fallingmino->shape;

	if (IsMinoFalling)
	{
		switch (fallingmino->direction)
		{
		case UP:
			switch (fallingmino->shape)
			{
			case 'I':
				flag = flag && (screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 0 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 2 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
				break;
			case 'S':
				flag = flag && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
				break;
			case 'Z':
				flag = flag && (screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 0 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 2 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
				break;
			case 'O':
				flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
				break;
			case 'T':
				flag = flag && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
				break;
			case 'J':
				flag = flag && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
				break;
			case 'L':
				flag = flag && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
				break;
			default:
				break;
			}
			break;
		case RIGHT:
			switch (fallingmino->shape)
			{
			case 'I':
				flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
				break;
			case 'S':
				flag = flag && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
				break;
			case 'Z':
				flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
				break;
			case 'O':
				flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
				break;
			case 'T':
				flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
				break;
			case 'J':
				flag = flag && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
				break;
			case 'L':
				flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
				break;
			default:
				break;
			}
			break;
		case LEFT:
			switch (fallingmino->shape)
			{
			case 'I':
				flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
				break;
			case 'S':
				flag = flag && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
				break;
			case 'Z':
				flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
				break;
			case 'O':
				flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
				break;
			case 'T':
				flag = flag && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
				break;
			case 'J':
				flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
				break;
			case 'L':
				flag = flag && (screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 0 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 2 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
				break;
			default:
				break;
			}
			break;
		case DOWN:
			switch (fallingmino->shape)
			{
			case 'I':
				flag = flag && (screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 0 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 2 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
				break;
			case 'S':
				flag = flag && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
				break;
			case 'Z':
				flag = flag && (screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 0 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 2 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
				break;
			case 'O':
				flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
				break;
			case 'T':
				flag = flag && (screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 0 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 2 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
				break;
			case 'J':
				flag = flag && (screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 0 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 2 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
				break;
			case 'L':
				flag = flag && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
				flag = flag && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
				break;
			default:
				break;
			}
			break;
		}

		if (flag)
		{
			for (int i = 1; i <= 4; i++)
				screen[fallingmino->piece_y[i]][fallingmino->piece_x[i]] = fallingmino->piece_x[i] >= SCREEN_START_X && fallingmino->piece_x[i] <= SCREEN_END_X && fallingmino->piece_y[i] >= 3 ? 2 : 0;

			for (int i = 1; i <= 4; i++)
				fallingmino->piece_y[i]++;

			for (int i = 1; i <= 4; i++)
				screen[fallingmino->piece_y[i]][fallingmino->piece_x[i]] = fallingmino->shape;

			fallingmino->mino_y++;
		}
		else
		{
			bool IsSpace = true;
			drop_count = 90;
			for (int t = 0; drop_count; t++)
			{
				Sleep(10);

				IsSpace = true;

				switch (fallingmino->direction)
				{
				case UP:
					switch (fallingmino->shape)
					{
					case 'I':
						IsSpace = IsSpace && (screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 0 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 2 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
						break;
					case 'S':
						IsSpace = IsSpace && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
						break;
					case 'Z':
						IsSpace = IsSpace && (screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 0 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 2 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
						break;
					case 'O':
						IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
						break;
					case 'T':
						IsSpace = IsSpace && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
						break;
					case 'J':
						IsSpace = IsSpace && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
						break;
					case 'L':
						IsSpace = IsSpace && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
						break;
					default:
						break;
					}
					break;
				case RIGHT:
					switch (fallingmino->shape)
					{
					case 'I':
						IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
						break;
					case 'S':
						IsSpace = IsSpace && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
						break;
					case 'Z':
						IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
						break;
					case 'O':
						IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
						break;
					case 'T':
						IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
						break;
					case 'J':
						IsSpace = IsSpace && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
						break;
					case 'L':
						IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
						break;
					default:
						break;
					}
					break;
				case DOWN:
					switch (fallingmino->shape)
					{
					case 'I':
						IsSpace = IsSpace && (screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 0 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 2 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
						break;
					case 'S':
						IsSpace = IsSpace && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
						break;
					case 'Z':
						IsSpace = IsSpace && (screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 0 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 2 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
						break;
					case 'O':
						IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
						break;
					case 'T':
						IsSpace = IsSpace && (screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 0 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 2 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
						break;
					case 'J':
						IsSpace = IsSpace && (screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 0 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 2 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
						break;
					case 'L':
						IsSpace = IsSpace && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
						break;
					default:
						break;
					}
					break;

				case LEFT:
					switch (fallingmino->shape)
					{
					case 'I':
						IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
						break;
					case 'S':
						IsSpace = IsSpace && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
						break;
					case 'Z':
						IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
						break;
					case 'O':
						IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
						break;
					case 'T':
						IsSpace = IsSpace && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
						break;
					case 'J':
						IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
						break;
					case 'L':
						IsSpace = IsSpace && (screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 0 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 2 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == SHADOW);
						IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
						break;
					default:
						break;
					}
					break;

				default:
					break;
				}

				if (IsSpace)
				{
					IsMinoFalling = true;
					return;
				}
				drop_count--;
			}

			IsSpace = true;

			switch (fallingmino->direction)
			{
			case UP:
				switch (fallingmino->shape)
				{
				case 'I':
					IsSpace = IsSpace && (screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 0 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 2 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'S':
					IsSpace = IsSpace && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'Z':
					IsSpace = IsSpace && (screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 0 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 2 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'O':
					IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'T':
					IsSpace = IsSpace && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'J':
					IsSpace = IsSpace && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'L':
					IsSpace = IsSpace && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				default:
					break;
				}
				break;
			case RIGHT:
				switch (fallingmino->shape)
				{
				case 'I':
					IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'S':
					IsSpace = IsSpace && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'Z':
					IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'O':
					IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'T':
					IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'J':
					IsSpace = IsSpace && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'L':
					IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				default:
					break;
				}
				break;
			case DOWN:
				switch (fallingmino->shape)
				{
				case 'I':
					IsSpace = IsSpace && (screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 0 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 2 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'S':
					IsSpace = IsSpace && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'Z':
					IsSpace = IsSpace && (screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 0 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 2 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'O':
					IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'T':
					IsSpace = IsSpace && (screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 0 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 2 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'J':
					IsSpace = IsSpace && (screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 0 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 2 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'L':
					IsSpace = IsSpace && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				default:
					break;
				}
				break;
			case LEFT:
				switch (fallingmino->shape)
				{
				case 'I':
					IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'S':
					IsSpace = IsSpace && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'Z':
					IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'O':
					IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'T':
					IsSpace = IsSpace && (screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 0 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == 2 || screen[fallingmino->piece_y[2] + 1][fallingmino->piece_x[2]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'J':
					IsSpace = IsSpace && (screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 0 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == 2 || screen[fallingmino->piece_y[3] + 1][fallingmino->piece_x[3]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				case 'L':
					IsSpace = IsSpace && (screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 0 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == 2 || screen[fallingmino->piece_y[1] + 1][fallingmino->piece_x[1]] == SHADOW);
					IsSpace = IsSpace && (screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 0 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == 2 || screen[fallingmino->piece_y[4] + 1][fallingmino->piece_x[4]] == SHADOW);
					break;
				default:
					break;
				}
				break;

			default:
				break;
			}

			if (IsSpace)
			{
				IsMinoFalling = true;
				return;
			}

			if (fallingmino->shape != memory) return;

			IsMinoFalling = false;
			IsHolded = false;
			SetMino(HOLD_X, HOLD_Y, Hold[0], UP, screen);//»ö³Ö±â

		}
	}

	drop_count = 50;
	return;
}


void DeleteMino(int x, int y, char shape, int direction, int screen[][100])
{
	if (direction == UP)
	{
		switch (shape)
		{
		case 'I':
		case 'i':
			screen[y + 1][x] = x >= SCREEN_START_X && x <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 1][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 1][x + 2] = x + 2 >= SCREEN_START_X && x + 2 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 1][x + 3] = x + 3 >= SCREEN_START_X && x + 3 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			break;
		case 'S':
		case 's':
			screen[y][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y >= 3 ? 2 : 0;
			screen[y][x + 2] = x + 2 >= SCREEN_START_X && x + 2 <= SCREEN_END_X && y >= 3 ? 2 : 0;
			screen[y + 1][x] = x >= SCREEN_START_X && x <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 1][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			break;
		case 'Z':
		case 'z':
			screen[y][x] = x >= SCREEN_START_X && x <= SCREEN_END_X && y >= 3 ? 2 : 0;
			screen[y][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y >= 3 ? 2 : 0;
			screen[y + 1][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 1][x + 2] = x + 2 >= SCREEN_START_X && x + 2 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			break;
		case 'O':
		case 'o':
			screen[y][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y >= 3 ? 2 : 0;
			screen[y][x + 2] = x + 2 >= SCREEN_START_X && x + 2 <= SCREEN_END_X && y >= 3 ? 2 : 0;
			screen[y + 1][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 1][x + 2] = x + 2 >= SCREEN_START_X && x + 2 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			break;
		case 'T':
		case 't':
			screen[y][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y >= 3 ? 2 : 0;
			screen[y + 1][x] = x >= SCREEN_START_X && x <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 1][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 1][x + 2] = x + 2 >= SCREEN_START_X && x + 2 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			break;
		case 'J':
		case 'j':
			screen[y][x] = x >= SCREEN_START_X && x <= SCREEN_END_X && y >= 3 ? 2 : 0;
			screen[y + 1][x] = x >= SCREEN_START_X && x <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 1][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 1][x + 2] = x + 2 >= SCREEN_START_X && x + 2 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			break;
		case 'L':
		case 'l':
			screen[y][x + 2] = x + 2 >= SCREEN_START_X && x + 2 <= SCREEN_END_X && y >= 3 ? 2 : 0;
			screen[y + 1][x] = x >= SCREEN_START_X && x <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 1][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 1][x + 2] = x + 2 >= SCREEN_START_X && x + 2 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			break;
		default:
			break;
		}
	}
	else if (direction == RIGHT)
	{
		switch (shape)
		{
		case 'I':
		case 'i':
			screen[y + 0][x + 2] = x + 2 >= SCREEN_START_X && x + 2 <= SCREEN_END_X && y + 0 >= 3 ? 2 : 0;
			screen[y + 1][x + 2] = x + 2 >= SCREEN_START_X && x + 2 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 2][x + 2] = x + 2 >= SCREEN_START_X && x + 2 <= SCREEN_END_X && y + 2 >= 3 ? 2 : 0;
			screen[y + 3][x + 2] = x + 2 >= SCREEN_START_X && x + 2 <= SCREEN_END_X && y + 3 >= 3 ? 2 : 0;
			break;
		case 'S':
		case 's':
			screen[y][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y >= 3 ? 2 : 0;
			screen[y + 1][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 1][x + 2] = x + 2 >= SCREEN_START_X && x + 2 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 2][x + 2] = x + 2 >= SCREEN_START_X && x + 2 <= SCREEN_END_X && y + 2 >= 3 ? 2 : 0;
			break;
		case 'Z':
		case 'z':
			screen[y][x + 2] = x + 2 >= SCREEN_START_X && x + 2 <= SCREEN_END_X && y >= 3 ? 2 : 0;
			screen[y + 1][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 1][x + 2] = x + 2 >= SCREEN_START_X && x + 2 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 2][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 2 >= 3 ? 2 : 0;
			break;
		case 'O':
		case 'o':
			screen[y][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y >= 3 ? 2 : 0;
			screen[y][x + 2] = x + 2 >= SCREEN_START_X && x + 2 <= SCREEN_END_X && y >= 3 ? 2 : 0;
			screen[y + 1][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 1][x + 2] = x + 2 >= SCREEN_START_X && x + 2 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			break;
		case 'T':
		case 't':
			screen[y][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y >= 3 ? 2 : 0;
			screen[y + 1][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 1][x + 2] = x + 2 >= SCREEN_START_X && x + 2 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 2][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 2 >= 3 ? 2 : 0;
			break;
		case 'J':
		case 'j':
			screen[y][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y >= 3 ? 2 : 0;
			screen[y][x + 2] = x + 2 >= SCREEN_START_X && x + 2 <= SCREEN_END_X && y >= 3 ? 2 : 0;
			screen[y + 1][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 2][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 2 >= 3 ? 2 : 0;
			break;
		case 'L':
		case 'l':
			screen[y][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y >= 3 ? 2 : 0;
			screen[y + 1][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 2][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 2 >= 3 ? 2 : 0;
			screen[y + 2][x + 2] = x + 2 >= SCREEN_START_X && x + 2 <= SCREEN_END_X && y + 2 >= 3 ? 2 : 0;
			break;
		default:
			break;
		}
	}
	else if (direction == LEFT)
	{
		switch (shape)
		{
		case 'I':
		case 'i':
			screen[y + 0][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 0 >= 3 ? 2 : 0;
			screen[y + 1][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 2][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 2 >= 3 ? 2 : 0;
			screen[y + 3][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 3 >= 3 ? 2 : 0;
			break;
		case 'S':
		case 's':
			screen[y + 0][x + 0] = x + 0 >= SCREEN_START_X && x + 0 <= SCREEN_END_X && y + 0 >= 3 ? 2 : 0;
			screen[y + 1][x + 0] = x + 0 >= SCREEN_START_X && x + 0 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 1][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 2][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 2 >= 3 ? 2 : 0;
			break;
		case 'Z':
		case 'z':
			screen[y][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y >= 3 ? 2 : 0;
			screen[y + 1][x + 0] = x >= SCREEN_START_X && x <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 1][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 2][x + 0] = x >= SCREEN_START_X && x <= SCREEN_END_X && y + 2 >= 3 ? 2 : 0;
			break;
		case 'O':
		case 'o':
			screen[y][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y >= 3 ? 2 : 0;
			screen[y][x + 2] = x + 2 >= SCREEN_START_X && x + 2 <= SCREEN_END_X && y >= 3 ? 2 : 0;
			screen[y + 1][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 1][x + 2] = x + 2 >= SCREEN_START_X && x + 2 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			break;
		case 'T':
		case 't':
			screen[y][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y >= 3 ? 2 : 0;
			screen[y + 1][x + 0] = x >= SCREEN_START_X && x <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 1][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 2][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 2 >= 3 ? 2 : 0;
			break;
		case 'J':
		case 'j':
			screen[y][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y >= 3 ? 2 : 0;
			screen[y + 1][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 2][x + 0] = x >= SCREEN_START_X && x <= SCREEN_END_X && y + 2 >= 3 ? 2 : 0;
			screen[y + 2][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 2 >= 3 ? 2 : 0;
			break;
		case 'L':
		case 'l':
			screen[y][x] = x >= SCREEN_START_X && x <= SCREEN_END_X && y >= 3 ? 2 : 0;
			screen[y][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y >= 3 ? 2 : 0;
			screen[y + 1][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 2][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 2 >= 3 ? 2 : 0;
			break;
		default:
			break;
		}
	}
	else if (direction == DOWN)
	{
		switch (shape)
		{
		case 'I':
		case 'i':
			screen[y + 2][x] = x >= SCREEN_START_X && x <= SCREEN_END_X && y + 2 >= 3 ? 2 : 0;
			screen[y + 2][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 2 >= 3 ? 2 : 0;
			screen[y + 2][x + 2] = x + 2 >= SCREEN_START_X && x + 2 <= SCREEN_END_X && y + 2 >= 3 ? 2 : 0;
			screen[y + 2][x + 3] = x + 3 >= SCREEN_START_X && x + 3 <= SCREEN_END_X && y + 2 >= 3 ? 2 : 0;
			break;
		case 'S':
		case 's':
			screen[y + 1][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 1][x + 2] = x + 2 >= SCREEN_START_X && x + 2 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 2][x] = x >= SCREEN_START_X && x <= SCREEN_END_X && y + 2 >= 3 ? 2 : 0;
			screen[y + 2][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 2 >= 3 ? 2 : 0;
			break;
		case 'Z':
		case 'z':
			screen[y + 1][x] = x >= SCREEN_START_X && x <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 1][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 2][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 2 >= 3 ? 2 : 0;
			screen[y + 2][x + 2] = x + 2 >= SCREEN_START_X && x + 2 <= SCREEN_END_X && y + 2 >= 3 ? 2 : 0;
			break;
		case 'O':
		case 'o':
			screen[y][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y >= 3 ? 2 : 0;
			screen[y][x + 2] = x + 2 >= SCREEN_START_X && x + 2 <= SCREEN_END_X && y >= 3 ? 2 : 0;
			screen[y + 1][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 1][x + 2] = x + 2 >= SCREEN_START_X && x + 2 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			break;
		case 'T':
		case 't':
			screen[y + 1][x] = x >= SCREEN_START_X && x <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 1][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 1][x + 2] = x + 2 >= SCREEN_START_X && x + 2 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 2][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 2 >= 3 ? 2 : 0;
			break;
		case 'J':
		case 'j':
			screen[y + 1][x] = x >= SCREEN_START_X && x <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 1][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 1][x + 2] = x + 2 >= SCREEN_START_X && x + 2 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 2][x + 2] = x + 2 >= SCREEN_START_X && x + 2 <= SCREEN_END_X && y + 2 >= 3 ? 2 : 0;
			break;
		case 'L':
		case 'l':
			screen[y + 1][x] = x >= SCREEN_START_X && x <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 1][x + 1] = x + 1 >= SCREEN_START_X && x + 1 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 1][x + 2] = x + 2 >= SCREEN_START_X && x + 2 <= SCREEN_END_X && y + 1 >= 3 ? 2 : 0;
			screen[y + 2][x] = x >= SCREEN_START_X && x <= SCREEN_END_X && y + 2 >= 3 ? 2 : 0;
			break;
		default:
			break;
		}
	}

	return;
}


void SummonMino(struct FallingMino* fallingmino, char NextMino[], int screen[][100])
{
	IsMinoFalling = true;

	switch (NextMino[0])
	{
	case 'I':
		for (int i = 1; i <= 4; i++)
		{
			fallingmino->piece_x[i] = START_X + i - 1;
			fallingmino->piece_y[i] = START_Y + 1;
		}
		break;
	case 'Z':
		fallingmino->piece_x[1] = START_X;
		fallingmino->piece_x[2] = START_X + 1;
		fallingmino->piece_x[3] = START_X + 1;
		fallingmino->piece_x[4] = START_X + 2;

		fallingmino->piece_y[1] = START_Y;
		fallingmino->piece_y[2] = START_Y;
		fallingmino->piece_y[3] = START_Y + 1;
		fallingmino->piece_y[4] = START_Y + 1;
		break;
	case 'S':
		fallingmino->piece_x[1] = START_X + 1;
		fallingmino->piece_x[2] = START_X + 2;
		fallingmino->piece_x[3] = START_X;
		fallingmino->piece_x[4] = START_X + 1;

		fallingmino->piece_y[1] = START_Y;
		fallingmino->piece_y[2] = START_Y;
		fallingmino->piece_y[3] = START_Y + 1;
		fallingmino->piece_y[4] = START_Y + 1;
		break;
	case 'O':
		fallingmino->piece_x[1] = START_X + 1;
		fallingmino->piece_x[2] = START_X + 2;
		fallingmino->piece_x[3] = START_X + 1;
		fallingmino->piece_x[4] = START_X + 2;

		fallingmino->piece_y[1] = START_Y;
		fallingmino->piece_y[2] = START_Y;
		fallingmino->piece_y[3] = START_Y + 1;
		fallingmino->piece_y[4] = START_Y + 1;
		break;
	case 'T':
		fallingmino->piece_x[1] = START_X + 1;
		fallingmino->piece_x[2] = START_X;
		fallingmino->piece_x[3] = START_X + 1;
		fallingmino->piece_x[4] = START_X + 2;

		fallingmino->piece_y[1] = START_Y;
		fallingmino->piece_y[2] = START_Y + 1;
		fallingmino->piece_y[3] = START_Y + 1;
		fallingmino->piece_y[4] = START_Y + 1;
		break;
	case 'L':
		fallingmino->piece_x[1] = START_X + 2;
		fallingmino->piece_x[2] = START_X;
		fallingmino->piece_x[3] = START_X + 1;
		fallingmino->piece_x[4] = START_X + 2;

		fallingmino->piece_y[1] = START_Y;
		fallingmino->piece_y[2] = START_Y + 1;
		fallingmino->piece_y[3] = START_Y + 1;
		fallingmino->piece_y[4] = START_Y + 1;
		break;
	case 'J':
		fallingmino->piece_x[1] = START_X;
		fallingmino->piece_x[2] = START_X;
		fallingmino->piece_x[3] = START_X + 1;
		fallingmino->piece_x[4] = START_X + 2;

		fallingmino->piece_y[1] = START_Y;
		fallingmino->piece_y[2] = START_Y + 1;
		fallingmino->piece_y[3] = START_Y + 1;
		fallingmino->piece_y[4] = START_Y + 1;
		break;
	default:
		break;
	}

	fallingmino->shape = NextMino[0];
	fallingmino->direction = UP;

	for (int i = 1; i <= 4; i++)
	{
		if (screen[fallingmino->piece_y[i]][fallingmino->piece_x[i]] != 0)
		{
			game_over(screen);
			return;
		}
	}
	fallingmino->mino_x = START_X;
	fallingmino->mino_y = START_Y;
	shadow_mino(*fallingmino, screen);

	SetMino(START_X, START_Y, NextMino[0], UP, screen);
	for (int i = 1; i <= 14; i++)
	{
		NextMino[i - 1] = NextMino[i];
	}

	return;
}


void SetMino(int x, int y, char shape, int direction, int screen[][100])
{
	if (direction == UP)
	{
		switch (shape)
		{
		case 'I':
		case 'i':
			screen[y + 1][x] = IsHolded && x == HOLD_X ? SHADOW_I : 'I';
			screen[y + 1][x + 1] = IsHolded && x == HOLD_X ? SHADOW_I : 'I';
			screen[y + 1][x + 2] = IsHolded && x == HOLD_X ? SHADOW_I : 'I';
			screen[y + 1][x + 3] = IsHolded && x == HOLD_X ? SHADOW_I : 'I';
			break;
		case 'S':
		case 's':
			screen[y][x + 1] = IsHolded && x == HOLD_X ? SHADOW_S : 'S';
			screen[y][x + 2] = IsHolded && x == HOLD_X ? SHADOW_S : 'S';
			screen[y + 1][x + 0] = IsHolded && x == HOLD_X ? SHADOW_S : 'S';
			screen[y + 1][x + 1] = IsHolded && x == HOLD_X ? SHADOW_S : 'S';
			break;
		case 'Z':
		case 'z':
			screen[y][x] = IsHolded && x == HOLD_X ? SHADOW_Z : 'Z';
			screen[y][x + 1] = IsHolded && x == HOLD_X ? SHADOW_Z : 'Z';
			screen[y + 1][x + 1] = IsHolded && x == HOLD_X ? SHADOW_Z : 'Z';
			screen[y + 1][x + 2] = IsHolded && x == HOLD_X ? SHADOW_Z : 'Z';
			break;
		case 'O':
		case 'o':
			screen[y][x + 1] = IsHolded && x == HOLD_X ? SHADOW_O : 'O';
			screen[y][x + 2] = IsHolded && x == HOLD_X ? SHADOW_O : 'O';
			screen[y + 1][x + 1] = IsHolded && x == HOLD_X ? SHADOW_O : 'O';
			screen[y + 1][x + 2] = IsHolded && x == HOLD_X ? SHADOW_O : 'O';
			break;
		case 'T':
		case 't':
			screen[y][x + 1] = IsHolded && x == HOLD_X ? SHADOW_T : 'T';
			screen[y + 1][x] = IsHolded && x == HOLD_X ? SHADOW_T : 'T';
			screen[y + 1][x + 1] = IsHolded && x == HOLD_X ? SHADOW_T : 'T';
			screen[y + 1][x + 2] = IsHolded && x == HOLD_X ? SHADOW_T : 'T';
			break;
		case 'J':
		case 'j':
			screen[y][x] = IsHolded && x == HOLD_X ? SHADOW_J : 'J';
			screen[y + 1][x] = IsHolded && x == HOLD_X ? SHADOW_J : 'J';
			screen[y + 1][x + 1] = IsHolded && x == HOLD_X ? SHADOW_J : 'J';
			screen[y + 1][x + 2] = IsHolded && x == HOLD_X ? SHADOW_J : 'J';
			break;
		case 'L':
		case 'l':
			screen[y][x + 2] = IsHolded && x == HOLD_X ? SHADOW_L : 'L';
			screen[y + 1][x] = IsHolded && x == HOLD_X ? SHADOW_L : 'L';
			screen[y + 1][x + 1] = IsHolded && x == HOLD_X ? SHADOW_L : 'L';
			screen[y + 1][x + 2] = IsHolded && x == HOLD_X ? SHADOW_L : 'L';
			break;
		default:
			switch (shape - SHADOW)
			{
			case I:
				screen[y + 1][x] = SHADOW;
				screen[y + 1][x + 1] = SHADOW;
				screen[y + 1][x + 2] = SHADOW;
				screen[y + 1][x + 3] = SHADOW;
				break;
			case S:
				screen[y][x + 1] = SHADOW;
				screen[y][x + 2] = SHADOW;
				screen[y + 1][x + 0] = SHADOW;
				screen[y + 1][x + 1] = SHADOW;
				break;
			case Z:
				screen[y][x] = SHADOW;
				screen[y][x + 1] = SHADOW;
				screen[y + 1][x + 1] = SHADOW;
				screen[y + 1][x + 2] = SHADOW;
				break;
			case O:
				screen[y][x + 1] = SHADOW;
				screen[y][x + 2] = SHADOW;
				screen[y + 1][x + 1] = SHADOW;
				screen[y + 1][x + 2] = SHADOW;
				break;
			case T:
				screen[y][x + 1] = SHADOW;
				screen[y + 1][x] = SHADOW;
				screen[y + 1][x + 1] = SHADOW;
				screen[y + 1][x + 2] = SHADOW;
				break;
			case J:
				screen[y][x] = SHADOW;
				screen[y + 1][x] = SHADOW;
				screen[y + 1][x + 1] = SHADOW;
				screen[y + 1][x + 2] = SHADOW;
				break;
			case L:
				screen[y][x + 2] = SHADOW;
				screen[y + 1][x] = SHADOW;
				screen[y + 1][x + 1] = SHADOW;
				screen[y + 1][x + 2] = SHADOW;
				break;
			default:
				break;
			}
			break;
		}
	}
	else if (direction == RIGHT)
	{
		switch (shape)
		{
		case 'I':
		case 'i':
			screen[y + 0][x + 2] = 'I';
			screen[y + 1][x + 2] = 'I';
			screen[y + 2][x + 2] = 'I';
			screen[y + 3][x + 2] = 'I';
			break;
		case 'S':
		case 's':
			screen[y][x + 1] = 'S';
			screen[y + 1][x + 1] = 'S';
			screen[y + 1][x + 2] = 'S';
			screen[y + 2][x + 2] = 'S';
			break;
		case 'Z':
		case 'z':
			screen[y][x + 2] = 'Z';
			screen[y + 1][x + 1] = 'Z';
			screen[y + 1][x + 2] = 'Z';
			screen[y + 2][x + 1] = 'Z';
			break;
		case 'O':
		case 'o':
			screen[y][x + 1] = 'O';
			screen[y][x + 2] = 'O';
			screen[y + 1][x + 1] = 'O';
			screen[y + 1][x + 2] = 'O';
			break;
		case 'T':
		case 't':
			screen[y][x + 1] = 'T';
			screen[y + 1][x + 1] = 'T';
			screen[y + 1][x + 2] = 'T';
			screen[y + 2][x + 1] = 'T';
			break;
		case 'J':
		case 'j':
			screen[y][x + 1] = 'J';
			screen[y][x + 2] = 'J';
			screen[y + 1][x + 1] = 'J';
			screen[y + 2][x + 1] = 'J';
			break;
		case 'L':
		case 'l':
			screen[y][x + 1] = 'L';
			screen[y + 1][x + 1] = 'L';
			screen[y + 2][x + 1] = 'L';
			screen[y + 2][x + 2] = 'L';
			break;
		default:
			switch (shape - SHADOW)
			{
			case I:
				screen[y + 0][x + 2] = SHADOW;
				screen[y + 1][x + 2] = SHADOW;
				screen[y + 2][x + 2] = SHADOW;
				screen[y + 3][x + 2] = SHADOW;
				break;
			case S:
				screen[y][x + 1] = SHADOW;
				screen[y + 1][x + 1] = SHADOW;
				screen[y + 1][x + 2] = SHADOW;
				screen[y + 2][x + 2] = SHADOW;
				break;
			case Z:
				screen[y][x + 2] = SHADOW;
				screen[y + 1][x + 1] = SHADOW;
				screen[y + 1][x + 2] = SHADOW;
				screen[y + 2][x + 1] = SHADOW;
				break;
			case O:
				screen[y][x + 1] = SHADOW;
				screen[y][x + 2] = SHADOW;
				screen[y + 1][x + 1] = SHADOW;
				screen[y + 1][x + 2] = SHADOW;
				break;
			case T:
				screen[y][x + 1] = SHADOW;
				screen[y + 1][x + 1] = SHADOW;
				screen[y + 1][x + 2] = SHADOW;;
				screen[y + 2][x + 1] = SHADOW;
				break;
			case J:
				screen[y][x + 1] = SHADOW;
				screen[y][x + 2] = SHADOW;
				screen[y + 1][x + 1] = SHADOW;
				screen[y + 2][x + 1] = SHADOW;
				break;
			case L:
				screen[y][x + 1] = SHADOW;
				screen[y + 1][x + 1] = SHADOW;;
				screen[y + 2][x + 1] = SHADOW;
				screen[y + 2][x + 2] = SHADOW;
				break;
			default:
				break;
			}
			break;
		}
	}
	else if (direction == LEFT)
	{
		switch (shape)
		{
		case 'I':
		case 'i':
			screen[y + 0][x + 1] = 'I';
			screen[y + 1][x + 1] = 'I';
			screen[y + 2][x + 1] = 'I';
			screen[y + 3][x + 1] = 'I';
			break;
		case 'S':
		case 's':
			screen[y][x + 0] = 'S';
			screen[y + 1][x + 0] = 'S';
			screen[y + 1][x + 1] = 'S';
			screen[y + 2][x + 1] = 'S';
			break;
		case 'Z':
		case 'z':
			screen[y][x + 1] = 'Z';
			screen[y + 1][x + 0] = 'Z';
			screen[y + 1][x + 1] = 'Z';
			screen[y + 2][x + 0] = 'Z';
			break;
		case 'O':
		case 'o':
			screen[y][x + 1] = 'O';
			screen[y][x + 2] = 'O';
			screen[y + 1][x + 1] = 'O';
			screen[y + 1][x + 2] = 'O';
			break;
		case 'T':
		case 't':
			screen[y][x + 1] = 'T';
			screen[y + 1][x + 0] = 'T';
			screen[y + 1][x + 1] = 'T';
			screen[y + 2][x + 1] = 'T';
			break;
		case 'J':
		case 'j':
			screen[y][x + 1] = 'J';
			screen[y + 1][x + 1] = 'J';
			screen[y + 2][x + 0] = 'J';
			screen[y + 2][x + 1] = 'J';
			break;
		case 'L':
		case 'l':
			screen[y][x] = 'L';
			screen[y][x + 1] = 'L';
			screen[y + 1][x + 1] = 'L';
			screen[y + 2][x + 1] = 'L';
			break;
		default:
			switch (shape - SHADOW)
			{
			case I:
				screen[y + 0][x + 1] = SHADOW;
				screen[y + 1][x + 1] = SHADOW;
				screen[y + 2][x + 1] = SHADOW;
				screen[y + 3][x + 1] = SHADOW;
				break;
			case S:
				screen[y][x + 0] = SHADOW;
				screen[y + 1][x + 0] = SHADOW;
				screen[y + 1][x + 1] = SHADOW;
				screen[y + 2][x + 1] = SHADOW;
				break;
			case Z:
				screen[y][x + 1] = SHADOW;
				screen[y + 1][x + 0] = SHADOW;
				screen[y + 1][x + 1] = SHADOW;
				screen[y + 2][x + 0] = SHADOW;
				break;
			case O:
				screen[y][x + 1] = SHADOW;
				screen[y][x + 2] = SHADOW;
				screen[y + 1][x + 1] = SHADOW;
				screen[y + 1][x + 2] = SHADOW;
				break;
			case T:
				screen[y][x + 1] = SHADOW;
				screen[y + 1][x + 0] = SHADOW;
				screen[y + 1][x + 1] = SHADOW;
				screen[y + 2][x + 1] = SHADOW;
				break;
			case J:
				screen[y][x + 1] = SHADOW;
				screen[y + 1][x + 1] = SHADOW;
				screen[y + 2][x + 0] = SHADOW;
				screen[y + 2][x + 1] = SHADOW;
				break;
			case L:
				screen[y][x] = SHADOW;
				screen[y][x + 1] = SHADOW;
				screen[y + 1][x + 1] = SHADOW;
				screen[y + 2][x + 1] = SHADOW;
				break;
			default:
				break;
			}
			break;
		}
	}
	else if (direction == DOWN)
	{
		switch (shape)
		{
		case 'I':
		case 'i':
			screen[y + 2][x] = 'I';
			screen[y + 2][x + 1] = 'I';
			screen[y + 2][x + 2] = 'I';
			screen[y + 2][x + 3] = 'I';
			break;
		case 'S':
		case 's':
			screen[y + 1][x + 1] = 'S';
			screen[y + 1][x + 2] = 'S';
			screen[y + 2][x] = 'S';
			screen[y + 2][x + 1] = 'S';
			break;
		case 'Z':
		case 'z':
			screen[y + 1][x] = 'Z';
			screen[y + 1][x + 1] = 'Z';
			screen[y + 2][x + 1] = 'Z';
			screen[y + 2][x + 2] = 'Z';
			break;
		case 'O':
		case 'o':
			screen[y][x + 1] = 'O';
			screen[y][x + 2] = 'O';
			screen[y + 1][x + 1] = 'O';
			screen[y + 1][x + 2] = 'O';
			break;
		case 'T':
		case 't':
			screen[y + 1][x] = 'T';
			screen[y + 1][x + 1] = 'T';
			screen[y + 1][x + 2] = 'T';
			screen[y + 2][x + 1] = 'T';
			break;
		case 'J':
		case 'j':
			screen[y + 1][x] = 'J';
			screen[y + 1][x + 1] = 'J';
			screen[y + 1][x + 2] = 'J';
			screen[y + 2][x + 2] = 'J';
			break;
		case 'L':
		case 'l':
			screen[y + 1][x] = 'L';
			screen[y + 1][x + 1] = 'L';
			screen[y + 1][x + 2] = 'L';
			screen[y + 2][x] = 'L';
			break;
		default:
			switch (shape - SHADOW)
			{
			case I:
				screen[y + 2][x] = SHADOW;
				screen[y + 2][x + 1] = SHADOW;
				screen[y + 2][x + 2] = SHADOW;
				screen[y + 2][x + 3] = SHADOW;
				break;
			case S:
				screen[y + 1][x + 1] = SHADOW;
				screen[y + 1][x + 2] = SHADOW;
				screen[y + 2][x] = SHADOW;
				screen[y + 2][x + 1] = SHADOW;
				break;
			case Z:
				screen[y + 1][x] = SHADOW;
				screen[y + 1][x + 1] = SHADOW;
				screen[y + 2][x + 1] = SHADOW;
				screen[y + 2][x + 2] = SHADOW;
				break;
			case O:
				screen[y][x + 1] = SHADOW;
				screen[y][x + 2] = SHADOW;
				screen[y + 1][x + 1] = SHADOW;
				screen[y + 1][x + 2] = SHADOW;
				break;
			case T:
				screen[y + 1][x] = SHADOW;
				screen[y + 1][x + 1] = SHADOW;
				screen[y + 1][x + 2] = SHADOW;
				screen[y + 2][x + 1] = SHADOW;
				break;
			case J:
				screen[y + 1][x] = SHADOW;
				screen[y + 1][x + 1] = SHADOW;
				screen[y + 1][x + 2] = SHADOW;
				screen[y + 2][x + 2] = SHADOW;
				break;
			case L:
				screen[y + 1][x] = SHADOW;
				screen[y + 1][x + 1] = SHADOW;
				screen[y + 1][x + 2] = SHADOW;
				screen[y + 2][x] = SHADOW;
				break;
			default:
				break;
			}
			break;
		}
	}
	return;
}


void CreateNextMino(char NextMino[], bool IsFirstCreate)
{
	srand((unsigned int)time(NULL));
	int random;
	int cnt = -1;
	int flag = 0;
	if (IsFirstCreate)
	{
		flag = 1;
		srand((unsigned int)time(NULL) - 10);
	}

	for (int i = 0; i < 7; i++)
	{
		random = rand() % (7 - i);
		for (int j = 0; j < 7; j++)
		{
			if (NextMino[j + 7 - 7 * flag] == '\0')
				cnt++;

			if (cnt == random)
			{
				NextMino[j + 7 - 7 * flag] = minos[i];
				cnt = -1;
				break;
			}

		}
	}
	return;
}