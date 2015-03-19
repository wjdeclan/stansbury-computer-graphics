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

private:
	bool paused;
	float x, y;
	float lastX, lastY;
	bool _active;
	float speed, defspeed;

	int dirX, dirY;

	float timing, spawntiming, shottiming;

	TextActor *pause, *timer;

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
