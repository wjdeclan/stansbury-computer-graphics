#pragma once

#include <vector>
#include "../OurGameManager.h"
#include "../Mobs/Monster.h"

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
	int mapPos, transPos, spawnPos, mobPos;
	bool _active;
	float speed, defspeed;

	int dirX, dirY;

	float timing, shottiming;

	TextActor *pause;

	Actor *background;
	Actor *foreground;

	Actor *shot;
	
	vector < Actor* > solidWalls;
	vector < Actor* > transpWalls;
	vector < Actor* > spawners;
	vector < Fireball* > shots;
	Monster *mobs[20];

	Actor *player;
	AngelSampleHandle music;
};
