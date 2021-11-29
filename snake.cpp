#pragma once
#include"snake.h"
#include"food.h"
snake::snake()
{
	head = (sBody*)malloc(sizeof(sBody));
	rear = (sBody*)malloc(sizeof(sBody));
	sBody* s1 = (sBody*)malloc(sizeof(sBody));
	sBody* s2 = (sBody*)malloc(sizeof(sBody));

	if (head == NULL || rear == NULL || s1 == NULL || s2 == NULL)
	{
		cout << "游戏初始化失败！" << endl;
		return;
	}

	head->col = col;
	head->line = line;
	head->front = NULL;
	
	s1->col = col-2;
	s1->line = line;
	s1->front = head;

	s2->col = s1->col-2;
	s2->line = line;
	s2->front = s1;
	
	rear->col = s2->col - 2;
	rear->line = line;
	rear->front = s2;

}

void snake::move(Surface& sf)
{
	Cursor cur;
	while (isAlive)
	{

		int L_dif = rear->line - rear->front->line;
		int C_dif = rear->col - rear->front->col;

		for (sBody* i = rear; i->front != NULL; i = i->front)
		{
			i->line = i->front->line;
			i->col = i->front->col;
		}

		switch (direction)
		{
		case 'a':
		{
			head->col -= 2;
			break;
		}
		case 'd':
		{
			head->col += 2;
			break;
		}
		case 'w':
		{
			head->line -= 1;
			break;
		}
		case 's':
		{
			head->line += 1;
			break;
		}
		default:
			break;
		}

		int c_col = (head->col-55) / 2;
		char s1 = sf.getsd(head->line-3, c_col);
		if (s1 == '*' || s1 == '=')
		{
			isAlive = false;
			return;
		}
		if (s1 == '$')
			grow(sf, L_dif, C_dif);

		WaitForSingleObject(sf.g_hMutex, INFINITE);
		cur.SetCursor(head->col, head->line);
		sf.setsd(head->line-3, c_col, '@');
		sf.UpdateSurface('@');
		ReleaseMutex(sf.g_hMutex);

		for (sBody* i = rear; i->front != NULL; i = i->front)
		{
			int c = (i->col-55) / 2;
			if (i == rear)
			{
				WaitForSingleObject(sf.g_hMutex, INFINITE);
				cur.SetCursor(i->col, i->line);
				sf.setsd(i->line-3, c, ' ');
				sf.UpdateSurface(' ');
				ReleaseMutex(sf.g_hMutex);
			}
			else
			{
				WaitForSingleObject(sf.g_hMutex, INFINITE);
				cur.SetCursor(i->col, i->line);
				sf.setsd(i->line-3, c, '=');
				sf.UpdateSurface('=');
				ReleaseMutex(sf.g_hMutex);
			}
		}
		Sleep(speed);
	}
}

void snake::grow(Surface &sf,int L_dif,int C_dif)
{
	sBody* Nbody = (sBody*)malloc(sizeof(sBody));
	if (Nbody == NULL)
	{
		cout << "游戏运行错误！" << endl;
		isAlive = false;
		return;
	}
	sf.socre++;

	Nbody->line = rear->line;
	Nbody->col = rear->col;
	Nbody->front = rear->front;

	if (L_dif == 0)
	{
		if (C_dif == 2)
			rear->col += 2;
		else
			rear->col -= 2;;
	}
	else
	{
		if (L_dif == 1)
			rear->line++;
		else
			rear->line--;
	}
	rear->front = Nbody;
	
	int real_col = (Nbody->col-55) / 2;
	Cursor cur;

	WaitForSingleObject(sf.g_hMutex, INFINITE);
	cur.SetCursor(Nbody->col, Nbody->line);
	sf.setsd(Nbody->line-3, real_col, '=');
	cout << "=";
	ReleaseMutex(sf.g_hMutex);

	sf.havefood = false;
	speed -= 40;
	if (speed <= 50)
	{
		if (sf.socre >= 35)
		{
			speed -= 3;
			if (speed <= 0)speed = 0;
		}
		else
		{
			speed = 50;
		}
	}

	return;
}


void snake::changedir(char key)
{
	switch (key)
	{
	case 'a':
	{
		if (direction == 'd')break;
		direction = 'a';
		break;
	}
	case 'd':
	{
		if (direction == 'a')break;
		direction = 'd';
		break;
	}
	case 's':
	{
		if (direction == 'w')break;
		direction = 's';
		break;
	}
	case 'w':
	{
		if (direction == 's')break;
		direction = 'w';
		break;
	}
	case 'e':
	{
		isAlive = false;
		break;
	}
	default:
		break;
	}
}

void food::production(Surface &sf,snake s)
{
	srand((unsigned int)time(NULL));
	int line = rand();
	int col = rand();
	Cursor cur;
	int a = line % 41;
	int b = col % 41;
	int real_b = b * 2;
	char s1 = sf.getsd(a, b);
	char s2 = sf.getsd(s.rear->line-3, s.rear->col-55);
	if (s1 != '=' && s1 != '@' && s1 != '*' && (a != s.rear->line-3 || b != s.rear->col-55))
	{ 
		WaitForSingleObject(sf.g_hMutex, INFINITE);
		cur.SetCursor(real_b+55, a+3);
		sf.setsd(a, b, '$');
		cout << '$';
		ReleaseMutex(sf.g_hMutex);

		sf.havefood = true;

	}
	return;
}
