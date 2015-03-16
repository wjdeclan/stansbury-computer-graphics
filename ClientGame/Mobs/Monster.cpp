#include "stdafx.h"
#include "Monster.h"

Monster::Monster(float x1, float y1)
{
	health = 100;
	x = x1;
	y = y1;
	
}

void Monster::Update(float dx)
{
	x += 0.1 * dx;
}

Vector2 Monster::ReturnVector() {
	return Vector2(x, y);
}
