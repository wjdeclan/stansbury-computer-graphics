#include "stdafx.h"
#include "Monster.h"

Monster::Monster(Vector2 vs, Actor *point, int mHealth, int mS)
{
	player = point;
	health = mHealth;
	pos = vs;
	mSpeed = mS;

	//this->SetColor(Color(1.0f,1.0f,1.0f,1.0f));
	this->SetSprite("./Resources/Images/monster.png");
}

void Monster::Update(float dx)
{
	
}

void Monster::TrueUpdate(float dx) {
	Vector2 v2 = player->GetPosition();
	v2 -= this->GetPosition();
	v2.Normalize();
	v2 *= mSpeed;
	dPos = v2;
	pos += dPos * dx;
}

void Monster::Damage(int dmg) {
	health -= dmg;
}

int Monster::getHealth()
{
	return health;
}

Vector2 Monster::getPos() {
	return pos;
}