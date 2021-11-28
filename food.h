#pragma once
#include"Wall.h"
#include<time.h>
#include"snake.h"
class food
{
public:
	food();
	void production(Surface &sf,snake s);
};