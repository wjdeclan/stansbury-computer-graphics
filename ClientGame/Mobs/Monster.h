#pragma once
#include "../../Angel/Actors/Actor.h"

class Monster : public Actor
{
public:
	Monster(float x, float y);

	int health;
	float x, y;


	void Update(float dx);

	Vector2 ReturnVector();

};