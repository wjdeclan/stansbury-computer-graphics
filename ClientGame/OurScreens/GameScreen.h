#pragma once

#include <vector>
#include "../OurGameManager.h"
#include "../Mobs/Monster.h"
#include "../Items/Fireball.h"

using namespace std;

class GameScreen : public BaseScreen, public MouseListener
{
public:
	GameScreen();

	virtual void Start();
	virtual void Update(float dt);

	virtual void MessageHandler(String content);
	virtual void MouseDownEvent(Vec2i screenCoordinates, MouseButtonInput button);

	bool hitCheck(BoundingBox bb);

private:
	bool paused, skip;
	Actor *select;
	float x, y;
	int pos;
	float lastX, lastY;
	bool _active;
	float speed, defspeed;
	float spawnSpeed;
	float rate;
	int mHealth, mSpeed;
	int cashMoney, price;
	int dmg;
	int reward;

	int dirX, dirY;

	float timing, spawntiming, shottiming;

	TextActor *pause, *timer, *instructions, *cashDisp;
	TextActor *shop1, *shop2, *shop3;

	Actor *background;
	Actor *foreground;
	
	vector < Actor* > solidWalls;
	vector < Actor* > transpWalls;
	vector < Actor* > spawners;
	vector < Fireball* > shots;
	vector < Monster* > mobs;

	Actor *player;
	AngelSampleHandle music;
};
