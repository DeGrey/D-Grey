#pragma once

#include"Wall.h"
#include"snake.h"
#include<conio.h>
#include"food.h"
Surface Wall;
Cursor cur;
snake s;
food f;

void hideCursor()
{
	while (s.isAlive)
	{
		GetConsoleCursorInfo(cur.hout, &cur.cci);
		if (cur.cci.bVisible != 0)
		{
			cur.cci.bVisible = 0;
			SetConsoleCursorInfo(cur.hout, &cur.cci);
		}
	}
}

void startmove()
{
	s.move(Wall,cur);
	return;
}

void food_prod()
{
	while (s.isAlive)
	{
		while (!Wall.havefood)
		{
			f.production(Wall, s);
		}
	}
	return;
}

int main()
{
	char con; 

	SetConsoleTitle(L"Greedy snake1.0");
	cur.coord.X = 255;
	cur.coord.Y = 80;
	SetConsoleScreenBufferSize(cur.hout, cur.coord);

	Wall.IniWall(cur);
	cur.SetCursor(0, 0);

	thread th0(hideCursor);

	con = _getch();
	thread th1(startmove);
	thread th2(food_prod);


	do
	{
		con = _getch();
		
		s.changedir(Wall,con,cur);
	} while (s.isAlive);

	th0.join();
	th1.join();
	th2.join();

	cur.SetCursor(94, 45);
	cout << "Score:" << Wall.socre << endl;
	cur.SetCursor(0, 47);


	return 0;
}