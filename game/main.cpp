#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "Console.h"
#include <iostream>

using namespace std;
using namespace game;

#define MAX 40
#define BACKCOLOR 15 // white 

struct ST_OBJECT
{
	int x = 0;  
	int y = 0;
	bool bActive = false;
};

int g_score = 0;
ST_OBJECT g_stEnemy[MAX];
ST_OBJECT g_stPlayer;
ST_OBJECT g_stBullet[10];

void Spawn(void) // enemies appear
{
	for (int i = 0; i < MAX; i++)
	{
		if (!g_stEnemy[i].bActive)
		{
			g_stEnemy[i].x = (rand() % 20) * 2; 
			g_stEnemy[i].y = 0;
			g_stEnemy[i].bActive = true;
			break;
		}
	}
}

void InputProcess(void)
{
	// player move 
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		g_stPlayer.x -= 2; 
		if (g_stPlayer.x < 0) g_stPlayer.x = 0;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		g_stPlayer.x += 2;
		if (g_stPlayer.x > 38) g_stPlayer.x = 38;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		g_stPlayer.y -= 1;
		if (g_stPlayer.y < 0) g_stPlayer.y = 0;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		g_stPlayer.y += 1;
		if (g_stPlayer.y > 39) g_stPlayer.y = 39;
	}

	// launch missile
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		for(int i=0 ; i<5; i++)
		{
		if (!g_stBullet[i].bActive) 
		{
			g_stBullet[i].x = g_stPlayer.x;
			g_stBullet[i].y = g_stPlayer.y - 1;
			g_stBullet[i].bActive = true;
			break;
		}

		if (g_stBullet[i].y == 0)
		{
			g_stBullet[i].x = g_stPlayer.x;
			g_stBullet[i].y = g_stPlayer.y - 1;
		}
		}
	}
}

int EnemyProcess(void) 
{
	int count = 0;
	for (int i = 0; i < MAX; i++)
	{
		if (g_stEnemy[i].bActive)
		{
			GotoXY(g_stEnemy[i].x, g_stEnemy[i].y);
			SetColor(BACKCOLOR, i % 15); // 15 different colors enemies
			printf("¡Ú");
			count++;

			g_stEnemy[i].y++;
			
			// player collides with stars
			if (((g_stEnemy[i].x == g_stPlayer.x) && (g_stEnemy[i].y == g_stPlayer.y)) || ((g_stEnemy[i].x == g_stPlayer.x) && (g_stEnemy[i].y == g_stPlayer.y + 1)))
			{
				g_stPlayer.bActive = false;
			}

			if (g_stEnemy[i].y > 39)
			{
				g_stEnemy[i].bActive = false;
			}

		}
	}
	return count;
}

void Update(void)
{
	SetColor(BACKCOLOR, 12);

	if (g_stPlayer.bActive)
	{
		// player alive
		GotoXY(g_stPlayer.x, g_stPlayer.y);
		printf("¡ã");

	}
	else
	{
		// player dead
		GotoXY(g_stPlayer.x, g_stPlayer.y);
		printf("¢Æ");
		for(int i =0 ; i<5; i++)
		{
		g_stBullet[i].bActive = false;
		}
	}

	for(int i =0; i<5; i++)
	{
	if (g_stBullet[i].bActive)  
	{
		GotoXY(g_stBullet[i].x, g_stBullet[i].y);
		printf("¡è");
		g_stBullet[i].y--;
		if (g_stBullet[i].y < 0) g_stBullet[i].bActive = false;
	}
	if (!g_stBullet[i].bActive)
	{
		g_stBullet[i].x = g_stPlayer.x;
		g_stBullet[i].y = g_stPlayer.y;
	}
	}
}
void Collapse(void)
{
	// bullet crash into stars
	for(int i = 0 ; i<5 ; i++)
	{
	if (g_stBullet[i].bActive) 
	{

		for (int j = 0; j < MAX; j++)
		{
			if (((g_stBullet[i].x == g_stEnemy[j].x) && (g_stBullet[i].y == g_stEnemy[j].y)) || ((g_stBullet[i].x == g_stEnemy[j].x) && (g_stBullet[i].y + 1 == g_stEnemy[j].y)))
			{
				g_score += 100;
				g_stEnemy[j].bActive = false;

				g_stEnemy[j].x += 40;
				g_stEnemy[j].y += 40;

				g_stBullet[i].bActive = false;


				break;
			}
		}
	}
	}
}

void Init(void)
{
	// initialize
	SetConsoleSize(40, 40);

	g_stPlayer.x = 18;
	g_stPlayer.y = 38;
	g_stPlayer.bActive = true; 

	// maximum 5 bullets are available.
	for (int i = 0; i < 5; i++)
	{
		g_stBullet[i].x = g_stPlayer.x;
		g_stBullet[i].y = g_stPlayer.y;
		g_stBullet[i].bActive = false;
	}
	
	SetCursor(false);
	srand(time(NULL)); 
	SetTitle("Galaga"); 
	SetColor(BACKCOLOR, 0);

}


void Score(void)
{
	if (g_stPlayer.bActive == 1)
	{
		g_score++;
	}
	SetColor(BACKCOLOR, 0);
	GotoXY(0, 0);
	printf("Score : %d", g_score);
}


void StartMenu(void)
{
	while (_kbhit()) _getch(); 

	while (1)
	{
		Clear();
		GotoXY(16, 10);
		printf("Galaga");
		GotoXY(16, 20);
		printf("press any key...");
		if (_kbhit()) break;  
		Sleep(50);
	}
}

void GameMain()
{
	g_score = 0;
	while (1)
	{
		Clear();

		if (g_stPlayer.bActive)
		{
			Spawn();
			InputProcess();
		}

		int state = EnemyProcess();
		if (state == 0) break;

		Update();
		Collapse();
		Score();
		Sleep(40);
	}
}

bool ResultMenu(void)
{
	bool bRet; 
	while (1)
	{
		Clear();
		GotoXY(15, 10);
		printf("Result Menu");
		GotoXY(15, 13);
		printf("Score : %d", g_score);
		GotoXY(15, 20);
		printf("Continue...(Y/N)");
		if (GetAsyncKeyState('Y') & 0x8000)
		{
			bRet = 0;
			break;
		}
		if (GetAsyncKeyState('N') & 0x8000)
		{
			bRet = 1;
			break;
		}

		Sleep(100);
	}
	return bRet;
}

int main(void)
{
	while (1)
	{
		Init();
		StartMenu();
		GameMain();
		if (ResultMenu()) break;
	}

	system("pause");
	return 0;
}
