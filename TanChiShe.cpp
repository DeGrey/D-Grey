#pragma once

#include"Wall.h"
#include"snake.h"
#include<conio.h>
#include"food.h"
Surface Wall;
snake s;
food f;

void startmove()
{
	s.move(Wall);
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
	Cursor cur;

	SetConsoleTitle(L"Greedy snake1.0");
	cur.coord.X = 255;
	cur.coord.Y = 80;
	SetConsoleScreenBufferSize(cur.hout, cur.coord);

	Wall.IniWall(cur);
	cur.SetCursor(0, 0);

	con = _getch();
	thread th1(startmove);
	thread th2(food_prod);

	do
	{
		con = _getch();
		s.changedir(con);
	} while (s.isAlive);

	th1.join();
	th2.join();

	cur.SetCursor(94, 45);
	cout << "Score£º" << Wall.socre << endl;
	cur.SetCursor(0, 47);


	return 0;
}