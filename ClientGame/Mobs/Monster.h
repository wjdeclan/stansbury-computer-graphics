#pragma once
#include "../../Angel/Actors/Actor.h"

class Monster : public Actor
{
public:
	Monster();

	int health;
	
	void Start();
	void Update();

};