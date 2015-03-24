#pragma once
#include "../../Angel/Actors/Actor.h"

class Monster : public Actor
{
public:
	Monster(Vector2 v2, Actor *point, int mHealth, int mSpeed);

	Actor *player;

	int health;
	Vector2 pos;
	Vector2 dPos;

	void Update(float dx);
	void Damage(int dmg);
	int getHealth();
	Vector2 getPos();
	void TrueUpdate(float dx);
	int mSpeed = 3;
};