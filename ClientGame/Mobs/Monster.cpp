#include "stdafx.h"
#include "Monster.h"

Monster::Monster(Vector2 vs, Vector2 vp)
{
	health = 100;
	pos = vs;
	dPos = vp;

	//this->SetColor(Color(1.0f,1.0f,1.0f,1.0f));
	this->SetSprite("./Resources/Images/monster.png");
}

void Monster::Update(float dx)
{
	pos += dPos * dx;
	this->SetPosition(pos);
}

void Monster::Damage(int dmg) {
	health -= dmg;
}

int Monster::getHealth()
{
	return health;
}