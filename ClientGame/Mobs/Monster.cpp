#include "stdafx.h"
#include "Monster.h"

Monster::Monster(Vector2 vs, Vector2 vp)
{
	health = 100;
	pos = vs;
	dPos = vp;

	this->SetColor(Color(1.0f,1.0f,1.0f,1.0f));
	
}

void Monster::Update(float dx)
{
	pos += dPos * dx;
	this->SetPosition(pos);
}