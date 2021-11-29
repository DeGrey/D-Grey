#pragma once
#include<iostream>
#include<Windows.h>
#include<thread>

using namespace std;

struct sBody
{
	int line, col;
	sBody* front;
};

class Cursor
{
public:
	HANDLE hout;

	COORD coord;
	CONSOLE_CURSOR_INFO cci = { 0 };
	CONSOLE_SCREEN_BUFFER_INFO csbi = { 0 };
	Cursor();
	void SetCursor(int, int);
};

class Surface
{
private:
	char SurData[41][41];

public:
	int socre=0;
	bool havefood = false;
	HANDLE g_hMutex;

	Surface();
	void IniWall(Cursor cur);
	void UpdateSurface(char s);

	char getsd(int line, int col) { return SurData[line][col]; }
	void setsd(int line, int col, char value) { SurData[line][col] = value; }
};

