#pragma once
#include "../../Angel/Actors/Actor.h"

class Monster : public Actor
{
public:
	Monster(Vector2 v2, Actor *point);

	Actor *player;

	int health;
	Vector2 pos;
	Vector2 dPos;

	void Update(float dx);
	void Damage(int dmg);
	int getHealth();

};