#pragma once
#include "../../Angel/Actors/Actor.h"

class Fireball : public Actor
{
public:
	Fireball(Vector2 a, Vector2 b, float TTL, float rot);

	int health;
	float TTL;
	Vector2 pos, dPos;

	void Update(float dx);

};