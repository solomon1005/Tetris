#include "system.h"


struct MyHeadType
{
	int count;
	struct MyMemoryType* next;
};

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

int All_Clear = 0;
int cleared_line = 0;
int combo = 0;
int T_Spin = 0;
bool T_Spin_Mini = false;
bool T_Spin_Print = false;
int num_lines = 0;
int score = 0;
bool IsHolded = false;





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
					printf("continue");
					j += 3;
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
					printf("continue");
					j += 3;
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