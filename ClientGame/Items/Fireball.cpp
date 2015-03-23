#include "stdafx.h"
#include "Fireball.h"
#include "../OurGameManager.h"

Fireball::Fireball(Vector2 v2, Vector2 v2b, float time, float rotation)
{
	TTL = time;
	pos = v2;
	dPos = v2b;
	dmg = 75;
	this->SetRotation(rotation);
	this->SetSize(0.6f, 0.8f);
	//this->SetColor(Color(0.0f, 0.0f, 0.0f, 1.0f));
	this->SetSprite("./Resources/Images/shot.png");
	this->SetLayer("hud");

}

void Fireball::Update(float dx)
{

}

void Fireball::TrueUpdate(float dx) {
	if (TTL <= 0.0f) {
	}
	else {
		pos += dPos*dx;
		TTL -= dx;
	}
}

int Fireball::GetDamage() {
	return dmg;
}

float Fireball::getTime() {
	return TTL;
}

Vector2 Fireball::getPos() {
	return pos;
}