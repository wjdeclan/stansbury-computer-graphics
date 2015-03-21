#include "stdafx.h"
#include "Monster.h"

Monster::Monster(Vector2 vs, Actor *point)
{
	player = point;
	health = 100;
	pos = vs;

	//this->SetColor(Color(1.0f,1.0f,1.0f,1.0f));
	this->SetSprite("./Resources/Images/monster.png");
}

void Monster::Update(float dx)
{
	Vector2 v2 = player->GetPosition();
	v2 -= this->GetPosition();
	v2.Normalize();
	v2 *= 3;
	dPos = v2;
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