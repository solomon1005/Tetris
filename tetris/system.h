#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <process.h>
#include <string.h>

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

extern int All_Clear;
extern int cleared_line;
extern int combo;
extern int T_Spin;
extern bool T_Spin_Mini;
extern bool T_Spin_Print;
extern int num_lines;
extern int score;
extern bool IsHolded;


void textcolor(int ColorNum);

void print_screen(int screen[][100]);

void load_map(FILE* fp, int screen[][100]);

void CursorView();

void gotoxy(int x, int y);

struct MyHeadType* MakeStack();

void MyStack_Push(struct MyHeadType* MyHead, char Hold[20], char NextMino[20], struct FallingMino* fallingmino, int screen[][100]);

struct MyMemoryType* MyStack_Pop(struct MyHeadType* MyHead);

#endif