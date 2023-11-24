//고쳐야 할 것
//메인 화면 -  게임 모드에 따른 점수 계산
// 최고 점수, 게임 오버 화면 순서 바꾸기
//버그 픽스
//버그 픽스
//배포!


#define _CRT_SECURE_NO_WARNINGS

#include "system.h"
#include "game_system.h"


void game(int screen[][100], struct FallingMino* fallingmino, struct MyHeadType* MyHead);


void soundLoad()
{
	soundEffect("game_count.mp3", &game_count, &dwID_count, true, false, true);
	soundEffect("game_single.mp3", &game_single, &dwID_single, true, false, true);
	soundEffect("game_double.mp3", &game_double, &dwID_double, true, false, true);
	soundEffect("game_triple.mp3", &game_triple, &dwID_triple, true, false, true);
	soundEffect("game_tetris.mp3", &game_tetris, &dwID_tetris, true, false, true);
	soundEffect("game_perfect.mp3", &game_perfect, &dwID_perfect, true, false, true);
	soundEffect("game_move.mp3", &game_move, &dwID_move, true, false, true);
	soundEffect("game_hold.mp3", &game_hold, &dwID_hold, true, false, true);
	soundEffect("game_harddrop.mp3", &game_harddrop, &dwID_harddrop, true, false, true);
	soundEffect("game_softdrop.mp3", &game_softdrop, &dwID_softdrop, true, false, true);
	soundEffect("game_rotate.mp3", &game_rotate, &dwID_rotate, true, false, true);
	soundEffect("game_landing.mp3", &game_landing, &dwID_landing, true, false, true);
	soundEffect("sys_ok.mp3", &system_ok, &dwID_ok, true, false, true);
	soundEffect("sys_select.mp3", &system_select, &dwID_select, true, false, true);

	return;
}


int main()
{
	CursorView();

	struct MyHeadType* MyHead = MakeStack();
	soundLoad();
	load_record();
	

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


		game_result(screen);
			
		num_lines = 0;
		cleared_line = 0;
		T_Spin = 0;
		T_Spin_Mini = T_Spin_Print = false;
		All_Clear = 0;
		score = 0;
	}

	return 0;
}


void game(int screen[][100], struct FallingMino* fallingmino, struct MyHeadType* MyHead)
{
	IsGamePlaying = true; 
	IsMinoFalling = false;
	IsHolded = false;
	IsRetry = false;
	char c = '\0';
	for (int i = 0; i < 20; i++) NextMino[i] = '\0';

	FILE* fp = fopen("map.txt", "r");
	load_map(fp, screen);
	fclose(fp);

	gotoxy(0, 0);


	for (int i = 0; i < 20; i++) Hold[i] = '\0';

	CreateNextMino(NextMino, true);
	CreateNextMino(NextMino, false);
	MyStack_Push(MyHead, Hold, NextMino, fallingmino, screen);

	srand((unsigned int)time(NULL) + 10);


	print_screen(screen);

	if (!IsInstantRetry) {
		Sleep(2000);
		soundEffect("game_count.mp3", &game_count, &dwID_count, true, false, false);
		Sleep(1000);
		soundEffect("game_count.mp3", &game_count, &dwID_count, true, false, false);
		Sleep(1000);
		soundEffect("game_count.mp3", &game_count, &dwID_count, true, false, false);
		Sleep(1000);
	}
	
	while (_kbhit()) c = _getch();
	c = '\0';

	soundEffect("TetrisTheme.mp3", &bgm, &dwID_bgm, true, true, false);
	
	if (is40lines || isBlitz) startTime = time(NULL);


	SummonMino(fallingmino, NextMino, screen);
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
	erase_shadow(screen);
	shadow_mino(*fallingmino, screen);


	IsInstantRetry = false;

	_beginthreadex(NULL, 0, Thread_Ingame, 0, 0, NULL);


	while (IsGamePlaying)
	{
		if (isBlitz && time(NULL) - startTime >= 60)
		{
			IsGamePlaying = false;
			game_result(screen);
			break;
		}

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
						soundEffect("game_rotate.mp3", &game_rotate, &dwID_rotate, true, false, false);
						*fallingmino = Turn_Right(*fallingmino, 1, screen);
						break;
					case 80://아
						soundEffect("game_softdrop.mp3", &game_softdrop, &dwID_softdrop, true, false, false);
						softDrop(fallingmino, screen);
						break;
					default:
						break;
					}
				}
				else if ((c == 'c' || c == 'C') && !IsHolded)
				{
					soundEffect("game_hold.mp3", &game_hold, &dwID_hold, true, false, false);
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
					soundEffect("game_harddrop.mp3", &game_harddrop, &dwID_harddrop, true, false, false);
					Hard_Drop(fallingmino, screen);
				}
				else if (c == 'z' || c == 'Z')
				{
					soundEffect("game_rotate.mp3", &game_rotate, &dwID_rotate, true, false, false);
					*fallingmino = Turn_Right(*fallingmino, 3, screen);
				}
				else if (c == 'x' || c == 'X')
				{
					soundEffect("game_rotate.mp3", &game_rotate, &dwID_rotate, true, false, false);
					*fallingmino = Turn_Right(*fallingmino, 1, screen);
				}
				else if (c == 'a' || c == 'A')
				{
					soundEffect("game_rotate.mp3", &game_rotate, &dwID_rotate, true, false, false);
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
				else if (c == 26)// Ctrl + z
				{
					if (MyHead->count < 2) continue;
					struct MyMemoryType* MyMemory = MyStack_Pop(MyHead);
					free(MyMemory);
					MyMemory = MyStack_Pop(MyHead);
					if (MyMemory != NULL)
					{
						RollBack = true;
						IsHolded = MyMemory->IsHolded;
						for (int i = 0; i <= SCREEN_END_Y; i++) {
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
						combo = MyMemory->combo;
						cleared_line = MyMemory->cleared_line;

						score = MyMemory->score;
						num_lines = MyMemory->num_lines;

						T_Spin = MyMemory->T_Spin;
						T_Spin_Mini = MyMemory->T_Spin_Mini;
						T_Spin_Print = MyMemory->T_Spin_Print;

						SetMino(HOLD_X, HOLD_Y, Hold[0], UP, screen);
						free(MyMemory);
					}

				}
				else if (c == 27)//esc
				{
					if (isZen)
					{
						Pause();
						if (!IsGamePlaying) return;
					}
				}
			}
			gotoxy(0, 0);
			print_screen(screen);
		}

		if(!RollBack) Clear_Line(screen);
		MyStack_Push(MyHead, Hold, NextMino, fallingmino, screen);
		RollBack = false;

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




