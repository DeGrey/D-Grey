#pragma once
#include"Wall.h"

class snake
{

public:
	int line = 20+3, col = 42+55;
	char direction = 'd';
	bool isAlive = true;
	int speed=260;
	sBody* head, * rear;

	snake();

	void changedir(char);
	void move(Surface&);
	void grow(Surface &sf,int,int);
};