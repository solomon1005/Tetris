#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include <stdbool.h>
#include <conio.h>
#include <mmsystem.h>
#include <Digitalv.h>

#pragma comment(lib,"winmm.lib")

#define SHADOW 10
#define SHADOW_I 11
#define SHADOW_S 12
#define SHADOW_Z 13
#define SHADOW_O 14
#define SHADOW_T 15
#define SHADOW_J 16
#define SHADOW_L 17

#define SCREEN_START_X 7
#define SCREEN_START_Y 3
#define SCREEN_END_X 16
#define SCREEN_END_Y 22

extern struct MyHeadType
{
	int count;
	struct MyMemoryType* next;
} Myhead;

struct MyMemoryType
{
	int screen[100][100];
	struct FallingMino* fallingmino;
	char hold[20];
	char nextmino[20];
	bool IsHolded;
	struct MyMemoryType* next;
	int combo;
	int cleared_line;
	int score;
	int num_lines;
	int T_Spin;
	bool T_Spin_Mini;
	bool T_Spin_Print;
};

extern MCI_OPEN_PARMS bgm;
extern int dwID_bgm;

extern MCI_OPEN_PARMS bgm;
extern int dwID_bgm;

extern MCI_OPEN_PARMS system_select;
extern int dwID_select;

extern MCI_OPEN_PARMS system_ok;
extern int dwID_ok;

extern int All_Clear;
extern int cleared_line;
extern int combo;
extern int T_Spin;
extern bool T_Spin_Mini;
extern bool T_Spin_Print;
extern int num_lines;
extern int score;
extern bool IsHolded;
extern bool IsGamePlaying;
extern bool IsRetry;
extern bool IsInstantRetry;
extern int screen1[100][100];
extern bool GamePause;
extern bool isZen;
extern bool isBlitz;
extern bool is40lines;
extern int tutorial;
extern int isTutorial;
extern int bestScore;
extern int record;
extern int best_record;
extern int score_zen;
extern int bestScore_zen;
extern time_t startTime;
extern time_t endTime;


void textcolor(int ColorNum);

void print_screen(int screen[][100]);

void load_map(FILE* fp, int screen[][100]);

void main_screen(struct MyHeadType* MyHead, int screen[][100]);

void CursorView();

void gotoxy(int x, int y);

struct MyHeadType* MakeStack();

void MyStack_Push(struct MyHeadType* MyHead, char Hold[20], char NextMino[20], struct FallingMino* fallingmino, int screen[][100]);

struct MyMemoryType* MyStack_Pop(struct MyHeadType* MyHead);

void soundEffect(char filePath[], MCI_OPEN_PARMS* soundEffect, int* dwID, bool playing, bool repeat, bool load);

void mode_select_screen(int screen[][100]);

void game_result(int screen[][100]);

void load_record();

void save_record();

void help_screen(int screen[][100]);

#endif