// 테트리스
// 위에서 떨어지는 블록을 회전하고, 이동하고 쌓아서 줄을 없애 점수를 얻는 게임이다.
// 닌텐도의 테트리스를 모방하여 만들었으며, wall kick을 구현하여 더욱 역동적인 게임이 되도록 하였다.

#define _CRT_SECURE_NO_WARNINGS

#include "system.h"
#include "game_system.h"


void game(int screen[][100], struct FallingMino* fallingmino, struct MyHeadType* MyHead); // 게임이 실행되는 중 중추가 되는 함수이다. 게임 내 거의 대부분의 시스템을 실행시킨다.


void soundLoad() // 음악을 재생하기 전 로드해 호출했을 때 즉시 나올 수 있도록 하는 함수이다.
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
	CursorView(); // 화면 깜빡임을 없앤다.

	struct MyHeadType* MyHead = MakeStack(); //되돌리기 실행을 위한 스택을 만든다.
	soundLoad(); // 음악을 로드한다.
	load_record(); // 최고 기록을 받아 와 저장한다.
	

	while (1) // 시스템이 종료되기 전까지 실행한다.
	{
		srand((unsigned int)time(NULL));

		if (!IsRetry)// 이전 게임에서 즉시 재시작을 눌렀다면 실행하지 않는다.
			main_screen(MyHead, screen); //게임을 처음 시작했을 때 나오는 화면이다.

		game(screen, &fallingmino, MyHead); // 게임을 실행한다.

		game_result(screen);

		while (MyHead->count) {// 게임 실행 후 스택을 비운다.
			struct MyMemoryType* MyMemory = MyStack_Pop(MyHead);
			free(MyMemory);
		}
		num_lines = 0; // 게임 실행 후 변수를 초기화한다.
		cleared_line = 0;
		T_Spin = 0;
		T_Spin_Mini = T_Spin_Print = false;
		All_Clear = 0;
		score = 0;
	}

	return 0;
}


void game(int screen[][100], struct FallingMino* fallingmino, struct MyHeadType* MyHead) // 게임이 실행되는 중 중추가 되는 함수이다. 게임 내 거의 대부분의 시스템을 실행시킨다.
{
	IsGamePlaying = true; //각 변수들의 초기값을 설정한다.
	IsMinoFalling = false;
	IsHolded = false;
	IsRetry = false;
	char c = '\0';
	for (int i = 0; i < 20; i++) NextMino[i] = '\0';

	FILE* fp = fopen("map.txt", "r"); // 게임 내 화면을 불러온다.
	load_map(fp, screen); 
	fclose(fp);

	gotoxy(0, 0);


	for (int i = 0; i < 20; i++) Hold[i] = '\0';

	CreateNextMino(NextMino, true); //다음에 나올 미노(블록)을 설정한다.
	CreateNextMino(NextMino, false);
	MyStack_Push(MyHead, Hold, NextMino, fallingmino, screen);

	srand((unsigned int)time(NULL) + 10);


	print_screen(screen); // 화면을 출력한다.

	if (!IsInstantRetry) { // 이전 게임에서 즉시 재시작을 누르지 않았다면 시작음을 재생한다.
		Sleep(2000);
		soundEffect("game_count.mp3", &game_count, &dwID_count, true, false, false);
		Sleep(1000);
		soundEffect("game_count.mp3", &game_count, &dwID_count, true, false, false);
		Sleep(1000);
		soundEffect("game_count.mp3", &game_count, &dwID_count, true, false, false);
		Sleep(1000);
	}
	
	while (_kbhit()) c = _getch(); // 버퍼를 비운다.
	c = '\0';

	soundEffect("TetrisTheme.mp3", &bgm, &dwID_bgm, true, true, false); // 배경 음악을 재생한다.
	
	if (is40lines || isBlitz) startTime = time(NULL); // 점수 계산에 필요한 시간값을 받아 온다.


	SummonMino(fallingmino, NextMino, screen); //화면에 떨어지는 미노를 생성한다.
	if (NextMino[4] == '\0')
	{
		for (int i = 4; i < 14; i++)
		{
			NextMino[i] = NextMino[i + 1];
		}

	} // 오류를 감지하여 복구한다.
	SetMino(NEXT_X, NEXT1_Y, NextMino[0], UP, screen);
	SetMino(NEXT_X, NEXT2_Y, NextMino[1], UP, screen);
	SetMino(NEXT_X, NEXT3_Y, NextMino[2], UP, screen);
	SetMino(NEXT_X, NEXT4_Y, NextMino[3], UP, screen);
	SetMino(NEXT_X, NEXT5_Y, NextMino[4], UP, screen);
	erase_shadow(screen); //미노의 그림자를 생성한다.
	shadow_mino(*fallingmino, screen); 


	IsInstantRetry = false;

	_beginthreadex(NULL, 0, Thread_Ingame, 0, 0, NULL); // 미노가 떨어지도록 스레드를 실행한다.


	while (IsGamePlaying) // 게임이 플레이되는 동안 실행한다.
	{
		if (isBlitz && time(NULL) - startTime >= 60) // Blitz모드의 종료 여부를 판단한다.
		{
			IsGamePlaying = false; // 게임이 종료되었다면 결과를 띄우고 리턴한다.
			game_result(screen); 
			break;
		}

		if (NextMino[7] == '\0') // 다음에 생성될 미노를 만든다.
		{
			CreateNextMino(NextMino, false);
		}
		while (IsMinoFalling) // 미노가 떨어지는 동안 실행한다.
		{
			if (_kbhit()) // 키보드 입력이 들어오면
			{
				c = _getch();

				if (c == -32)
				{
					c = _getch();
					switch (c)
					{
					case 75://왼
						Move_Mino(fallingmino, LEFT, screen);//미노가 왼쪽으로 움직일 수 있는지 여부를 판단해 움직인다.
						break;
					case 77://오
						Move_Mino(fallingmino, RIGHT, screen); // 미노가 오른쪽으로 움직일 수 있는지 여부를 판단하여 움직인다.
						break;
					case 72://위
						soundEffect("game_rotate.mp3", &game_rotate, &dwID_rotate, true, false, false); // 미노가 돌아갈 수 있는지 여부를 판단하여 움직인다.(소리 재생)
						*fallingmino = Turn_Right(*fallingmino, 1, screen);
						break;
					case 80://아
						soundEffect("game_softdrop.mp3", &game_softdrop, &dwID_softdrop, true, false, false); // 미노가 아래로 내려갈 수 있는지 판단하여 움직인다.(소리 재생)
						softDrop(fallingmino, screen);
						break;
					default:
						break;
					}
				}
				else if ((c == 'c' || c == 'C') && !IsHolded) //C를 눌렀다면 홀드 가능한지 여부를 판단하여 홀드한다.
				{
					soundEffect("game_hold.mp3", &game_hold, &dwID_hold, true, false, false); // 소리 재생
					IsHolded = true;
					erase_shadow(screen);
					DeleteMino(fallingmino->mino_x, fallingmino->mino_y, fallingmino->shape, fallingmino->direction, screen);
					if (Hold[0] != '\0') // 만약 이미 홀드한 블록이 있다면 그 블록과 떨어지는 블록을 교체한다.
					{
						DeleteMino(HOLD_X, HOLD_Y, Hold[0], UP, screen);
						SetMino(HOLD_X, HOLD_Y, fallingmino->shape, UP, screen);
						Hold[1] = fallingmino->shape;
						SummonMino(fallingmino, Hold, screen);
					}
					else // 그렇지 않다면 미노를 홀드하고 다음에 나올 미노를 다시 표시한다.
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
				else if (c == ' ') // 만약 스페이스를 눌렀다면 하드드롭한다.
				{
					soundEffect("game_harddrop.mp3", &game_harddrop, &dwID_harddrop, true, false, false);
					Hard_Drop(fallingmino, screen);
				}
				else if (c == 'z' || c == 'Z') // 만약 z를 눌렀다면 반시계 방향으로 돌아갈 수 있는지 확인 후 돌린다.
				{
					soundEffect("game_rotate.mp3", &game_rotate, &dwID_rotate, true, false, false);
					*fallingmino = Turn_Right(*fallingmino, 3, screen);
				}
				else if (c == 'x' || c == 'X') // 만약 x를 눌렀다면 반시계 방향으로 돌아갈 수 있는지 확인 후 돌린다.
				{
					soundEffect("game_rotate.mp3", &game_rotate, &dwID_rotate, true, false, false);
					*fallingmino = Turn_Right(*fallingmino, 1, screen);
				}
				else if (c == 'a' || c == 'A') // 만약 a를 눌렀다면 180도 돌릴 수 있는지 확인 후 돌린다.
				{
					soundEffect("game_rotate.mp3", &game_rotate, &dwID_rotate, true, false, false);
					*fallingmino = Turn_Right(*fallingmino, 2, screen);
				}
				else if (c == 'r' || c == 'R') //만약 r을 눌렀다면 즉시 재시작한다.
				{
					IsInstantRetry = true;
					IsGamePlaying = false;
					Sleep(800);
					game_over(screen);
					return;
				}
				else if (c == 26)// 만약 Ctrl + z를 눌렀다면 스택에 들어 있던 정보를 이용해 미노를 놓기 전으로 돌아간다.
				{
					if (MyHead->count < 2) continue; //만약 스택이 비었다면 무시하고 계속 실행한다.
					struct MyMemoryType* MyMemory = MyStack_Pop(MyHead); // 스택에 들어 있는 정보를 꺼내 변수를 초기화한다.
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
				else if (c == 27)//만약 esc를 눌렀다면 일시 정지한다.
				{
					if (isZen)
					{
						Pause();
						if (!IsGamePlaying) return;
					}
				}
			}
			gotoxy(0, 0);
			print_screen(screen); // 화면을 갱신한다.
		}

		if(!RollBack) Clear_Line(screen); // 이전 화면으로 돌아가지 않았을 경우 줄을 없애야 하는지 판단 후 실행한다(불필요한 효과 방지)
		MyStack_Push(MyHead, Hold, NextMino, fallingmino, screen);//스택에 현재 화면을 넣는다.
		RollBack = false;

		{
			DeleteMino(NEXT_X, NEXT1_Y, NextMino[0], UP, screen);
			DeleteMino(NEXT_X, NEXT2_Y, NextMino[1], UP, screen);
			DeleteMino(NEXT_X, NEXT3_Y, NextMino[2], UP, screen);
			DeleteMino(NEXT_X, NEXT4_Y, NextMino[3], UP, screen);
			DeleteMino(NEXT_X, NEXT5_Y, NextMino[4], UP, screen);
			SummonMino(fallingmino, NextMino, screen); // 다음에 떨어질 미노를 생성한다.
			if (!IsGamePlaying) return;
			SetMino(NEXT_X, NEXT1_Y, NextMino[0], UP, screen);
			SetMino(NEXT_X, NEXT2_Y, NextMino[1], UP, screen);
			SetMino(NEXT_X, NEXT3_Y, NextMino[2], UP, screen);
			SetMino(NEXT_X, NEXT4_Y, NextMino[3], UP, screen);
			SetMino(NEXT_X, NEXT5_Y, NextMino[4], UP, screen);
			erase_shadow(screen);
			shadow_mino(*fallingmino, screen);
			if (NextMino[4] == '\0') // 오류를 감지하면 복구한다.
			{
				for (int i = 4; i < 14; i++)
				{
					NextMino[i] = NextMino[i + 1];
				}

			}
		}

	}

	return;
}
