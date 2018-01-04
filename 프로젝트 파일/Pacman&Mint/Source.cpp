#include <windows.h>
#include <stdio.h>
#include "resource.h"
#include <MMSystem.h>
#include "Digitalv.h"
#include "Mmsystem.h"

#pragma comment(lib,"msimg32.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#define speed 4;
#define Gspeed 5;
#define Endspeed 3;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CALLBACK DoubleBuffering(HWND hWnd, UINT uMsg, UINT ibEvent, DWORD dwTime);
void GhostAI();
void OUTConflictHandling(RECT rc);
void INConflictHandling(int left, int top, int right, int bottom);
void RectAngleManager(HDC hDC, RECT rect);
void GhostConflictHandling(RECT Ghost1, RECT Ghost2, RECT Ghost3, RECT Ghost4);
DWORD LoadWav(HWND hWnd, LPCTSTR lpszWave);

MCI_OPEN_PARMS mciOpen; // Load File
MCI_PLAY_PARMS mciPlay; // Play File
MCI_STATUS_PARMS   mciStatus; // File State
UINT wDeviceID = 0;

HINSTANCE g_hInst;

LPCWSTR lpszClass = TEXT("First");

HBITMAP PM[3][8];
HBITMAP GHOST[3][4];
HBITMAP CandyBit[2];
HBITMAP map[6];
HBITMAP MainB[4];
HBITMAP Arrow[1];
HBITMAP Intro[7];
HBITMAP N[10];
HBITMAP UI[5];
HBITMAP GameOverB[3];
HBITMAP MINT[3][2];
HBITMAP GameClearB;


RECT WALL[9][22];
RECT CandyArea[5][9][22];
RECT Temp_;
RECT Princess = {920, 360, 1000,440};
RECT EndRect = {920, 680, 1000,760};

bool WallTrue[9][22];

DWORD Sound1;
DWORD Sound2;
DWORD Sound3;
DWORD Sound4;
DWORD Sound5;

enum CandyCondition { not, candy , kirat};

int x = 0, y = 0;
RECT player = { 80, 280, 160, 360 };
RECT playerC = { 15, 0, 65, 80 };
RECT playerR = { 95, 300, 145, 360 };
RECT Ghost1 = { 1760, 920, 1840, 1000 };
RECT Ghost2 = { 1760, 280, 1840, 360 };
RECT Ghost3 = { 880, 280, 960, 360 };
RECT Ghost4 = { 960, 920, 1040, 1000 };
RECT Ghost5 = { 80, 500, 160, 580 };
RECT Ghost6 = { 80, 920, 160, 1000 };
RECT Ghost1R = { Ghost1.left + 20, Ghost1.top + 10, Ghost1.right - 20, Ghost1.bottom - 10 };
RECT Ghost2R = { Ghost2.left + 20, Ghost2.top + 10, Ghost2.right - 20, Ghost2.bottom - 10 };
RECT Ghost3R = { Ghost3.left + 20, Ghost3.top + 10, Ghost3.right - 20, Ghost3.bottom - 10 };
RECT Ghost4R = { Ghost4.left + 20, Ghost4.top + 10, Ghost4.right - 20, Ghost4.bottom - 10 };
RECT Ghost5R = { Ghost5.left + 20, Ghost5.top + 10, Ghost5.right - 20, Ghost5.bottom - 10 };
RECT Ghost6R = { Ghost6.left + 20, Ghost6.top + 10, Ghost6.right - 20, Ghost6.bottom - 10 };



static RECT ArrowR = { 580, 657, 648, 654 };

int Candy[9][22];
int Mouse = 0;
int GhostMouse = 0;
int direction = 0;
int GhostMove1 = 0;
int GhostMove2 = 0;
int GhostMove3 = 0;
int GhostMove4 = 0;
int dirManager = 0;
int MouseManager = 0;
int stage = 0;
int CandyNum = 198;
int CandyTemp = 0;
int CandyManager = 0;
int Life = 2;
int InGame = 0;
int Main = 1;
int MainNum = 0;
int IntroM = -1;
int N1 = 0;
int N10 = 0;
int N100 = 0;
int GameOver = 0;
int GameClear = 0;
int Textdown = 0;
int Pressenter = 0;
int GManager = 0;

int Ending = 0;

int Mdirection = 0;

int GameEndPX = 920;
int GameEndPY = 680;

int CandyCheck[9][22] = 
{ { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }};

bool stage_1[9][22] =
{ { 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
{ 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1 },
{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1 },
{ 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1 },
{ 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1 },
{ 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1 },
{ 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1 },
{ 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1 },
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1 } };

bool stage_2[9][22] =
{ { 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1 },
{ 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1 },
{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1 },
{ 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1 },
{ 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1 },
{ 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1 },
{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1 },
{ 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1 },
{ 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1 } };

bool stage_3[9][22] =
{ { 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1 },
{ 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1 },
{ 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1 },
{ 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1 },
{ 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1 },
{ 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1 },
{ 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1 },
{ 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1 },
{ 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1 } };

bool stage_4[9][22] =
{ { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1 },
{ 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1 },
{ 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1 },
{ 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1 },
{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1 },
{ 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1 },
{ 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1 },
{ 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1 },
{ 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } };

bool stage_5[9][22] =
{ { 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1 },
{ 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1 },
{ 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1 },
{ 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1 },
{ 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1 },
{ 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1 },
{ 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1 },
{ 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1 },
{ 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1 } };

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_POPUPWINDOW,
		0, 0, 1920, 1080,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	Sound1 = LoadWav(hWnd, L"./Resource/BGM/mp3/MAIN.mp3");
	Sound2 = LoadWav(hWnd, L"./Resource/BGM/mp3/Intro.mp3");
	Sound3 = LoadWav(hWnd, L"./Resource/BGM/mp3/InGame.mp3");
	Sound4 = LoadWav(hWnd, L"./Resource/BGM/mp3/GameOver.mp3");
	Sound5 = LoadWav(hWnd, L"./Resource/BGM/mp3/GameClear.mp3");

	if (Main == 1)
		Sound1 = mciSendCommand(1, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC   hdc;
	PAINTSTRUCT ps;



	switch (iMessage) {
	case WM_CREATE:

		// Main
		MainB[0] = (HBITMAP)LoadImage(NULL, L"./Resource/Main/Title.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		MainB[1] = (HBITMAP)LoadImage(NULL, L"./Resource/Main/Start.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		MainB[2] = (HBITMAP)LoadImage(NULL, L"./Resource/Main/Quit.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		MainB[3] = (HBITMAP)LoadImage(NULL, L"./Resource/Main/Title.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		Arrow[0] = (HBITMAP)LoadImage(NULL, L"./Resource/Main/arrow.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		// Clear
		GameClearB = (HBITMAP)LoadImage(NULL, L"./Resource/GameClear/clear.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		// Intro
		Intro[0] = (HBITMAP)LoadImage(NULL, L"./Resource/Intro/Intro_00.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		Intro[1] = (HBITMAP)LoadImage(NULL, L"./Resource/Intro/Intro_01.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		Intro[2] = (HBITMAP)LoadImage(NULL, L"./Resource/Intro/Intro_02.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		Intro[3] = (HBITMAP)LoadImage(NULL, L"./Resource/Intro/Intro_03.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		Intro[4] = (HBITMAP)LoadImage(NULL, L"./Resource/Intro/Intro_04.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		Intro[5] = (HBITMAP)LoadImage(NULL, L"./Resource/Intro/Intro_05.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		Intro[6] = (HBITMAP)LoadImage(NULL, L"./Resource/Intro/Intro_06.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		// UI
		N[0] = (HBITMAP)LoadImage(NULL, L"./Resource/UI/0.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		N[1] = (HBITMAP)LoadImage(NULL, L"./Resource/UI/1.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		N[2] = (HBITMAP)LoadImage(NULL, L"./Resource/UI/2.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		N[3] = (HBITMAP)LoadImage(NULL, L"./Resource/UI/3.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		N[4] = (HBITMAP)LoadImage(NULL, L"./Resource/UI/4.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		N[5] = (HBITMAP)LoadImage(NULL, L"./Resource/UI/5.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		N[6] = (HBITMAP)LoadImage(NULL, L"./Resource/UI/6.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		N[7] = (HBITMAP)LoadImage(NULL, L"./Resource/UI/7.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		N[8] = (HBITMAP)LoadImage(NULL, L"./Resource/UI/8.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		N[9] = (HBITMAP)LoadImage(NULL, L"./Resource/UI/9.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		UI[0] = (HBITMAP)LoadImage(NULL, L"./Resource/UI/Floor.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		UI[1] = (HBITMAP)LoadImage(NULL, L"./Resource/UI/Floor_H.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		UI[2] = (HBITMAP)LoadImage(NULL, L"./Resource/UI/Life.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		UI[3] = (HBITMAP)LoadImage(NULL, L"./Resource/UI/UI.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		UI[4] = (HBITMAP)LoadImage(NULL, L"./Resource/UI/Garigea.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		// GameOver
		GameOverB[0] = (HBITMAP)LoadImage(NULL, L"./Resource/GameOver/GAME_OVER.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GameOverB[1] = (HBITMAP)LoadImage(NULL, L"./Resource/GameOver/GameOver.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GameOverB[2] = (HBITMAP)LoadImage(NULL, L"./Resource/GameOver/PressEnter.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		// Pacman Bitmap [Mouse][Direction]
		PM[0][0] = (HBITMAP)LoadImage(NULL, L"./Resource/Pacman/P.left 1.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		PM[0][1] = (HBITMAP)LoadImage(NULL, L"./Resource/Pacman/P.up 1.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		PM[0][2] = (HBITMAP)LoadImage(NULL, L"./Resource/Pacman/P.right 1.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		PM[0][3] = (HBITMAP)LoadImage(NULL, L"./Resource/Pacman/P.down 1.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		PM[0][4] = (HBITMAP)LoadImage(NULL, L"./Resource/Pacman/P.down 1.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		PM[0][5] = (HBITMAP)LoadImage(NULL, L"./Resource/Pacman/Death3.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		PM[0][6] = (HBITMAP)LoadImage(NULL, L"./Resource/Pacman/Death2.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		PM[0][7] = (HBITMAP)LoadImage(NULL, L"./Resource/Pacman/Death1.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		PM[1][0] = (HBITMAP)LoadImage(NULL, L"./Resource/Pacman/P.left 2.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		PM[1][1] = (HBITMAP)LoadImage(NULL, L"./Resource/Pacman/P.up 2.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		PM[1][2] = (HBITMAP)LoadImage(NULL, L"./Resource/Pacman/P.right 2.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		PM[1][3] = (HBITMAP)LoadImage(NULL, L"./Resource/Pacman/P.down 2.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		PM[1][4] = (HBITMAP)LoadImage(NULL, L"./Resource/Pacman/P.down 1.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		PM[1][5] = (HBITMAP)LoadImage(NULL, L"./Resource/Pacman/Death3.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		PM[1][6] = (HBITMAP)LoadImage(NULL, L"./Resource/Pacman/Death2.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		PM[1][7] = (HBITMAP)LoadImage(NULL, L"./Resource/Pacman/Death1.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		PM[2][0] = (HBITMAP)LoadImage(NULL, L"./Resource/Pacman/P.left 3.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		PM[2][1] = (HBITMAP)LoadImage(NULL, L"./Resource/Pacman/P.up 3.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		PM[2][2] = (HBITMAP)LoadImage(NULL, L"./Resource/Pacman/P.right 3.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		PM[2][3] = (HBITMAP)LoadImage(NULL, L"./Resource/Pacman/P.down 3.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		PM[2][4] = (HBITMAP)LoadImage(NULL, L"./Resource/Pacman/P.down 1.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		PM[2][5] = (HBITMAP)LoadImage(NULL, L"./Resource/Pacman/Death3.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		PM[2][6] = (HBITMAP)LoadImage(NULL, L"./Resource/Pacman/Death2.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		PM[2][7] = (HBITMAP)LoadImage(NULL, L"./Resource/Pacman/Death1.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		// MINT
		MINT[0][0] = (HBITMAP)LoadImage(NULL, L"./Resource/Mint/후정.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		MINT[0][1] = (HBITMAP)LoadImage(NULL, L"./Resource/Mint/정.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		MINT[1][0] = (HBITMAP)LoadImage(NULL, L"./Resource/Mint/후왼.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		MINT[1][1] = (HBITMAP)LoadImage(NULL, L"./Resource/Mint/정왼.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		MINT[2][0] = (HBITMAP)LoadImage(NULL, L"./Resource/Mint/후오.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		MINT[2][1] = (HBITMAP)LoadImage(NULL, L"./Resource/Mint/정오.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		// Ghost
		GHOST[0][0] = (HBITMAP)LoadImage(NULL, L"./Resource/Ghost/G_left 1.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GHOST[0][1] = (HBITMAP)LoadImage(NULL, L"./Resource/Ghost/G_up 1.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GHOST[0][2] = (HBITMAP)LoadImage(NULL, L"./Resource/Ghost/G_right 1.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GHOST[0][3] = (HBITMAP)LoadImage(NULL, L"./Resource/Ghost/G_down 1.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		GHOST[1][0] = (HBITMAP)LoadImage(NULL, L"./Resource/Ghost/G_left 2.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GHOST[1][1] = (HBITMAP)LoadImage(NULL, L"./Resource/Ghost/G_up 2.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GHOST[1][2] = (HBITMAP)LoadImage(NULL, L"./Resource/Ghost/G_right 2.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GHOST[1][3] = (HBITMAP)LoadImage(NULL, L"./Resource/Ghost/G_down 2.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		GHOST[2][0] = (HBITMAP)LoadImage(NULL, L"./Resource/Ghost/G_left 3.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GHOST[2][1] = (HBITMAP)LoadImage(NULL, L"./Resource/Ghost/G_up 3.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GHOST[2][2] = (HBITMAP)LoadImage(NULL, L"./Resource/Ghost/G_right 3.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GHOST[2][3] = (HBITMAP)LoadImage(NULL, L"./Resource/Ghost/G_down 3.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		// Item

		CandyBit[candy] = (HBITMAP)LoadImage(NULL, L"./Resource/Item/Candy.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);


		// Map
		map[0] = (HBITMAP)LoadImage(NULL, L"./Resource/Map/Stage_1.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		map[1] = (HBITMAP)LoadImage(NULL, L"./Resource/Map/Stage_2.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		map[2] = (HBITMAP)LoadImage(NULL, L"./Resource/Map/Stage_3.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		map[3] = (HBITMAP)LoadImage(NULL, L"./Resource/Map/Stage_4.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		map[4] = (HBITMAP)LoadImage(NULL, L"./Resource/Map/Stage_5.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		map[5] = (HBITMAP)LoadImage(NULL, L"./Resource/Map/ClearStage.bmp", IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		// Timer

		SetTimer(hWnd, 1, 1, (TIMERPROC)DoubleBuffering);

		SetTimer(hWnd, 2, 10, NULL);
		SetTimer(hWnd, 3, 250, NULL);
		SetTimer(hWnd, 4, 10, (TIMERPROC)GhostAI);
		SetTimer(hWnd, 5, 250, NULL);
		SetTimer(hWnd, 6, 1000, NULL);
		SetTimer(hWnd, 8, 9000, NULL);
		if (GameOver == 1)
		{
			SetTimer(hWnd, 7, 100, NULL);
		}
		SetTimer(hWnd, 9, 10, NULL);
		SetTimer(hWnd, 10, 250, NULL);
		return 0;

	case WM_TIMER:
	case 10:
		if (GameClear == 1)
		{
			switch (MouseManager)
			{
			case 0:
				if (dirManager == 0)
				{
					Mouse = 1;
					MouseManager = 1;
				}
				else
				{
					Mouse = 2;
					MouseManager = 2;
				}
				break;
			case 1:
				Mouse = 0;
				MouseManager = 0;
				dirManager += 1;
				break;
			case 2:
				Mouse = 0;
				MouseManager = 0;
				dirManager -= 1;
			case 3:
				Mouse = 0;

				break;
			default:
				break;
			}
		}
	case 9:
		if (GameClear == 1)
		{
			switch (direction)
			{

			case 1:
				GameEndPY -= Endspeed;

				if (Princess.bottom > GameEndPY)
				{
					GameEndPY += Endspeed;
					Mdirection = 1;
				}
				break;

			case 3:
				GameEndPY += Endspeed;
				if (Mdirection == 1)
				Princess.top += Endspeed;

				if (GameEndPY > 680)
					GameEndPY -= Endspeed;
				break;


			default:
				break;

			}
		}
		if (InGame == 1)
		{
			switch (wParam)
			{
			case 2:

				switch (direction)
				{
				case 0:
					player.left -= speed;
					player.right -= speed;
					playerR.left -= speed;
					playerR.right -= speed;
					playerC.left -= speed;
					playerC.right -= speed;
					break;

				case 1:
					player.top -= speed;
					player.bottom -= speed;
					playerR.top -= speed;
					playerR.bottom -= speed;
					playerC.top -= speed;
					playerC.bottom -= speed;
					break;

				case 2:
					player.left += speed;
					player.right += speed;
					playerR.left += speed;
					playerR.right += speed;
					playerC.left += speed;
					playerC.right += speed;
					break;

				case 3:
					player.top += speed;
					player.bottom += speed;
					playerR.top += speed;
					playerR.bottom += speed;
					playerC.top += speed;
					playerC.bottom += speed;
					break;


				default:
					break;
				}

				Ghost1R = { Ghost1.left + 20, Ghost1.top + 10, Ghost1.right - 20, Ghost1.bottom - 10 };
				Ghost2R = { Ghost2.left + 20, Ghost2.top + 10, Ghost2.right - 20, Ghost2.bottom - 10 };
				Ghost3R = { Ghost3.left + 20, Ghost3.top + 10, Ghost3.right - 20, Ghost3.bottom - 10 };
				Ghost4R = { Ghost4.left + 20, Ghost4.top + 10, Ghost4.right - 20, Ghost4.bottom - 10 };

				GhostConflictHandling(Ghost1R, Ghost2R, Ghost3R, Ghost4R);

				break;

			case 3:
				switch (MouseManager)
				{
				case 0:
					if (dirManager == 0)
					{
						Mouse = 1;
						MouseManager = 1;
					}
					else
					{
						Mouse = 2;
						MouseManager = 2;
					}
					break;
				case 1:
					Mouse = 0;
					MouseManager = 0;
					dirManager += 1;
					break;
				case 2:
					Mouse = 0;
					MouseManager = 0;
					dirManager -= 1;
				case 3:
					Mouse = 0;

					break;
				default:
					break;
				}

				break;

			case 5:

				switch (GhostMouse)
				{
				case 0:
					GhostMouse++;
					break;
				case 1:
					GhostMouse--;
					break;


					break;
				default:
					break;
				}

			case 6:
				switch (direction)
				{
				case 5:
					direction++;
					break;


				case 6:
					direction++;
					break;

				case 7:
					player = { 80, 280, 160, 360 };
					playerC = { 15, 0, 65, 80 };
					playerR = { 95, 300, 145, 360 };
					direction = 4;
					Ghost1 = { 1760, 920, 1840, 1000 };
					Ghost2 = { 1760, 280, 1840, 360 };
					Ghost3 = { 880, 280, 960, 360 };
					Ghost4 = { 960, 920, 1040, 1000 };
					Life -= 1;

					if (Life <= 0)
					{
						InGame--;
						GameOver++;
					}
					break;

				default:
					break;
				}

			case 8:
				if (InGame == 1)
				{
					GManager++;
					if (GManager == rand() % 100)
					{
						GhostMove3 = rand() % 4;
						GManager = 0;
					}
					if (GManager == rand() % 100)
					{
						GhostMove2 = rand() % 4;
						GManager = 0;
					}
					if (GManager == rand() % 100)

					{
						GManager = 0;
						GhostMove1 = rand() % 4;
					}
					if (GManager == rand() % 100)
					{
						GManager = 0;
						GhostMove4 = rand() % 4;
					}
				}

				break;
			}


	case 7:
		if (GameOver == 1)
		{
			if (Textdown <= 250)
				Textdown += 10;
			else
			{
				Pressenter = 1;
			}

	default:
		break;
		}

		}
	
	

		return 0;

	case WM_KEYDOWN:
		if (IntroM >= 0 && IntroM <= 7)
		{
			
			switch (wParam)
			{
			case VK_LEFT:
				IntroM--;
				if (IntroM < 0)
					IntroM++;
				break;
			case VK_RIGHT:
				IntroM++;
				if (IntroM > 6)
				IntroM--;
				break;
			case VK_RETURN:
				IntroM = 8;
				InGame = 1;
				Sound2 = mciSendCommand(2, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
				Sound3 = mciSendCommand(3, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);


				break;
			}
		}
		if (Main == 1)
		{
			switch (wParam)
			{
			case VK_DOWN:
				MainNum++;
				ArrowR.top += 115;
				ArrowR.bottom += 115;
				if (MainNum > 1)
				{
					MainNum--;
					ArrowR.top -= 115;
					ArrowR.bottom -= 115;
				}
				break;

			case VK_UP:

				ArrowR.top -= 115;
				ArrowR.bottom -= 115;
				MainNum--;
				if (MainNum < 0)
				{
					MainNum++;
					ArrowR.top += 115;
					ArrowR.bottom += 115;
				}
				break;

			case VK_RETURN:
				if (MainNum == 0)
				{
					Main = 0;
					IntroM = 0;
					Sound1 = mciSendCommand(1, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
					Sound2 = mciSendCommand(2, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
				}
				else if (MainNum == 1)
					SendMessage(hWnd, WM_CLOSE, 0, 0);
				break;
			}
		}
		
		if (InGame == 1)
		{
			if (direction < 5)
			{
				switch (wParam)
				{
				case VK_SHIFT:
					CandyNum = 0;
					break;
				case VK_CONTROL:
					InGame = 0;
					GameOver = 1;
					break;

				case VK_LEFT:
					direction = 0;
					MouseManager = 0;
					break;

				case VK_UP:
					direction = 1;
					MouseManager = 0;
					break;

				case VK_RIGHT:
					direction = 2;
					MouseManager = 0;
					break;

				case VK_DOWN:
					direction = 3;
					MouseManager = 0;
					break;

				default:
					break;
				}
			}
		}
		if (GameOver == 1)
		{
			switch (wParam)
			{
			case VK_RETURN:
				SendMessage(hWnd, WM_CLOSE, 0, 0);
				break;
			}
			
		}
		if (GameClear == 1)
		{
			printf("1");
			switch (wParam)
			{
			case VK_UP:
				Mouse = 0;
				dirManager = 0;
				direction = 1;
				printf("1");
				break;

			case VK_DOWN:
				Mouse = 0;
				dirManager = 0;
				direction = 3;
				break;

			default:
				break;

			}
		}
		if (Ending == 1)
		{
			switch (wParam)
			{
			case VK_RETURN:
				SendMessage(hWnd, WM_CLOSE, 0, 0);
				break;
			default:
				break;

			}
		}
		return 0;
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = 1920;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = 1080;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 1920;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 1080;
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		DeleteDC(hdc);
		EndPaint(hWnd, &ps);


		return 0;

	case WM_DESTROY:
		if (wDeviceID > 0)
		{
			mciSendCommand(1, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
			mciSendCommand(2, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
		}
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		KillTimer(hWnd, 3);
		KillTimer(hWnd, 4);
		KillTimer(hWnd, 5);
		KillTimer(hWnd, 6);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}



void CALLBACK DoubleBuffering(HWND hWnd, UINT uMsg, UINT ibEvent, DWORD dwTime)
{
	

	
		HDC         hdc = GetDC(hWnd);
		HDC         hMemDC;
		HDC			CDC;
		HDC			CanDC;

		static HBITMAP backBitmap = NULL;
		HBITMAP      hBitmap = NULL, OldBitmap = NULL;

		static RECT rt = { 0, 0, 1920, 1080 };

		int CandyDraw = 0;
		int stageManager = 0;

		bool MapStage[9][22];
		
		
		hMemDC = CreateCompatibleDC(hdc);
		CDC = CreateCompatibleDC(hdc);
		CanDC = CreateCompatibleDC(hdc);

		HPEN MyPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
		HPEN OldPen = (HPEN)SelectObject(CanDC, MyPen);
		HBRUSH MyBrush = CreateSolidBrush(RGB(255, 0, 255));
		HBRUSH OldBrush = (HBRUSH)SelectObject(CanDC, MyBrush);

		backBitmap = CreateCompatibleBitmap(hdc, 1920, 1080);
		OldBitmap = (HBITMAP)SelectObject(hMemDC, backBitmap);
		FillRect(hMemDC, &rt, (HBRUSH)GetStockObject(BLACK_BRUSH));

		Sound4 = mciSendCommand(4, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);

		if (Main == 1)
		{
			hBitmap = (HBITMAP)SelectObject(CDC, MainB[3]);
			BitBlt(hMemDC, 0, 0, 1920, 1080, CDC, 0, 0, SRCCOPY);
			SelectObject(CDC, hBitmap);

			hBitmap = (HBITMAP)SelectObject(CDC, Arrow[0]);
			BitBlt(hMemDC, ArrowR.left, ArrowR.top, ArrowR.right, ArrowR.bottom, CDC, 0, 0, SRCCOPY);
			SelectObject(CDC, hBitmap);
		}
		if (IntroM >= 0 && IntroM <= 7)       
		{
			hBitmap = (HBITMAP)SelectObject(CDC, Intro[IntroM]);
			BitBlt(hMemDC, 0, 0, 1920, 1080, CDC, 0, 0, SRCCOPY);
			SelectObject(CDC, hBitmap);
		}
		if (InGame == 1)
		{


			
					if (stage == 0 && stageManager == 0)
					{
						for (int a = 0; a < 9; a++)
						{
							for (int b = 0; b < 22; b++)
								MapStage[a][b] = stage_1[a][b];
						}
						stageManager++;
					}
					else if (stage == 1 && stageManager == 1)
					{
						for (int a = 0; a < 9; a++)
						{
							for (int b = 0; b < 22; b++)
								MapStage[a][b] = stage_2[a][b];
						}
						stageManager++;
					}
					else if (stage == 2 && stageManager == 2)
					{
						for (int a = 0; a < 9; a++)
						{
							for (int b = 0; b < 22; b++)
								MapStage[a][b] = stage_3[a][b];
						}
						stageManager++;
					}
					else if (stage == 3 && stageManager == 3)
					{
						for (int a = 0; a < 9; a++)
						{
							for (int b = 0; b < 22; b++)
								MapStage[a][b] = stage_3[a][b];
						}
						stageManager++;
					}
					else if (stage == 4 && stageManager == 4)
					{
						for (int a = 0; a < 9; a++)
						{
							for (int b = 0; b < 22; b++)
								MapStage[a][b] = stage_5[a][b];
						}
					}
			
			for (int a = 0; a < 9; a++)
			{
				for (int b = 0; b < 22; b++)
				{
					for (int c = 0; c < 5;c++)
					{ 
						WALL[a][b] = { b * 80, a * 80, b * 80+80 , a * 80 +80};
						CandyArea[c][a][b] = { b * 80 + 25, a * 80 + 25, b * 80 + 55, a * 80 + 55 };
					}
				}
			}

			INConflictHandling(1, 1, 23, 10);



			printf("%d\n", CandyNum);

			if (stage == 0)
			{
				if (CandyManager == 0)
				{
					for (int a = 0; a < 9; a++)
					{
						for (int b = 0; b < 22; b++)
						{
							CandyCheck[a][b] = 1;
							MapStage[a][b] = stage_1[a][b];
							WallTrue[a][b] = stage_1[a][b];
							if (MapStage[a][b] == 0)
								CandyNum--;
						}
					}
					CandyManager++;
				}
				if (CandyNum <= 0)
				{
					
					stage++;
					InvalidateRect(hWnd, NULL, 0);

				}
			}

			else if (stage == 1) //&& CandyManager == 1)
			{
				if (CandyManager == 1)
				{
					for (int a = 0; a < 9; a++)
					{
						for (int b = 0; b < 22; b++)
						{
							CandyCheck[a][b] = 1;

							MapStage[a][b] = stage_2[a][b];
							WallTrue[a][b] = stage_2[a][b];
							if (MapStage[a][b] == 0)
								CandyNum--;
						}
					}
					CandyManager++;
					CandyNum = 198;
					player = { 80, 280, 160, 360 };
					playerC = { 15, 0, 65, 80 };
					playerR = { 95, 300, 145, 360 };
					direction = 4;
					Ghost1 = { 1760, 920, 1840, 1000 };
					Ghost2 = { 1760, 280, 1840, 360 };
					Ghost3 = { 880, 280, 960, 360 };
					Ghost4 = { 960, 920, 1040, 1000 };

				}
				if (CandyNum <= 0)
				{
					
					stage++;
					InvalidateRect(hWnd, NULL, 0);

				}
			}

			else if (stage == 2)// && CandyManager == 2)
			{
				if (CandyManager == 2)
				{
					for (int a = 0; a < 9; a++)
					{
						for (int b = 0; b < 22; b++)
						{
							CandyCheck[a][b] = 1;

							MapStage[a][b] = stage_3[a][b];
							WallTrue[a][b] = stage_3[a][b];
							if (MapStage[a][b] == 0)
								CandyNum--;
						}
					}
					CandyManager++;
					CandyNum = 198;
					player = { 80, 280, 160, 360 };
					playerC = { 15, 0, 65, 80 };
					playerR = { 95, 300, 145, 360 };
					direction = 4;
					Ghost1 = { 1760, 920, 1840, 1000 };
					Ghost2 = { 1760, 280, 1840, 360 };
					Ghost3 = { 880, 280, 960, 360 };
					Ghost4 = { 960, 920, 1040, 1000 };

				}

				if (CandyNum <= 0)
				{
					stage++;
					InvalidateRect(hWnd, NULL, 0);

				}
			}

			else if (stage == 3)// && CandyManager == 3)
			{
				if (CandyManager == 3)
				{
					for (int a = 0; a < 9; a++)
					{
						for (int b = 0; b < 22; b++)
						{
							CandyCheck[a][b] = 1;

							MapStage[a][b] = stage_4[a][b];
							WallTrue[a][b] = stage_4[a][b];
							if (MapStage[a][b] == 0)
								CandyNum--;
						}
					}
					CandyManager++;
					CandyNum = 198;
					player = { 80, 280, 160, 360 };
					playerC = { 15, 0, 65, 80 };
					playerR = { 95, 300, 145, 360 };
					direction = 4;
					Ghost1 = { 1760, 920, 1840, 1000 };
					Ghost2 = { 1760, 280, 1840, 360 };
					Ghost3 = { 880, 280, 960, 360 };
					Ghost4 = { 960, 920, 1040, 1000 };

				}
				if (CandyNum <= 0)
				{
					stage++;
					InvalidateRect(hWnd, NULL, 0);

				}
			}
			else if (stage == 4)// && CandyManager == 4)
			{
				if (CandyManager == 4)
				{
					for (int a = 0; a < 9; a++)
					{
						for (int b = 0; b < 22; b++)
						{
							CandyCheck[a][b] = 1;

							MapStage[a][b] = stage_5[a][b];
							WallTrue[a][b] = stage_5[a][b];
							if (MapStage[a][b] == 0)
								CandyNum--;
						}
					}
					CandyManager++;
					CandyNum = 198;
					player = { 80, 280, 160, 360 };
					playerC = { 15, 0, 65, 80 };
					playerR = { 95, 300, 145, 360 };
					direction = 4;
					Ghost1 = { 1760, 920, 1840, 1000 };
					Ghost2 = { 1760, 280, 1840, 360 };
					Ghost3 = { 880, 280, 960, 360 };
					Ghost4 = { 960, 920, 1040, 1000 };
					

				}
				if (CandyNum <= 0)
				{
					InGame = 0;
					GameClear = 1;
				}

			}
			
		
			hBitmap = (HBITMAP)SelectObject(CanDC, CandyBit[candy]);
			TransparentBlt(hMemDC, 80, 280, 1760, 720, CanDC, 0, 0, 1760, 720, RGB(255, 0, 255));
			SelectObject(CanDC, hBitmap);

			for (int a = 0; a < 9; a++)
			{
				for (int b = 0; b < 22; b++)
				{
					if (WallTrue[a][b] == 0)
						OUTConflictHandling(WALL[a][b]);

				}
				
			}
			//// UI

			hBitmap = (HBITMAP)SelectObject(CDC, UI[0]);
			BitBlt(hMemDC, 230, 12, 1920, 200, CDC, 0, 0, SRCCOPY);
			SelectObject(CDC, hBitmap);

			hBitmap = (HBITMAP)SelectObject(CDC, UI[4]);
			BitBlt(hMemDC, 230, 12-(stage+1)*36, 1920, 200, CDC, 0, 0, SRCCOPY);
			SelectObject(CDC, hBitmap);

			hBitmap = (HBITMAP)SelectObject(CDC, UI[3]);
			TransparentBlt(hMemDC, 0, 0, 1920, 200, CDC, 0, 0, 1920, 200, RGB(255, 0, 255));
			SelectObject(CDC, hBitmap);
			if (stage <= 4)
			{
				hBitmap = (HBITMAP)SelectObject(CDC, UI[1]);
				BitBlt(hMemDC, 440, 147 - stage * 36, 1920, 200, CDC, 0, 0, SRCCOPY);
				SelectObject(CDC, hBitmap);
			}

			if (Life >= 1)
			{
				hBitmap = (HBITMAP)SelectObject(CDC, UI[2]);
				BitBlt(hMemDC, 850, 50, 1920, 200, CDC, 0, 0, SRCCOPY);
				SelectObject(CDC, hBitmap);
				if (Life >= 2)
				{
					hBitmap = (HBITMAP)SelectObject(CDC, UI[2]);
					BitBlt(hMemDC, 980, 50, 1920, 200, CDC, 0, 0, SRCCOPY);
					SelectObject(CDC, hBitmap);
				}
			}

			N1 = CandyNum % 10;
			N10 = (CandyNum / 10) % 10;
			if (CandyNum >= 1)
			{
				hBitmap = (HBITMAP)SelectObject(CDC, N[N1]);
				BitBlt(hMemDC, 1640, 73, 1920, 200, CDC, 0, 0, SRCCOPY);
				SelectObject(CDC, hBitmap);
			}
				if (CandyNum >= 10)
				{
					hBitmap = (HBITMAP)SelectObject(CDC, N[N10]);
					BitBlt(hMemDC, 1572, 73, 1920, 200, CDC, 0, 0, SRCCOPY);
					SelectObject(CDC, hBitmap);
				}
				if (CandyNum >= 100)
				{
					hBitmap = (HBITMAP)SelectObject(CDC, N[1]);
					BitBlt(hMemDC, 1504, 73, 1920, 200, CDC, 0, 0, SRCCOPY);
					SelectObject(CDC, hBitmap);
				}
	


			//// Drawing Here ////

			hBitmap = (HBITMAP)SelectObject(CDC, map[stage]);
			TransparentBlt(hMemDC, 0, 200, 1920, 880, CDC, 0, 0, 1920, 880, RGB(255, 0, 255));
			SelectObject(CDC, hBitmap);


			//// Candy ////
			hBitmap = (HBITMAP)SelectObject(CanDC, CandyBit[candy]);

			for (int a = 0; a < 9; a++)
			{
				for (int b = 0; b < 22; b++)
				{
					if (IntersectRect(&Temp_, &playerC, &CandyArea[stage][a][b]) && MapStage[a][b] == 1 && CandyCheck[a][b] == 1)
					{
						MapStage[a][b] = 0;
						RectAngleManager(CanDC, CandyArea[stage][a][b]);
						CandyNum--;
						CandyCheck[a][b] = 0;
						Sound4 = mciSendCommand(4, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
					}
					if (MapStage[a][b] == 0)
					{
						RectAngleManager(CanDC, CandyArea[stage][a][b]);
					}
				}
			}
			printf("%d\n", MapStage[2][2]);
			printf("%d\n", MapStage[1][1]);

			SelectObject(CanDC, OldBrush);
			SelectObject(CanDC, OldPen);


			TransparentBlt(hMemDC, 80, 280, 1760, 720, CanDC, 0, 0, 1760, 720, RGB(255, 0, 255));
			SelectObject(CanDC, hBitmap);






			// Ghost

			hBitmap = (HBITMAP)SelectObject(CDC, GHOST[Mouse][GhostMove1]);
			TransparentBlt(hMemDC, Ghost1.left, Ghost1.top, 80, 80, CDC, 0, 0, 80, 80, RGB(255, 0, 255));
			SelectObject(CDC, hBitmap);

			hBitmap = (HBITMAP)SelectObject(CDC, GHOST[Mouse][GhostMove2]);
			TransparentBlt(hMemDC, Ghost2.left, Ghost2.top, 80, 80, CDC, 0, 0, 80, 80, RGB(255, 0, 255));
			SelectObject(CDC, hBitmap);

			hBitmap = (HBITMAP)SelectObject(CDC, GHOST[Mouse][GhostMove3]);
			TransparentBlt(hMemDC, Ghost3.left, Ghost3.top, 80, 80, CDC, 0, 0, 80, 80, RGB(255, 0, 255));
			SelectObject(CDC, hBitmap);

			hBitmap = (HBITMAP)SelectObject(CDC, GHOST[Mouse][GhostMove4]);
			TransparentBlt(hMemDC, Ghost4.left, Ghost4.top, 80, 80, CDC, 0, 0, 80, 80, RGB(255, 0, 255));
			SelectObject(CDC, hBitmap);

			// player //
			hBitmap = (HBITMAP)SelectObject(CDC, PM[Mouse][direction]);
			TransparentBlt(hMemDC, player.left, player.top, 80, 80, CDC, 0, 0, 80, 80, RGB(255, 0, 255));
			SelectObject(CDC, hBitmap);

		}

		if (GameOver == 1)
		{
			Sound3 = mciSendCommand(3, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
			Sound4 = mciSendCommand(4, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);

			hBitmap = (HBITMAP)SelectObject(CDC, GameOverB[0]);
			BitBlt(hMemDC, 0, 0, 1920, 1080, CDC, 0, 0,SRCCOPY);
			SelectObject(CDC, hBitmap);

			hBitmap = (HBITMAP)SelectObject(CDC, GameOverB[1]);
			TransparentBlt(hMemDC, 401, 250, 1118, 105, CDC, 0, 0, 1118, 105, RGB(252, 0, 255));
			SelectObject(CDC, hBitmap);

			if (Pressenter == 1)
			{
				hBitmap = (HBITMAP)SelectObject(CDC, GameOverB[2]);
				TransparentBlt(hMemDC, 690, 800, 541, 44, CDC, 0, 0, 541, 44, RGB(252, 0, 255));
				SelectObject(CDC, hBitmap);
			}

		}
		if (GameClear == 1)
		{

			Sound3 = mciSendCommand(3, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
			hBitmap = (HBITMAP)SelectObject(CDC, map[5]);
			BitBlt(hMemDC, 0, 0, 1920, 1080, CDC, 0, 0, SRCCOPY);
			SelectObject(CDC, hBitmap);
			
			hBitmap = (HBITMAP)SelectObject(CDC, MINT[Mouse][Mdirection]);
			TransparentBlt(hMemDC, Princess.left, Princess.top, 80, 80, CDC, 0, 0, 80, 80, RGB(255, 0, 255));
			SelectObject(CDC, hBitmap);

			hBitmap = (HBITMAP)SelectObject(CDC, PM[Mouse][direction]);
			TransparentBlt(hMemDC, GameEndPX, GameEndPY, 80, 80, CDC, 0, 0, 80, 80, RGB(255, 0, 255));
			SelectObject(CDC, hBitmap);

			if (Mdirection == 1 && EndRect.top <= GameEndPY)
			{
				GameClear = 0;
				Ending = 1;
			}
			
		}
		if (Ending == 1)
		{
			Sound5 = mciSendCommand(5, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
			hBitmap = (HBITMAP)SelectObject(CDC, GameClearB);
			TransparentBlt(hMemDC, 0, 0, 1920, 1080, CDC, 0, 0, 1920, 1080, RGB(255, 0, 255));
			SelectObject(CDC, hBitmap);
		}
		//// Drawing End ////


		BitBlt(hdc, 0, 0, 1920, 1080, hMemDC, 0, 0, SRCCOPY);

		DeleteObject(SelectObject(hMemDC, OldBitmap));
		DeleteObject(SelectObject(CDC, hBitmap));
		DeleteObject(SelectObject(CanDC, hBitmap));
		DeleteDC(hMemDC);
		DeleteDC(CDC);
		DeleteDC(CanDC);
		DeleteObject(MyBrush);
		DeleteObject(MyPen);

		ReleaseDC(hWnd, hdc);
	
}

void INConflictHandling(int left, int top, int right, int bottom)
{
	left *= 80;
	top = top * 80 + 200;
	right *= 80;
	bottom = bottom * 80 + 200;

	if (playerR.left < left)
	{
		player.left += speed;
		player.right += speed;
		playerR.left += speed;
		playerR.right += speed;
		playerC.left += speed;
		playerC.right += speed;
		MouseManager = 3;

	}
	else if (playerR.top < top)
	{
		player.top += speed;
		player.bottom += speed;
		playerR.top += speed;
		playerR.bottom += speed;
		playerC.top += speed;
		playerC.bottom += speed;
		MouseManager = 3;

	}
	else if (playerR.right > right)
	{
		player.left -= speed;
		player.right -= speed;
		playerR.left -= speed;
		playerR.right -= speed;
		playerC.left -= speed;
		playerC.right -= speed;
		MouseManager = 3;

	}
	else if (playerR.bottom > bottom)
	{
		player.top -= speed;
		player.bottom -= speed;
		playerR.top -= speed;
		playerR.bottom -= speed;
		playerC.top -= speed;
		playerC.bottom -= speed;
		MouseManager = 3;

	}

	if (Ghost1.left < left)
	{
		Ghost1.left += Gspeed;
		Ghost1.right += Gspeed;
		
		GhostMove1 = rand() % 4;

	}
	else if (Ghost1.top < top)
	{
		Ghost1.top += Gspeed;
		Ghost1.bottom += Gspeed;
		
		GhostMove1 = rand() % 4;

	}
	else if (Ghost1.right > right)
	{
		Ghost1.left -= Gspeed;
		Ghost1.right -= Gspeed;
		
		GhostMove1 = rand() % 4;

	}
	else if (Ghost1.bottom > bottom)
	{
		Ghost1.top -= Gspeed;
		Ghost1.bottom -= Gspeed;
		
		GhostMove1 = rand() % 4;

	}
	if (Ghost2.left < left)
	{
		Ghost2.left += Gspeed;
		Ghost2.right += Gspeed;
		
		GhostMove2 = rand() % 4;

	}
	else if (Ghost2.top < top)
	{
		Ghost2.top += Gspeed;
		Ghost2.bottom += Gspeed;
		
		GhostMove2 = rand() % 4;

	}
	else if (Ghost2.right > right)
	{
		Ghost2.left -= Gspeed;
		Ghost2.right -= Gspeed;
		GhostMove2 = rand() % 4;

	}
	else if (Ghost2.bottom > bottom)
	{
		Ghost2.top -= Gspeed;
		Ghost2.bottom -= Gspeed;
		GhostMove2 = rand() % 4;

	}
	if (Ghost3.left < left)
	{
		Ghost3.left += Gspeed;
		Ghost3.right += Gspeed;
		GhostMove3 = rand() % 4;

	}
	else if (Ghost3.top < top)
	{
		Ghost3.top += Gspeed;
		Ghost3.bottom += Gspeed;
		GhostMove3 = rand() % 4;

	}
	else if (Ghost3.right > right)
	{
		Ghost3.left -= Gspeed;
		Ghost3.right -= Gspeed;
		GhostMove3 = rand() % 4;

	}
	else if (Ghost3.bottom > bottom)
	{
		Ghost3.top -= Gspeed;
		Ghost3.bottom -= Gspeed;
		GhostMove3 = rand() % 4;

	}
	if (Ghost4.left < left)
	{
		Ghost4.left += Gspeed;
		Ghost4.right += Gspeed;
		GhostMove4 = rand() % 4;

	}
	else if (Ghost4.top < top)
	{
		Ghost4.top += Gspeed;
		Ghost4.bottom += Gspeed;
		GhostMove4 = rand() % 4;

	}
	else if (Ghost4.right > right)
	{
		Ghost4.left -= Gspeed;
		Ghost4.right -= Gspeed;
		GhostMove4 = rand() % 4;

	}
	else if (Ghost4.bottom > bottom)
	{
		Ghost4.top -= Gspeed;
		Ghost4.bottom -= Gspeed;
		GhostMove4 = rand() % 4;

	}
}

void OUTConflictHandling(RECT rc)
{

	RECT Dest;
	rc.left += 80;
	rc.top += 280;
	rc.right += 80;
	rc.bottom += 280;

	if (IntersectRect(&Dest, &Ghost1, &rc))
	{
		switch (GhostMove1)
		{
		case 0:
			Ghost1.left += Gspeed;
			Ghost1.right += Gspeed;
			GhostMove1 = rand() % 4;
			return;
		case 1:
			Ghost1.bottom += Gspeed;
			Ghost1.top += Gspeed;
			GhostMove1 = rand() % 4;
			return;
		case 2:
			Ghost1.left -= Gspeed;
			Ghost1.right -= Gspeed;
			GhostMove1 = rand() % 4;
			return;
		case 3:
			Ghost1.bottom -= Gspeed;
			Ghost1.top -= Gspeed;
			GhostMove1 = rand() % 4;
			return;
		default:
			break;
		}
	}
	if (IntersectRect(&Dest, &Ghost2, &rc))
	{
		switch (GhostMove2)
		{
		case 0:
			Ghost2.left += Gspeed;
			Ghost2.right += Gspeed;
			GhostMove2 = rand() % 4;
			return;
		case 1:
			Ghost2.bottom += Gspeed;
			Ghost2.top += Gspeed;
			GhostMove2 = rand() % 4;
			return;
		case 2:
			Ghost2.left -= Gspeed;
			Ghost2.right -= Gspeed;
			GhostMove2 = rand() % 4;
			return;
		case 3:
			Ghost2.bottom -= Gspeed;
			Ghost2.top -= Gspeed;
			GhostMove2 = rand() % 4;
			return;
		default:
			break;
		}
	}
	if (IntersectRect(&Dest, &Ghost3, &rc))
	{
		switch (GhostMove3)
		{
		case 0:
			Ghost3.left += Gspeed;
			Ghost3.right += Gspeed;
			GhostMove3 = rand() % 4;
			return;
		case 1:
			Ghost3.bottom += Gspeed;
			Ghost3.top += Gspeed;
			GhostMove3 = rand() % 4;
			return;
		case 2:
			Ghost3.left -= Gspeed;
			Ghost3.right -= Gspeed;
			GhostMove3 = rand() % 4;
			return;
		case 3:
			Ghost3.bottom -= Gspeed;
			Ghost3.top -= Gspeed;
			GhostMove3 = rand() % 4;
			return;
		default:
			break;
		}
	}
	if (IntersectRect(&Dest, &Ghost4, &rc))
	{
		switch (GhostMove4)
		{
		case 0:
			Ghost4.left += Gspeed;
			Ghost4.right += Gspeed;
			GhostMove4 = rand() % 4;
			return;
		case 1:
			Ghost4.bottom += Gspeed;
			Ghost4.top += Gspeed;
			GhostMove4 = rand() % 4;
			return;
		case 2:
			Ghost4.left -= Gspeed;
			Ghost4.right -= Gspeed;
			GhostMove4 = rand() % 4;
			return;
		case 3:
			Ghost4.bottom -= Gspeed;
			Ghost4.top -= Gspeed;
			GhostMove4 = rand() % 4;
			return;
		default:
			break;
		}
	}

	if (IntersectRect(&Dest, &playerR, &rc))
	{

		switch (direction)
		{
		case 0:
			player.left += speed;
			player.right += speed;
			playerR.left += speed;
			playerR.right += speed;
			playerC.left += speed;
			playerC.right += speed;
			MouseManager = 3;
			return;
		case 1:
			player.top += speed;
			player.bottom += speed;
			playerR.top += speed;
			playerR.bottom += speed;
			playerC.top += speed;
			playerC.bottom += speed;
			MouseManager = 3;
			return;
		case 2:
			player.left -= speed;
			player.right -= speed;
			playerR.left -= speed;
			playerR.right -= speed;
			playerC.left -= speed;
			playerC.right -= speed;
			MouseManager = 3;
			return;
		case 3:
			player.top -= speed;
			player.bottom -= speed;
			playerR.top -= speed;
			playerR.bottom -= speed;
			playerC.top -= speed;
			playerC.bottom -= speed;
			MouseManager = 3;
			return;
		default:
			break;
		}
	}
}

void GhostAI()
{
	if (InGame == 1)
	{
		switch (GhostMove1)
		{
		case 0:
			Ghost1.left -= Gspeed;
			Ghost1.right -= Gspeed;


			break;
		case 1:
			Ghost1.top -= Gspeed;
			Ghost1.bottom -= Gspeed;

			break;
		case 2:
			Ghost1.left += Gspeed;
			Ghost1.right += Gspeed;

			break;
		case 3:
			Ghost1.top += Gspeed;
			Ghost1.bottom += Gspeed;

			break;
		}
		switch (GhostMove2)
		{
		case 0:
			Ghost2.left -= Gspeed;
			Ghost2.right -= Gspeed;


			break;
		case 1:
			Ghost2.top -= Gspeed;
			Ghost2.bottom -= Gspeed;

			break;
		case 2:
			Ghost2.left += Gspeed;
			Ghost2.right += Gspeed;

			break;
		case 3:
			Ghost2.top += Gspeed;
			Ghost2.bottom += Gspeed;

			break;
		}
		switch (GhostMove3)
		{
		case 0:
			Ghost3.left -= Gspeed;
			Ghost3.right -= Gspeed;


			break;
		case 1:
			Ghost3.top -= Gspeed;
			Ghost3.bottom -= Gspeed;

			break;
		case 2:
			Ghost3.left += Gspeed;
			Ghost3.right += Gspeed;

			break;
		case 3:
			Ghost3.top += Gspeed;
			Ghost3.bottom += Gspeed;

			break;
		}
		switch (GhostMove4)
		{
		case 0:
			Ghost4.left -= Gspeed;
			Ghost4.right -= Gspeed;


			break;
		case 1:
			Ghost4.top -= Gspeed;
			Ghost4.bottom -= Gspeed;

			break;
		case 2:
			Ghost4.left += Gspeed;
			Ghost4.right += Gspeed;

			break;
		case 3:
			Ghost4.top += Gspeed;
			Ghost4.bottom += Gspeed;

			break;
		}
	}
}


void RectAngleManager(HDC hDC, RECT rect)
{
	Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);
}

void GhostConflictHandling(RECT Ghost1, RECT Ghost2, RECT Ghost3, RECT Ghost4)
{
	RECT Dest;
	if (IntersectRect(&Dest, &Ghost1R, &playerR) || IntersectRect(&Dest, &Ghost2R, &playerR) || IntersectRect(&Dest, &Ghost3R, &playerR) || IntersectRect(&Dest, &Ghost4R, &playerR))
	{
		direction = 5;
	}
}

DWORD LoadWav(HWND hWnd, LPCTSTR lpszWave)
{
	DWORD Result;

	mciOpen.lpstrDeviceType = L"MPEGVideo";
	//WaveAudio - WAV // MPEGVideo -mp3 

	mciOpen.lpstrElementName = lpszWave;

	Result = mciSendCommand(wDeviceID, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&mciOpen);

	if (Result)
		return Result;

	wDeviceID = mciOpen.wDeviceID;

	mciPlay.dwCallback = (DWORD)hWnd;

	if (Result)
		return Result;

	return 0;
}