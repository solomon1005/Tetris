//고쳐야 할 것
// 
//메인 화면 -  최고 점수, 게임 모드(40line, blits, zen)선택 
//미노가 일정 높이 이상 올라오면 다음 미노 위치 표시하기
//bgm, 효과음 넣기 - (입브금? tetr.io? 뿌요뿌요?)
//버그 픽스
//버그 픽스
//버그 픽스
//버그 픽스
//버그 픽스
//배포!



#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <process.h>
#include <string.h>

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

#define SCREEN_START_X 7
#define SCREEN_START_Y 3
#define SCREEN_END_X 16
#define SCREEN_END_Y 22

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
#define SHADOW 10
#define SHADOW_I 11
#define SHADOW_S 12
#define SHADOW_Z 13
#define SHADOW_O 14
#define SHADOW_T 15
#define SHADOW_J 16
#define SHADOW_L 17

//map - 24 * 24
//0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
//0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
//0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
//1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1
//1 3 4 0 0 0 1 2 2 2 2 2 2 2 2 2 2 1 5 6 0 0 0 1
//1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1
//1 0 0 0 0 0 1 2 2 2 2 2 2 2 2 2 2 1 0 0 0 0 0 1
//1 0 # # # 0 1 2 2 2 2 2 2 2 2 2 2 1 0 # # # 0 1
//1 0 # # # 0 1 2 2 2 2 2 2 2 2 2 2 1 0 # # # 0 1
//1 0 0 0 0 0 1 2 2 2 2 2 2 2 2 2 2 1 0 0 0 0 0 1
//1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 1 0 # # # 0 1
//0 0 0 0 0 0 1 2 2 2 2 2 2 2 2 2 2 1 0 # # # 0 1
//0 0 0 0 0 0 1 2 2 2 2 2 2 2 2 2 2 1 0 0 0 0 0 1
//0 0 0 0 0 0 1 2 2 2 2 2 2 2 2 2 2 1 0 # # # 0 1
//0 0 0 0 0 0 1 2 2 2 2 2 2 2 2 2 2 1 0 # # # 0 1
//0 0 0 0 0 0 1 2 2 2 2 2 2 2 2 2 2 1 0 0 0 0 0 1
//0 0 0 0 0 0 1 2 2 2 2 2 2 2 2 2 2 1 0 # # # 0 1
//0 0 0 0 0 0 1 2 2 2 2 2 2 2 2 2 2 1 0 # # # 0 1
//0 0 0 0 0 0 1 2 2 2 2 2 2 2 2 2 2 1 0 0 0 0 0 1
//0 0 0 0 0 0 1 2 2 2 2 2 2 2 2 2 2 1 0 # # # 0 1
//0 0 0 0 0 0 1 2 2 2 2 2 2 2 2 2 2 1 0 # # # 0 1
//0 0 0 0 0 0 1 2 2 2 2 2 2 2 2 2 2 1 0 0 0 0 0 1
//0 0 0 0 0 0 1 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1
//0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0


struct FallingMino
{
	int mino_x;
	int mino_y;
	int piece_x[10];
	int piece_y[10];
	char shape;
	int direction;
};

struct MyMemoryType
{
	int screen[100][100];
	struct FallingMino* fallingmino;
	char hold[20];
	char nextmino[20];
	bool IsHolded;
	struct MyMemoryType* next;
};

struct MyHeadType
{
	int count;
	struct MyMemoryType* next;
};



void print_screen(int screen[][100]);

void load_map(FILE* fp, int screen[][100]);

void CursorView();

void gotoxy(int x, int y);

void main_screen(struct MyHeadType* MyHead, int screen[][100]);

void game(int screen[][100], struct FallingMino* fallingmino, struct MyHeadType* MyHead);

unsigned _stdcall Thread_Ingame(void* arg);

void textcolor(int ColorNum);

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

struct MyHeadType* MakeStack();

void MyStack_Push(struct MyHeadType* MyHead, char Hold[20], char NextMino[20], struct FallingMino* fallingmino, int screen[][100]);

struct MyMemoryType* MyStack_Pop(struct MyHeadType* MyHead);


char minos[7] = { 'I', 'S', 'Z', 'O', 'T', 'J', 'L' };
bool IsMinoFalling = false;
bool IsHolded = false;
bool IsGamePlaying = true;
bool IsRetry = false;
bool IsInstantRetry = false;
int All_Clear = 0;
int screen[100][100] = { 0 };
struct FallingMino fallingmino;
char Hold[20] = { '\0' };
char NextMino[20] = { '\0' };
int drop_count = 50;


int main()
{
	CursorView();

	struct MyHeadType* MyHead = MakeStack();

	while (1)
	{
		srand((unsigned int)time(NULL));
		if (!IsRetry)
			main_screen(MyHead, screen);

		game(screen, &fallingmino, MyHead);
		while (MyHead->count) {
			struct MyMemoryType* MyMemory = MyStack_Pop(MyHead);
			free(MyMemory);
		}

	}

	return 0;
}


void game(int screen[][100], struct FallingMino* fallingmino, struct MyHeadType* MyHead)
{
	IsGamePlaying = true;
	IsMinoFalling = false;
	IsHolded = false;
	IsRetry = false;
	IsInstantRetry = false;
	char c = '\0';
	for (int i = 0; i < 20; i++) NextMino[i] = '\0';

	FILE* fp = fopen("map.txt", "r");
	load_map(fp, screen);
	fclose(fp);

	gotoxy(0, 0);
	print_screen(screen);
	MyStack_Push(MyHead, Hold, NextMino, fallingmino, screen);


	for (int i = 0; i < 20; i++) Hold[i] = '\0';

	CreateNextMino(NextMino, true);
	CreateNextMino(NextMino, false);
	SummonMino(fallingmino, NextMino, screen);
	erase_shadow(screen);
	shadow_mino(*fallingmino, screen);
	if (NextMino[4] == '\0')
	{
		for (int i = 4; i < 14; i++)
		{
			NextMino[i] = NextMino[i + 1];
		}

		//printf("%d에서 NULL이 발견되었습니다.", &NextMino);
	}
	SetMino(NEXT_X, NEXT1_Y, NextMino[0], UP, screen);
	SetMino(NEXT_X, NEXT2_Y, NextMino[1], UP, screen);
	SetMino(NEXT_X, NEXT3_Y, NextMino[2], UP, screen);
	SetMino(NEXT_X, NEXT4_Y, NextMino[3], UP, screen);
	SetMino(NEXT_X, NEXT5_Y, NextMino[4], UP, screen);

	srand((unsigned int)time(NULL) + 10);

	_beginthreadex(NULL, 0, Thread_Ingame, 0, 0, NULL);


	while (IsGamePlaying)
	{
		if (NextMino[7] == '\0')
		{
			CreateNextMino(NextMino, false);
		}
		while (IsMinoFalling)
		{
			if (_kbhit())
			{
				c = _getch();

				if (c == -32)
				{
					c = _getch();
					switch (c)
					{
					case 75://왼
						Move_Mino(fallingmino, LEFT, screen);
						break;
					case 77://오
						Move_Mino(fallingmino, RIGHT, screen);
						break;
					case 72://위
						*fallingmino = Turn_Right(*fallingmino, 1, screen);
						break;
					case 80://아
						DeleteMino(fallingmino->mino_x, fallingmino->mino_y, fallingmino->shape, fallingmino->direction, screen);
						bool flag = true;
						while (flag) {
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
								Drop_Mino(fallingmino, screen);
						}

						SetMino(fallingmino->mino_x, fallingmino->mino_y, fallingmino->shape, fallingmino->direction, screen);
						break;
					default:
						break;
					}
				}
				else if ((c == 'c' || c == 'C') && !IsHolded)
				{
					IsHolded = true;
					erase_shadow(screen);
					DeleteMino(fallingmino->mino_x, fallingmino->mino_y, fallingmino->shape, fallingmino->direction, screen);
					if (Hold[0] != '\0')
					{
						DeleteMino(HOLD_X, HOLD_Y, Hold[0], UP, screen);
						SetMino(HOLD_X, HOLD_Y, fallingmino->shape, UP, screen);
						Hold[1] = fallingmino->shape;
						SummonMino(fallingmino, Hold, screen);
					}
					else
					{
						Hold[0] = fallingmino->shape;

						DeleteMino(NEXT_X, NEXT1_Y, NextMino[0], UP, screen);
						DeleteMino(NEXT_X, NEXT2_Y, NextMino[1], UP, screen);
						DeleteMino(NEXT_X, NEXT3_Y, NextMino[2], UP, screen);
						DeleteMino(NEXT_X, NEXT4_Y, NextMino[3], UP, screen);
						DeleteMino(NEXT_X, NEXT5_Y, NextMino[4], UP, screen);
						SummonMino(fallingmino, NextMino, screen);
						shadow_mino(*fallingmino, screen);
						SetMino(NEXT_X, NEXT1_Y, NextMino[0], UP, screen);
						SetMino(NEXT_X, NEXT2_Y, NextMino[1], UP, screen);
						SetMino(NEXT_X, NEXT3_Y, NextMino[2], UP, screen);
						SetMino(NEXT_X, NEXT4_Y, NextMino[3], UP, screen);
						SetMino(NEXT_X, NEXT5_Y, NextMino[4], UP, screen);

						SetMino(HOLD_X, HOLD_Y, Hold[0], UP, screen);
					}
					shadow_mino(*fallingmino, screen);

				}
				else if (c == ' ')
				{
					Hard_Drop(fallingmino, screen);
				}
				else if (c == 'z' || c == 'Z')
				{
					*fallingmino = Turn_Right(*fallingmino, 3, screen);
				}
				else if (c == 'x' || c == 'X')
				{
					*fallingmino = Turn_Right(*fallingmino, 1, screen);
				}
				else if (c == 'a' || c == 'A')
				{
					*fallingmino = Turn_Right(*fallingmino, 2, screen);
				}
				else if (c == 'r' || c == 'R')
				{
					IsInstantRetry = true;
					IsGamePlaying = false;
					Sleep(800);
					game_over(screen);
					return;
				}
				else if (c == 26)
				{
					if (MyHead->count < 2) continue;
					struct MyMemoryType* MyMemory = MyStack_Pop(MyHead);
					free(MyMemory);
					MyMemory = MyStack_Pop(MyHead);
					if (MyMemory != NULL)
					{
						IsHolded = MyMemory->IsHolded;
						for (int i = SCREEN_START_Y; i <= SCREEN_END_Y; i++) {
							for (int j = SCREEN_START_X; j <= SCREEN_END_X; j++)
								screen[i][j] = MyMemory->screen[i][j];
						}

						{
							DeleteMino(fallingmino->mino_x, fallingmino->mino_y, fallingmino->shape, fallingmino->direction, screen);
							DeleteMino(NEXT_X, NEXT1_Y, NextMino[0], UP, screen);
							DeleteMino(NEXT_X, NEXT2_Y, NextMino[1], UP, screen);
							DeleteMino(NEXT_X, NEXT3_Y, NextMino[2], UP, screen);
							DeleteMino(NEXT_X, NEXT4_Y, NextMino[3], UP, screen);
							DeleteMino(NEXT_X, NEXT5_Y, NextMino[4], UP, screen);
							DeleteMino(HOLD_X, HOLD_Y, Hold[0], UP, screen);
							erase_shadow(screen);
							IsMinoFalling = false;
						}
						for (int i = 0; i < 20; i++) {
							Hold[i] = MyMemory->hold[i];
							NextMino[i] = MyMemory->nextmino[i];
						}
						SetMino(HOLD_X, HOLD_Y, Hold[0], UP, screen);
						free(MyMemory);
					}

				}
			}
			gotoxy(0, 0);
			print_screen(screen);
		}

		Clear_Line(screen);
		MyStack_Push(MyHead, Hold, NextMino, fallingmino, screen);

		{
			DeleteMino(NEXT_X, NEXT1_Y, NextMino[0], UP, screen);
			DeleteMino(NEXT_X, NEXT2_Y, NextMino[1], UP, screen);
			DeleteMino(NEXT_X, NEXT3_Y, NextMino[2], UP, screen);
			DeleteMino(NEXT_X, NEXT4_Y, NextMino[3], UP, screen);
			DeleteMino(NEXT_X, NEXT5_Y, NextMino[4], UP, screen);
			SummonMino(fallingmino, NextMino, screen);
			if (!IsGamePlaying) return;
			SetMino(NEXT_X, NEXT1_Y, NextMino[0], UP, screen);
			SetMino(NEXT_X, NEXT2_Y, NextMino[1], UP, screen);
			SetMino(NEXT_X, NEXT3_Y, NextMino[2], UP, screen);
			SetMino(NEXT_X, NEXT4_Y, NextMino[3], UP, screen);
			SetMino(NEXT_X, NEXT5_Y, NextMino[4], UP, screen);
			erase_shadow(screen);
			shadow_mino(*fallingmino, screen);
			if (NextMino[4] == '\0')
			{
				for (int i = 4; i < 14; i++)
				{
					NextMino[i] = NextMino[i + 1];
				}

				//printf("%d에서 NULL이 발견되었습니다.", &NextMino);
			}
		}

	}

	return;
}


unsigned _stdcall Thread_Ingame(void* arg)
{
	while (IsGamePlaying)
	{
		Sleep(700);
		Drop_Mino(&fallingmino, screen);
		if (All_Clear == 1)
			All_Clear++;
		else if (All_Clear == 2)
			All_Clear++;
		else if (All_Clear == 3)
			All_Clear++;
		else if (All_Clear == 4)
			All_Clear = 0;
	}

	return 0;
}


struct MyMemoryType* MyStack_Pop(struct MyHeadType* MyHead)
{
	struct MyMemoryType* LastElement = MyHead->next;
	for (int i = 0; i < MyHead->count; i++)
		LastElement = LastElement->next;
	MyHead->count--;

	return LastElement;
}


void MyStack_Push(struct MyHeadType* MyHead, char Hold[20], char NextMino[20], struct FallingMino* fallingmino, int screen[][100])
{
	struct MyMemoryType* LastElement = MyHead->next;

	for (int i = 0; i < MyHead->count; i++)
		LastElement = LastElement->next;

	MyHead->count++;

	LastElement->next = (struct MyMemoryType*)malloc(sizeof(struct MyMemoryType));

	if (LastElement->next == NULL)
	{
		printf("동적 메모리 할당에 실패했습니다.");
		exit(NULL);
	}

	LastElement->next->fallingmino = fallingmino;
	for (int i = 0; i < 20; i++) {
		LastElement->next->hold[i] = Hold[i];
		LastElement->next->nextmino[i] = NextMino[i];
	}
	LastElement->next->IsHolded = IsHolded;
	for (int i = SCREEN_START_Y; i <= SCREEN_END_Y; i++) {
		for (int j = SCREEN_START_X; j <= SCREEN_END_X; j++)
			LastElement->next->screen[i][j] = screen[i][j];
	}

	return;
}


struct MyHeadType* MakeStack()
{
	struct MyHeadType* MyHead = (struct MyHeadType*)malloc(sizeof(struct MyHeadType));
	if (MyHead == NULL)
	{
		printf("동적 메모리 할당에 실패했습니다.");
		exit(NULL);
	}
	MyHead->count = 0;
	MyHead->next = NULL;

	MyHead->next = (struct MyMemoryType*)malloc(sizeof(struct MyMemoryType));
	if (MyHead->next == NULL)
	{
		printf("동적 메모리 할당에 실패했습니다.");
		exit(NULL);
	}
	MyHead->next->next = NULL;
	return MyHead;
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

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 0, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
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

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 1, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
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

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y - 2, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
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

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y - 2, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
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

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 0, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += -1;
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

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 1, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += -1;
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

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y - 2, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += -2;
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

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y - 2, fallingmino.shape, LEFT, screen);

				if (flag)
				{
					fallingmino.direction = LEFT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += -2;
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

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y - 1, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += -1;
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

				flag = IsMinoSetHere(fallingmino.mino_x + 0, fallingmino.mino_y + 2, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += 0;
					fallingmino.mino_y += 2;
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

				flag = IsMinoSetHere(fallingmino.mino_x - 1, fallingmino.mino_y + 2, fallingmino.shape, RIGHT, screen);

				if (flag)
				{
					fallingmino.direction = RIGHT;
					fallingmino.mino_x += -1;
					fallingmino.mino_y += 2;
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


void game_over(int screen[][100])
{
	IsGamePlaying = false;

	if (IsInstantRetry)
	{
		IsRetry = true;
		return;
	}

	Sleep(100);

	FILE* fp = fopen("game_over.txt", "r");
	load_map(fp, screen);
	fclose(fp);

	gotoxy(0, 0);
	print_screen(screen);

	int selected = 0;
	while (1)
	{
		switch (selected)
		{
		case 0:
			gotoxy(11, 19);
			printf(" ");
			gotoxy(36, 19);
			printf(" ");
			gotoxy(11, 17);
			printf(">");
			gotoxy(36, 17);
			printf("<");
			break;
		case 1:
			gotoxy(11, 17);
			printf(" ");
			gotoxy(36, 17);
			printf(" ");
			gotoxy(11, 19);
			printf(">");
			gotoxy(36, 19);
			printf("<");
			break;
		default:
			break;
		}
		char c = _getch();
		switch (c)
		{
		case -32:
			c = _getch();
			switch (c)
			{
			case 72://위
				selected = (selected + 1) % 2;
				break;
			case 80://아래
				selected = (selected - 1) % 2;
				if (selected == -1) selected += 2;
				break;
			default:
				break;
			}
			break;
		case ' ':
			if (selected == 0)
			{
				return;
			}
			else
			{
				IsRetry = true;
				return;
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

	shadow_mino(fallingmino, screen);
	SetMino(fallingmino.mino_x, fallingmino.mino_y, fallingmino.shape, fallingmino.direction, screen);

	return fallingmino;
}


void Hard_Drop(struct FallingMino* fallingmino, int screen[][100])
{

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
			Clear_Line(screen);
			SetMino(HOLD_X, HOLD_Y, Hold[0], UP, screen);
			IsMinoFalling = false;
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

	bool flag = true;

	for (int j = SCREEN_END_Y; j >= 1; j--)
	{
		flag = true;
		for (int i = SCREEN_START_X; i <= SCREEN_END_X; i++)
		{
			if (screen[j][i] == 2 || screen[j][i] == 0 || screen[j][i] == SHADOW)
				flag = false;
		}

		if (flag)
		{
			for (int k = j; k >= 1; k--)
			{
				for (int i = SCREEN_START_X; i <= SCREEN_END_X; i++)
				{
					screen[k][i] = screen[k - 1][i];
					if (k == SCREEN_START_Y && screen[k][i] == 0)
						screen[k][i] = 2;
				}
			}
			j++;
		}
	}

	flag = true;

	for (int j = SCREEN_END_Y; j >= 1; j--)
	{
		for (int i = SCREEN_START_X; i <= SCREEN_END_X; i++)
		{
			flag = flag && (screen[j][i] == 2 || screen[j][i] == 0 || screen[j][i] == SHADOW);
			if (!flag) return;
		}
	}

	All_Clear = 1;

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
				if (IsSpace) return;
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

			if (IsSpace) return;

			if (fallingmino->shape != memory) return;

			IsMinoFalling = false;
			IsHolded = false;
			//SetMino(fallingmino->mino_x, fallingmino->mino_y, fallingmino->shape, fallingmino->direction, screen);
			SetMino(HOLD_X, HOLD_Y, Hold[0], UP, screen);//색넣기
			Hard_Drop(fallingmino, screen);

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

	IsMinoFalling = true;
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


void main_screen(struct MyHeadType* MyHead, int screen[][100])
{
	FILE* fp = fopen("main.txt", "r");
	load_map(fp, screen);
	fclose(fp);

	gotoxy(0, 0);
	print_screen(screen);

	int selected = 0;
	while (1)
	{
		switch (selected)
		{
		case 0:
			gotoxy(11, 15);
			printf(" ");
			gotoxy(36, 15);
			printf(" ");
			gotoxy(11, 19);
			printf(" ");
			gotoxy(36, 19);
			printf(" ");
			gotoxy(11, 13);
			printf(">");
			gotoxy(36, 13);
			printf("<");
			break;
		case 1:
			gotoxy(11, 13);
			printf(" ");
			gotoxy(36, 13);
			printf(" ");
			gotoxy(11, 17);
			printf(" ");
			gotoxy(36, 17);
			printf(" ");
			gotoxy(11, 15);
			printf(">");
			gotoxy(36, 15);
			printf("<");
			break;
		case 2:
			gotoxy(11, 15);
			printf(" ");
			gotoxy(36, 15);
			printf(" ");
			gotoxy(11, 19);
			printf(" ");
			gotoxy(36, 19);
			printf(" ");
			gotoxy(11, 17);
			printf(">");
			gotoxy(36, 17);
			printf("<");
			break;
		case 3:
			gotoxy(11, 13);
			printf(" ");
			gotoxy(36, 13);
			printf(" ");
			gotoxy(11, 17);
			printf(" ");
			gotoxy(36, 17);
			printf(" ");
			gotoxy(11, 19);
			printf(">");
			gotoxy(36, 19);
			printf("<");
			break;
		default:
			break;
		}
		char c = _getch();
		switch (c)
		{
		case -32:
			c = _getch();
			switch (c)
			{
			case 72://위
				selected = (selected + 3) % 4;
				break;
			case 80://아래
				selected = (selected + 1) % 4;
				break;
			default:
				break;
			}
			break;
		case ' ':
			if (selected == 0)//game start
			{
				return;
			}
			else if (selected == 1)//help
			{

			}
			else if (selected == 2)//settings
			{

			}
			else if (selected == 3)//exit game
			{ 
				free(MyHead);
				exit(NULL);
			}
			else
			{

			}
			break;
		}
	}
	return;
}
//공사중 

void textcolor(int ColorNum)
{
	HANDLE _stdcall stdhandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(stdhandle, ColorNum);	
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


void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	return;
}


void print_screen(int screen[][100])
{
	//All_Clear 값에 따라 색 반전 시키기.
	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			if (All_Clear % 2 == 0)
			{
				switch (screen[i][j])
				{
				case 0:
					printf("  ");   
					break;   
				case 1:
					textcolor(0x0088);   
					printf("■ ");   
					textcolor(0x000F);   
					break;   
				case 2:
					textcolor(0x0008);   
					printf(". ");   
					textcolor(0x000F);   
					break;   
				case 3:
					printf(" HOLD ");   
					j += 2;   
					break;   
				case 4:
					printf(" NEXT ");   
					j += 2;   
					break;   
				case 5:
					printf(" EXIT TO MAIN MENU");   
					j += 8;   
					break;   
				case 6:
					printf(" RETRY");   
					j += 2;   
					break;   
				case 7:
					printf(" GAME START ");   
					j += 5;   
					break;   
				case 8:
					printf("SETTINGS");   
					j += 3;   
					break;   
				case 9:
					printf("HELP");   
					j += 1;   
					break;   
				case 'a' - '0':
					printf(" EXIT GAME");   
					j += 4;   
					break;   
				case 'I':
					if (j >= 18)
					{
						textcolor(0x00BB);   
						gotoxy(37, i);   
						printf("■ ■ ■ ■ ");   
						j += 3;   
						textcolor(0x000F);   
						printf(" ");   
					}
					else if (j <= 5)
					{
						textcolor(0x00BB);   
						gotoxy(3, i);   
						printf("■ ■ ■ ■ ");   
						j += 3;   
						textcolor(0x000F);   
						printf(" ");   
					}
					else
					{
						textcolor(0x00BB);   
						printf("■ ");   
						textcolor(0x000F);   
					}
					break;   
				case 'S':
					textcolor(0x00AA);   
					printf("■ ");   
					textcolor(0x000F);   
					break;   
				case 'Z':
					textcolor(0x00CC);   
					printf("■ ");   
					textcolor(0x000F);   
					break;   
				case 'O':
					if (j >= 18)
					{
						gotoxy(37, i);   
						printf("  ");   
						textcolor(0x00EE);   
						printf("■ ■ ");   
						j += 2;   
						textcolor(0x000F);   
						printf("   ");   
					}
					else if (j <= 5)
					{
						gotoxy(3, i);   
						printf("  ");   
						textcolor(0x00EE);   
						printf("■ ■ ");   
						j += 2;   
						textcolor(0x000F);   
						printf("   ");   
					}
					else
					{
						textcolor(0x00EE);   
						printf("■ ");   
						textcolor(0x000F);   
					}
					break;   
				case 'T':
					textcolor(0x00DD);   
					printf("■ ");   
					textcolor(0x000F);   
					break;   
				case 'J':
					textcolor(0x0099);   
					printf("■ ");   
					textcolor(0x000F);   
					break;   
				case 'L':
					textcolor(0x0066);   
					printf("■ ");   
					textcolor(0x000F);   
					break;   
				case SHADOW_I:
					textcolor(0x0088);   
					gotoxy(3, i);   
					printf("■ ■ ■ ■ ");   
					j += 3;   
					textcolor(0x000F);   
					printf(" ");   
					break;   
				case SHADOW_S:
					textcolor(0x0088);   
					printf("■ ");   
					textcolor(0x000F);   
					break;   
				case SHADOW_Z:
					textcolor(0x0088);   
					printf("■ ");   
					textcolor(0x000F);   
					break;   
				case SHADOW_O:
					gotoxy(3, i);   
					printf("  ");   
					textcolor(0x0088);   
					printf("■ ■ ");   
					j += 2;   
					textcolor(0x000F);   
					printf("   ");   
					break;   
				case SHADOW_T:
					textcolor(0x0088);   
					printf("■ ");   
					textcolor(0x000F);   
					break;   
				case SHADOW_J:
					textcolor(0x0088);   
					printf("■ ");   
					textcolor(0x000F);   
					break;   
				case SHADOW_L:
					textcolor(0x0088);   
					printf("■ ");   
					textcolor(0x000F);   
					break;   
				case SHADOW:
					textcolor(0x0088);   
					printf("■ ");   
					textcolor(0x000F);   
				default:
					break;   
				}
			}
			else
			{
				switch (screen[i][j])
				{
				case 0:
					printf("  ");   
					break;   
				case 1:
					textcolor(0x0088);   
					printf("■ ");   
					textcolor(0x00F0);
					break;   
				case 2:
					textcolor(0x00F8);
					printf(". ");   
					textcolor(0x00F0);
					break;   
				case 3:
					printf(" HOLD ");   
					j += 2;   
					break;   
				case 4:
					printf(" NEXT ");   
					j += 2;   
					break;   
				case 5:
					printf(" EXIT TO MAIN MENU");   
					j += 8;   
					break;   
				case 6:
					printf(" RETRY");   
					j += 2;   
					break;   
				case 7:
					printf(" GAME START ");   
					j += 5;   
					break;   
				case 8:
					printf("SETTINGS");   
					j += 3;   
					break;   
				case 9:
					printf("HELP");   
					j += 1;   
					break;   
				case 'a' - '0':
					printf(" EXIT GAME");   
					j += 4;   
					break;   
				case 'I':
					if (j >= 18)
					{
						textcolor(0x00BB);   
						gotoxy(37, i);   
						printf("■ ■ ■ ■ ");   
						j += 3;   
						textcolor(0x00F0);
						printf(" ");   
					}
					else if (j <= 5)
					{
						textcolor(0x00BB);   
						gotoxy(3, i);   
						printf("■ ■ ■ ■ ");   
						j += 3;   
						textcolor(0x00F0);
						printf(" ");   
					}
					else
					{
						textcolor(0x00BB);   
						printf("■ ");   
						textcolor(0x00F0);
					}
					break;   
				case 'S':
					textcolor(0x00AA);   
					printf("■ ");   
					textcolor(0x00F0);
					break;   
				case 'Z':
					textcolor(0x00CC);   
					printf("■ ");   
					textcolor(0x00F0);
					break;   
				case 'O':
					if (j >= 18)
					{
						gotoxy(37, i);   
						printf("  ");   
						textcolor(0x00EE);   
						printf("■ ■ ");   
						j += 2;   
						textcolor(0x00F0);
						printf("   ");   
					}
					else if (j <= 5)
					{
						gotoxy(3, i);   
						printf("  ");   
						textcolor(0x00EE);   
						printf("■ ■ ");   
						j += 2;   
						textcolor(0x00F0);
						printf("   ");   
					}
					else
					{
						textcolor(0x00EE);   
						printf("■ ");   
						textcolor(0x00F0);
					}
					break;   
				case 'T':
					textcolor(0x00DD);   
					printf("■ ");   
					textcolor(0x00F0);
					break;   
				case 'J':
					textcolor(0x0099);   
					printf("■ ");   
					textcolor(0x00F0);
					break;   
				case 'L':
					textcolor(0x0066);   
					printf("■ ");   
					textcolor(0x00F0);
					break;   
				case SHADOW_I:
					textcolor(0x0088);   
					gotoxy(3, i);   
					printf("■ ■ ■ ■ ");   
					j += 3;   
					textcolor(0x00F0);
					printf(" ");   
					break;   
				case SHADOW_S:
					textcolor(0x0088);   
					printf("■ ");   
					textcolor(0x00F0);
					break;   
				case SHADOW_Z:
					textcolor(0x0088);   
					printf("■ ");   
					textcolor(0x00F0);
					break;   
				case SHADOW_O:
					gotoxy(3, i);   
					printf("  ");   
					textcolor(0x0088);   
					printf("■ ■ ");   
					j += 2;   
					textcolor(0x00F0);
					printf("   ");   
					break;   
				case SHADOW_T:
					textcolor(0x0088);   
					printf("■ ");   
					textcolor(0x00F0);
					break;   
				case SHADOW_J:
					textcolor(0x0088);   
					printf("■ ");   
					textcolor(0x00F0);
					break;   
				case SHADOW_L:
					textcolor(0x0088);   
					printf("■ ");   
					textcolor(0x00F0);
					break;   
				case SHADOW:
					textcolor(0x0088);   
					printf("■ ");   
					textcolor(0x00F0);
				default:
					break;   
				}
			}
		}

		printf("\n");
	}

	return;
}


void load_map(FILE* fp, int screen[][100])
{
	char c[100];

	for (int i = 0; i < 24; i++)
	{
		fgets(c, 100, fp);
		for (int j = 0; j < 51; j += 2)
		{
			if (c[j] == '\n')
				break;
			else if (c[j] == '#')
				screen[i][j / 2] = 0;
			else if (c[j] >= 65 && c[j] <= 91)
				screen[i][j / 2] = c[j];
			else
				screen[i][j / 2] = c[j] - '0';
		}
	}
	return;
}


void CursorView()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = false;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
	return;
}