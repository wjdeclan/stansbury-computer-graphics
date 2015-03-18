#pragma once
#include "../../Angel/Actors/Actor.h"

class Monster : public Actor
{
public:
	Monster(Vector2 v2, Vector2 vel);

	int health;
	Vector2 pos;
	Vector2 dPos;

	void Update(float dx);

};