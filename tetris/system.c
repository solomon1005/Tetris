#include "system.h"


struct MyHeadType MyHead;


MCI_OPEN_PARMS bgm;
int dwID_bgm;

MCI_OPEN_PARMS system_select;
int dwID_select;

MCI_OPEN_PARMS system_ok;
int dwID_ok;

int All_Clear = 0;
int cleared_line = 0;
int combo = 0;
int T_Spin = 0;
bool T_Spin_Mini = false;
bool T_Spin_Print = false;
int num_lines = 0;
int score = 0;
bool IsHolded = false;
bool IsGamePlaying = true;
bool IsRetry = false;
bool IsInstantRetry = false;
int screen1[100][100];
bool GamePause = false;
bool isZen = false;
bool isBlitz = false;
bool is40lines = false;
int tutorial = 0;
int isTutorial = 0;
int bestScore = 0;
int record = 0;
int best_record = INT_MAX;
int score_zen = 0;
int bestScore_zen = 0;
time_t startTime;
time_t endTime;



void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	return;
}


void print_screen(int screen[][100])
{
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
				case 'a':
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
					break;
				case 'c':
					switch (cleared_line / 10)
					{
					case 1:
						printf("SINGLE");
						j += 2;
						break;
					case 2:
						printf("DOUBLE");
						j += 2;
						break;
					case 3:
						printf("TRIPLE");
						j += 2;
						break;
					case 4:
						printf(" QUAD ");
						j += 2;
						break;
					default:
						printf("  ");
						break;
					}
					break;
				case 'C':
					switch (combo)
					{
					case -1:
					case 0:
						printf("  ");
						break;
					default:
						printf(" %2d COMBO ", combo);
						j += 4;
						break;
					}
					break;
				case 'A':
					if (All_Clear)
					{
						printf(" ALL CLEAR");
						j += 4;
					}
					else
					{
						printf("  ");
					}
					break;
				case 't':
					if (T_Spin && T_Spin_Print)
					{
						textcolor(0x000D);
						if (T_Spin_Mini)
						{
							printf("t-spin mini ");
							j += 5;
						}
						else
						{
							printf("  t-spin");
							j += 3;
						}
						textcolor(0x000F);
					}
					else
					{
						printf("  ");
					}
					break;
				case 'l':
					printf(" lines: ");
					j += 3;
					break;
				case 'm':
					printf("%4d", num_lines);
					j += 1;
					break;
				case 's':
					printf(" score: ");
					j += 3;
					break;
				case 'u':
					printf("%8d", score);
					j += 3;
					break;
				case 'b':
					printf("CONTINUE");
					j += 3;
					break;
				case 'd':
					printf(" RETURN TO MAIN ");
					j += 7;
					break;
				case 'e':
					printf("40 LINES");
					j += 3;
					break;
				case 'f':
					printf(" BLITZ");
					j += 2;
					break;
				case 'g':
					printf("ZEN ");
					j += 1;
					break;
				case 'h':
					if (isBlitz) {
						printf(" SCORE:   %-10d", score);
						j += 9;
					}
					else if (is40lines) {
						printf("RECORD:   %-10d", record);
						j += 9;
					}
					else{
						printf(" SCORE:   %-10d", score_zen);
						j += 9;
					}
					break;
				case 'i':
					if (isBlitz) {
						if (bestScore < score) bestScore = score;
						printf("BEST SCORE:   %-10d", bestScore);
						j += 11;
					}
					else if (is40lines) {
						if (best_record < record) best_record = record;
						printf("BEST RECORD:   %-11d", best_record);
						j += 12;
					}
					else {
						if (bestScore_zen < score_zen) bestScore_zen = score_zen;
						printf("BEST SCORE:   %-10d", bestScore_zen);
						j += 11;
					}
					break;
				case 'j':
					printf("> CONTINUE <");
					j += 5;
					break;
				case 'k':
					printf("use [left arrow] to move mino left");
					j += 16;
					break;
				case 'n':
					printf("use [down arrow] to softdrop");
					j += 13;
					break;
				case 'o':
					printf("use [space] to harddrop ");
					j += 11;
					break;
				case 'p':
					printf("use [up arrow] / [x] to ");
					j += 11;
					break;
				case 'v':
					printf("rotate mino colckwise ");
					j += 10;
					break;
				case 'q':
					printf("use [z] to rotate mino countercolckwise ");
					j += 19;
					break;
				case 'r':
					printf("use [right arrow] to move mino right");
					j += 17;
					break;
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
				case 'a':
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
					break;
				case 'c':
					switch (cleared_line / 10)
					{
					case 1:
						printf("SINGLE");
						j += 2;
						break;
					case 2:
						printf("DOUBLE");
						j += 2;
						break;
					case 3:
						printf("TRIPLE");
						j += 2;
						break;
					case 4:
						printf(" QUAD ");
						j += 2;
						break;
					default:
						printf("  ");
						break;
					}
					break;
				case 'C':
					switch (combo)
					{
					case -1:
					case 0:
						printf("  ");
						break;
					default:
						printf(" %2d COMBO ", combo);
						j += 4;
						break;
					}
					break;
				case 'A':
					if (All_Clear)
					{
						printf(" ALL CLEAR");
						j += 4;
					}
					else
					{
						printf("  ");
					}
					break;
				case 't':
					if (T_Spin && T_Spin_Print)
					{
						textcolor(0x000D);
						if (T_Spin_Mini)
						{
							printf("T-spin mini ");
							j += 5;
						}
						else
						{
							printf(" T-spin ");
							j += 3;
						}
						textcolor(0x000F);
					}
					else
					{
						printf("  ");
					}
					break;
				case 'l':
					printf(" lines: ");
					j += 3;
					break;
				case 'm':
					printf("%4d", num_lines);
					j += 1;
					break;
				case 's':
					printf(" score: ");
					j += 3;
					break;
				case 'u':
					printf("%8d", score);
					j += 3;
					break;
				case 'b':
					printf("CONTINUE");
					j += 3;
				case 'd':
					printf(" RETURN TO MAIN ");
					j += 7;
					break;
				case 'e':
					printf("40 LINES");
					j += 3;
					break;
				case 'f':
					printf(" BLITZ");
					j += 2;
					break;
				case 'g':
					printf("ZEN ");
					j += 1;
					break;
				case 'h':
					if (isBlitz) {
						printf(" SCORE:   %-10d", score);
						j += 9;
					}
					else if (is40lines) {
						printf("RECORD:   %-10d", record);
						j += 9;
					}
					else {
						printf(" SCORE:   %-10d", score_zen);
						j += 9;
					}
					break;
				case 'i':
					if (isBlitz) {
						if (bestScore < score) bestScore = score;
						printf("BEST SCORE:   %-10d", bestScore);
						j += 11;
					}
					else if (is40lines) {
						if (best_record < record) best_record = record;
						printf("BEST RECORD:   %-11d", best_record);
						j += 12;
					}
					else {
						if (bestScore_zen < score_zen) bestScore_zen = score_zen;
						printf("BEST SCORE:   %-10d", bestScore_zen);
						j += 11;
					}
					break;
				case 'j':
					printf("> CONTINUE <");
					j += 5;
					break;
				case 'k':
					printf("use [left arrow] to move mino left");
					j += 16;
					break;
				case 'n':
					printf("use [down arrow] to softdrop");
					j += 13;
					break;
				case 'o':
					printf("use [space] to harddrop ");
					j += 11;
					break;
				case 'p':
					printf("use [up arrow] / [x] to ");
					j += 11;
					break;
				case 'v':
					printf("rotate mino colckwise ");
					j += 10;
					break;
				case 'q':
					printf("use [z] to rotate mino countercolckwise ");
					j += 19;
					break;
				case 'r':
					printf("use [right arrow] to move mino right");
					j += 17;
					break;
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
			else if (c[j] >= 97 && c[j] <= 123)
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


void textcolor(int ColorNum)
{
	HANDLE _stdcall stdhandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(stdhandle, ColorNum);
	return;
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
		exit(0);
	}

	LastElement->next->fallingmino = fallingmino;
	for (int i = 0; i < 20; i++) {
		LastElement->next->hold[i] = Hold[i];
		LastElement->next->nextmino[i] = NextMino[i];
	}
	LastElement->next->IsHolded = IsHolded;
	for (int i = 0; i <= SCREEN_END_Y; i++) {
		for (int j = SCREEN_START_X; j <= SCREEN_END_X; j++)
			LastElement->next->screen[i][j] = screen[i][j];
	}
	LastElement->next->combo = combo;
	LastElement->next->cleared_line = cleared_line;
	LastElement->next->score = score;
	LastElement->next->num_lines = num_lines;
	LastElement->next->T_Spin = T_Spin;
	LastElement->next->T_Spin_Mini = T_Spin_Mini;
	LastElement->next->T_Spin_Print = T_Spin_Print;
	return;
}


struct MyHeadType* MakeStack()
{
	struct MyHeadType* MyHead = (struct MyHeadType*)malloc(sizeof(struct MyHeadType));
	if (MyHead == NULL)
	{
		printf("동적 메모리 할당에 실패했습니다.");
		exit(0);
	}
	MyHead->count = 0;
	MyHead->next = NULL;

	MyHead->next = (struct MyMemoryType*)malloc(sizeof(struct MyMemoryType));
	if (MyHead->next == NULL)
	{
		printf("동적 메모리 할당에 실패했습니다.");
		exit(0);
	}
	MyHead->next->next = NULL;
	return MyHead;
}


void mode_select_screen(int screen[][100])
{
	FILE* fp = fopen("selectmode.txt", "r");
	load_map(fp, screen);
	gotoxy(0, 0);
	print_screen(screen);

	int selected = 0;
	while (1)
	{
		switch (selected)
		{
		case 0:
			gotoxy(11, 17);
			printf(" ");
			gotoxy(36, 17);
			printf(" ");
			gotoxy(11, 21);
			printf(" ");
			gotoxy(36, 21);
			printf(" ");
			gotoxy(11, 15);
			printf(">");
			gotoxy(36, 15);
			printf("<");
			break;
		case 1:
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
		case 2:
			gotoxy(11, 17);
			printf(" ");
			gotoxy(36, 17);
			printf(" ");
			gotoxy(11, 21);
			printf(" ");
			gotoxy(36, 21);
			printf(" ");
			gotoxy(11, 19);
			printf(">");
			gotoxy(36, 19);
			printf("<");
			break;
		case 3:
			gotoxy(11, 15);
			printf(" ");
			gotoxy(36, 15);
			printf(" ");
			gotoxy(11, 19);
			printf(" ");
			gotoxy(36, 19);
			printf(" ");
			gotoxy(11, 21);
			printf(">");
			gotoxy(36, 21);
			printf("<");
			break;
		default:
			break;
		}
		char c = _getch();
		switch (c)
		{
		case -32:
			soundEffect("sys_select.mp3", &system_select, &dwID_select, true, false, false);
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
			soundEffect("sys_ok.mp3", &system_ok, &dwID_ok, true, false, false);
			if (selected == 0)//zen
			{
				isZen = true;
				return;
			}
			else if (selected == 1)//40lines
			{
				is40lines = true;
				return;
			}
			else if (selected == 2)//blits
			{
				isBlitz = true;
				return;
			}
			else if (selected == 3)//return to main
			{
				isZen = isBlitz = is40lines = false;
				isTutorial = 0;
				return;
			}
			break;
		}
	}
	return;
}


void game_result(int screen[][100])
{
	FILE* fp = fopen("gameresult.txt", "r");
	load_map(fp, screen);
	fclose(fp);

	gotoxy(0, 0);
	print_screen(screen);

	while (1)
	{
		if (_kbhit())
		{
			char c = _getch();
			if (c == ' ') return;
		}
	}

	return;
}


void main_screen(struct MyHeadType* MyHead, int screen[][100])
{

	soundEffect("TetrisTheme.mp3", &bgm, &dwID_bgm, false, false, false);
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
			soundEffect("sys_select.mp3", &system_select, &dwID_select, true, false, false);
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
			soundEffect("sys_ok.mp3", &system_ok, &dwID_ok, true, false, false);
			if (selected == 0)//game start
			{
				mode_select_screen(screen);
				return;
			}
			else if (selected == 1)//settings
			{

			}
			else if (selected == 2)//help
			{
				help_screen(screen);
			}
			else if (selected == 3)//exit game
			{
				free(MyHead);
				save_record();
				exit(0);
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

void game_over(int screen[][100])
{
	IsGamePlaying = false;

	if (IsInstantRetry)
	{
		IsRetry = true;
		return;
	}

	soundEffect("TetrisTheme.mp3", &bgm, &dwID_bgm, false, false, false);
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


void Pause()
{
	GamePause = true;
	int selected = 0;

	FILE* fp = fopen("pause.txt", "r");
	load_map(fp, screen1);
	fclose(fp);
	gotoxy(0, 0);
	print_screen(screen1);
	gotoxy(11, 17);
	printf(">");
	gotoxy(36, 17);
	printf("<");
	while (1)
	{
		if (_kbhit)
		{
			char c = _getch();
			if (c == ' ')
			{
				soundEffect("sys_ok.mp3", &system_ok, &dwID_ok, true, false, false);
				if (selected == 0)
				{
					GamePause = false;
					break;
				}
				else
				{
					GamePause = false;
					IsGamePlaying = false;
					break;
				}
			}
			else if (c == -32)
			{
				c = _getch();
				switch (c)
				{
				case 72://위
				case 80://아래
					soundEffect("sys_select.mp3", &system_select, &dwID_select, true, false, false);
					selected = (selected + 1) % 2;
					if (selected == 0) {
						gotoxy(11, 17);
						printf(">");
						gotoxy(36, 17);
						printf("<");
						gotoxy(11, 19);
						printf(" ");
						gotoxy(36, 19);
						printf(" ");
					}
					else {
						gotoxy(11, 17);
						printf(" ");
						gotoxy(36, 17);
						printf(" ");
						gotoxy(11, 19);
						printf(">");
						gotoxy(36, 19);
						printf("<");
					}
					break;
				default:
					break;
				}
			}
		}
	}

	return;
}


void soundEffect(char filePath[], MCI_OPEN_PARMS* soundEffect, int* dwID, bool playing, bool repeat, bool load) {

	soundEffect->lpstrElementName = filePath;//파일 오픈
	soundEffect->lpstrDeviceType = "mpegvideo";//mp3 형식
	*dwID = soundEffect->wDeviceID;
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID) & *soundEffect);

	if (!load)
	{
		if (playing) {
			if (repeat) {
				mciSendCommand(*dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID) & *soundEffect); //음악 반복 재생
			}
			else {
				mciSendCommand(*dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL); //음원 재생 위치를 처음으로 초기화
				mciSendCommand(*dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID) & *soundEffect);	//음악 한 번만 재생
			}
		}
		else {
			mciSendCommand(*dwID, MCI_PAUSE, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID) & *soundEffect);	//음악 재생 중지
			mciSendCommand(*dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL); //음원 재생 위치를 처음으로 초기화
		}
	}
	return;
}


void load_record()
{
	FILE* fp = fopen("bestscore.txt", "r");
	if (fp == NULL)
	{
		return;
	}
	else {
		fscanf(fp, "%d %d %d", &bestScore, &bestScore_zen, &best_record);
		fclose(fp);
	}

	return;
}

void save_record()
{
	FILE* fp = fopen("bestscore.txt", "w");
	if (fp == NULL)
	{
		return;
	}
	else {
		fprintf(fp, "%d %d %d", bestScore, bestScore_zen, best_record);
		fclose(fp);
	}

	return;
}

void help_screen(int screen[][100])
{
	FILE* fp = fopen("help.txt", "r");
	if (fp == NULL)
	{
		printf("error!");
		Sleep(10000);
		return;
	}
	
	load_map(fp, screen);
	gotoxy(0, 0);
	print_screen(screen);

	char c;

	while (_kbhit) c = _getch();

	while (1)
	{
		if (_kbhit())
		{
			c = _getch();
			if (c == ' ')
			{
				break;
			}
		}
	}

	return;
}