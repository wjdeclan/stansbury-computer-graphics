#include "stdafx.h"
#include "Fireball.h"
#include "../OurGameManager.h"

Fireball::Fireball(Vector2 v2, Vector2 v2b, float time, float rotation)
{
	TTL = time;
	pos = v2;
	dPos = v2b;
	this->SetRotation(rotation);
	this->SetColor(Color(0.0f, 0.0f, 0.0f, 1.0f));
	//this->SetSprite("../Resources/Images/shot.png");
	this->SetLayer("hud");

}

void Fireball::Update(float dx)
{
	pos += dPos*dx;
	TTL -= dx;
	this->SetPosition(pos);
	if (TTL <= 0.0f) {
		theWorld.Remove(this);
	}
}
