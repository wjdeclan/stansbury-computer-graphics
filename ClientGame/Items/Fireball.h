#pragma once
#include "../../Angel/Actors/Actor.h"
#include "../OurGameManager.h"
#include <vector>

using namespace std;

class Fireball : public Actor
{
public:
	Fireball(Vector2 a, Vector2 b, float TTL, float rot);

	int dmg;

	float TTL;
	Vector2 pos, dPos;

	void Update(float dx);

	int GetDamage();
	float getTime();
	Vector2 getPos();
	void TrueUpdate(float dx);

};