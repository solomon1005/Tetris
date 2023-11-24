#ifndef __GAME_SYSTEM__
#define __GAME_SYSTEM__

#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include <stdlib.h>
#include <process.h>
#include "system.h"


#define HOLD_X 2
#define HOLD_Y 7
#define NEXT_X 19
#define NEXT1_Y 7
#define NEXT2_Y 10
#define NEXT3_Y 13
#define NEXT4_Y 16
#define NEXT5_Y 19

#define START_X 10
#define START_Y 0

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#define I 1
#define S 2
#define Z 3
#define O 4
#define T 5
#define J 6
#define L 7

extern char minos[7];
extern bool IsMinoFalling;
extern bool RollBack;
extern int softDropVal;
extern int screen[100][100];
extern struct FallingMino {
	int mino_x;
	int mino_y;
	int piece_x[10];
	int piece_y[10];
	char shape;
	int direction;
} fallingmino;
extern char Hold[20];
extern char NextMino[20];
extern int drop_count;
extern int best_score;

extern MCI_OPEN_PARMS game_count;
extern MCI_OPEN_PARMS game_single;
extern MCI_OPEN_PARMS game_double;
extern MCI_OPEN_PARMS game_triple;
extern MCI_OPEN_PARMS game_tetris;
extern MCI_OPEN_PARMS game_perfect;
extern MCI_OPEN_PARMS game_move;
extern MCI_OPEN_PARMS game_hold;
extern MCI_OPEN_PARMS game_harddrop;
extern MCI_OPEN_PARMS game_softdrop;
extern MCI_OPEN_PARMS game_rotate;
extern MCI_OPEN_PARMS game_landing;

extern int dwID_count;
extern int dwID_single;
extern int dwID_double;
extern int dwID_triple;
extern int dwID_tetris;
extern int dwID_perfect;
extern int dwID_move;
extern int dwID_hold;
extern int dwID_harddrop;
extern int dwID_softdrop;
extern int dwID_rotate;
extern int dwID_landing;


unsigned _stdcall Thread_Ingame(void* arg);

void SetMino(int x, int y, char shape, int direction, int screen[][100]);

void CreateNextMino(char NextMino[], bool IsFirstCreate);

void SummonMino(struct FallingMino* fallingminio, char NextMino[], int screen[][100]);

void Drop_Mino(struct FallingMino* fallingmino, int screen[][100]);

void Clear_Line(int screen[][100]);

void DeleteMino(int x, int y, char shape, int direction, int screen[][100]);

void Move_Mino(struct FallingMino* fallingmino, int direction, int screen[][100]);

void Hard_Drop(struct FallingMino* fallingmino, int screen[][100]);

void game_over(int screen[][100]);

void shadow_mino(struct FallingMino fallingmino, int screen[][100]);

void erase_shadow(int screen[][100]);

struct FallingMino Turn_Right(struct FallingMino fallingmino, int count, int screen[][100]);

bool IsMinoSetHere(int mino_x, int mino_y, int shape, int direction, int screen[][100]);

struct FallingMino Spin(struct FallingMino fallingmino, int count, int screen[][100]);

void Pause();

void softDrop(struct FallingMino* fallingmino, int screen[][100]);

#endif