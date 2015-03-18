#include "stdafx.h"
#include "Fireball.h"

Fireball::Fireball(Vector2 v2, Vector2 v2b, float time, float rotation)
{
	TTL = time;
	pos = v2;
	dPos = v2b;
	this->SetRotation(rotation);
	this->SetSprite("../Resources/Images/shot.png");
	this->SetLayer("hud");

}

void Fireball::Update(float dx)
{
	pos += dPos*dx;
	TTL -= dx;
	this->SetPosition(pos);
}
