#include"Wall.h"

Surface::Surface()
{
	g_hMutex = CreateMutex(NULL, FALSE, NULL);
	for (int i = 0; i < 41; i++)
	{
		for (int k = 0; k < 41; k++)
		{
			if (i == 0 || i == 40 || k == 0 || k == 40)
				SurData[i][k] = '*';
			else
				SurData[i][k] = ' ';
		}
	}
}

void Surface::IniWall(Cursor cur)
{
	
	for (int i = 0; i < 41; i++)
	{
		cur.SetCursor(55, 3 + i);
		for (int k = 0; k < 41; k++)
		{
			cout << SurData[i][k]<<' ';
			if (i == 17 && k == 40)
				cout << " Design by D_Grey";
			if (i == 18 && k == 40)
				cout << " Press to start the game and E to end the game";
			if (i == 19 && k == 40)
				cout << " W->Up";
			if (i == 20 && k == 40)
				cout << " S->Down";
			if (i == 21 && k == 40)
				cout << " A->Left";
			if (i == 22 && k == 40)
				cout << " D->Right";
		}
	}
	return;
}

void Surface::UpdateSurface(char s)
{
	cout << s;
	return;
}

Cursor::Cursor()
{
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hout, &csbi);
	cci.bVisible = 0;
	cci.dwSize = 1;
	SetConsoleCursorInfo(hout, &cci);

}

void Cursor::SetCursor(int x,int y)
{
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(hout, coord);
}
