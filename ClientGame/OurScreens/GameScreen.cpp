#include "stdafx.h"
#include "GameScreen.h"
#include "../Mobs/Monster.h"
#include "../Items/Fireball.h"
#include <iostream>

using namespace std;

GameScreen::GameScreen()
{
	//kept around in case we want music later
	//music = theSound.LoadSample("Resources/Sounds/xylophone.ogg", true /*stream*/);
	//if (music)
	//	theSound.PlaySound(music, 0.2f, true, 0);

	//watch for clicks or not
	_active = false;
}

void GameScreen::Start()
{
	//turn on clicks, turn off pause
	_active = true;
	paused = false;

	skip = false;
	
	//speed used by the player
	speed = 6.5f;
	//default speed to reset to
	defspeed = 6.5f;

	//various timers
	timing = 0;
	spawntiming = 0;
	shottiming = 0;
	spawnSpeed = 3.0f;
	mHealth = 100;

	timer = new TextActor("Console", "");
	timer->SetColor(Color(0.0f, 0.0f, 0.0f, 1.0f));
	timer->SetAlignment(TXT_Center);
	timer->SetLayer("pause");
	theWorld.Add(timer);
	_objects.push_back(timer);

	//menu items
	pause = new TextActor("Console", "PAUSED");
	pause->SetColor(Color(1.0f, 1.0f, 1.0f, 0.2f, true));
	pause->SetAlignment(TXT_Center);
	pause->SetPosition(0, 50);
	pause->SetLayer("pause");
	theWorld.Add(pause);
	_objects.push_back(pause);

	instructions = new TextActor("Console", "WARNING: FLYING EYEBALLS INCOMING\nTHEY CAN GO ABOVE WALLS\nFLEE FOR YOUR LIFE");
	instructions->SetColor(Color(1.0f, 0.1f, 0.1f, 1.0f));
	instructions->SetAlignment(TXT_Center);
	instructions->SetLayer("hud");
	theWorld.Add(instructions);
	_objects.push_back(instructions);

	//map building	
	background = new Actor();
	background->SetLayer("background");
	background->SetSprite("./Resources/Images/background.png");
	background->SetSize(78.0f, 60.0f);
	background->SetPosition(0.0f, 0.0f);
	theWorld.Add(background);
	_objects.push_back(background);

	foreground = new Actor();
	foreground->SetLayer("foreground");
	foreground->SetSprite("./Resources/Images/clear.png");
	foreground->SetAlpha(1.0f);
	foreground->SetSize(78.0f, 60.0f);
	foreground->SetPosition(0.0f, 0.0f);
	theWorld.Add(foreground);
	_objects.push_back(foreground);

	//loading from image file
	Vector2List positions;
	if (
		PixelsToPositions(
		"./Resources/Images/walls.png", positions, 1.0f, Color(0.0f, 0.0f, 0.0f)
		)
		)
	{
		for (unsigned int i = 0; i < positions.size(); i++)
		{
			Actor *wallPiece = new Actor();
			wallPiece->SetColor(0.0f, 0.0f, 0.0f, 0.0f);
			wallPiece->SetPosition(positions[i] + Vector2(0.5f, 0.5f));
			wallPiece->SetLayer("scene");
			solidWalls.push_back(wallPiece);
			theWorld.Add(wallPiece);
			_objects.push_back(wallPiece);
		}
	}
	positions.clear();
	if (
		PixelsToPositions(
		"./Resources/Images/walls.png", positions, 1.0f, Color(1.0f, 1.0f, 1.0f)
		)
		)
	{
		for (unsigned int i = 0; i < positions.size(); i++)
		{
			Actor *wallPiece = new Actor();
			wallPiece->SetColor(0.0f, 0.0f, 0.0f, 0.0f);
			wallPiece->SetPosition(positions[i] + Vector2(0.5f, 0.5f));
			wallPiece->SetLayer("scene");
			transpWalls.push_back(wallPiece);
			theWorld.Add(wallPiece);
			_objects.push_back(wallPiece);
		}
	}
	positions.clear();
	if (
		PixelsToPositions(
		"./Resources/Images/walls.png", positions, 1.0f, Color(1.0f, 0.0f, 1.0f)
		)
		)
	{
		for (unsigned int i = 0; i < positions.size(); i++)
		{
			Actor *wallPiece = new Actor();
			wallPiece->SetColor(0.0f, 0.0f, 0.0f, 0.0f);
			wallPiece->SetPosition(positions[i] + Vector2(0.5f, 0.5f));
			wallPiece->SetLayer("scene");
			spawners.push_back(wallPiece);
			theWorld.Add(wallPiece);
			_objects.push_back(wallPiece);
		}
	}

	//and finally the player
	player = new Actor();
	player->SetSprite("./Resources/Images/char.png");
	player->SetSize(0.5f, 0.5);
	player->SetPosition(0, 0);
	//player->SetColor(Color(1.0f, 1.0f, 1.0f, 1.0f, true));
	x = 0.0f;
	y = 0.0f;
	lastX = x;
	lastY = y;
	player->SetLayer("foreground");
	//theCamera. LockTo(player);
	theWorld.Add(player);
	_objects.push_back(player);
	theCamera.LockTo(player);
}

void GameScreen::MessageHandler(String content)
{
	//listen for escape from input bindings ini file
	if (content == "ESC") {
		paused = !paused;
		//act as toggle
		if (paused) {
			pause->SetPosition(x, y+5);
		}
		else {
			pause->SetPosition(0, 50);
		}
	}
}

void GameScreen::Update(float dt)
{
	if (!paused) {
		if (timing <= 1.0f) {
			instructions->SetPosition(x, y);
			instructions->SetColor(Color(1.0f,0.1f,0.1f,1.0f-timing));
		}
		timing += dt;
		timer->SetDisplayString(to_string(timing));
		

		if (timing > 60.0 && timing < 120.0)
		{
			spawnSpeed = 2.5;
			mHealth = 150;
		}
		else if (timing > 120.0 && timing < 180.0)
		{
			spawnSpeed = 2.0;
			mHealth = 250;
		}
		else if (timing > 180.0 && timing < 240.0)
		{
			spawnSpeed = 1.0;
			mHealth = 350;
		}
		else if (timing > 240.0)
		{
			spawnSpeed = .5;
			mHealth = 500;
		}


		timer->SetPosition(x, y + 7.0f);
		//mob spawner timer
		spawntiming += dt;
		//player shooting timer
		shottiming += dt;

		//hit detection on walls
		lastX = x;
		lastY = y;

		//and speed reset
		speed = defspeed;

		//sprinting
		if (theInput.IsKeyDown(ANGEL_KEY_LEFTSHIFT)) {
			speed += 2;
		}

		//shooting
		if (theInput.IsKeyDown(ANGEL_KEY_SPACE)) {
			std::cout << "shoot";
			
		}

		//INPUT
		//WASD movement
		if (theInput.IsKeyDown('s') || theInput.IsKeyDown(ANGEL_KEY_DOWNARROW)
			) {
			if (theInput.IsKeyDown('a') || theInput.IsKeyDown(ANGEL_KEY_LEFTARROW)
				) {
				y -= speed / 1.41 * dt;
			}
			else if (theInput.IsKeyDown('d') || theInput.IsKeyDown(ANGEL_KEY_RIGHTARROW)
				) {
				y -= speed / 1.41 * dt;
			} else {
				y -= speed * dt;
			}
			
		}
		else if (theInput.IsKeyDown('w') || theInput.IsKeyDown(ANGEL_KEY_UPARROW)
			) {
			if (theInput.IsKeyDown('a') || theInput.IsKeyDown(ANGEL_KEY_LEFTARROW)
				) {
				y += speed / 1.41 * dt;
			}
			else if (theInput.IsKeyDown('d') || theInput.IsKeyDown(ANGEL_KEY_RIGHTARROW)
				) {
				y += speed / 1.41 * dt;
			}
			else {
				y += speed * dt;
			}
			
		}
		//hit reset
		for (int i = 0; i < solidWalls.size(); i++) {
			Vector2 v2 = Vector2(x, y);
			BoundingBox bb = solidWalls.at(i)->GetBoundingBox();
			if (bb.Contains(v2)) {
				x = lastX;
				y = lastY;
				break;
			}
		}
		lastY = y;
		//and the same for X
			if (theInput.IsKeyDown('a') || theInput.IsKeyDown(ANGEL_KEY_LEFTARROW)
				) {
				if (theInput.IsKeyDown('w') || theInput.IsKeyDown(ANGEL_KEY_UPARROW)
					) {
					x -= speed / 1.41 * dt;
				}
				else if (theInput.IsKeyDown('s') || theInput.IsKeyDown(ANGEL_KEY_DOWNARROW)
					) {
					x -= speed / 1.41 * dt;
				}
				else {
					x -= speed * dt;
				}
			}
			else if (theInput.IsKeyDown('d') || theInput.IsKeyDown(ANGEL_KEY_RIGHTARROW)
				) {
				if (theInput.IsKeyDown('w') || theInput.IsKeyDown(ANGEL_KEY_UPARROW)
					) {
					x += speed / 1.41 * dt;
				}
				else if (theInput.IsKeyDown('s') || theInput.IsKeyDown(ANGEL_KEY_DOWNARROW)
					) {
					x += speed / 1.41 * dt;
				}
				else {
					x += speed * dt;
				}
			}
			for (int i = 0; i < solidWalls.size(); i++) {
				Vector2 v2 = Vector2(x, y);
				BoundingBox bb = solidWalls.at(i)->GetBoundingBox();
				if (bb.Contains(v2)) {
					x = lastX;
					y = lastY;
					break;
				}
			}
		
		//PROCESSING
		//transparency checking
		bool flag = false;
		for (int i = 0; i < transpWalls.size(); i++) {
			Vector2 v2 = Vector2(x, y);
			BoundingBox bb = transpWalls.at(i)->GetBoundingBox();
			if (bb.Contains(v2)) {
				flag = true;
				foreground->SetAlpha(0.4f);
				break;
			}
		}
		if (!flag) {
			foreground->SetAlpha(1.0f);
		}

		for (int i = 0; i < mobs.size(); i++) {
			mobs.at(i)->Update(dt);
			if (mobs.at(i)->GetBoundingBox().Intersects(player->GetBoundingBox())) {
				skip = true;
				OurGame.SetScreen(4);
			}
			if (mobs.at(i)->getHealth() <= 0) {
				theWorld.Remove(mobs.at(i));
				mobs.erase(mobs.begin() + i);
			}
		}

		for (int i = 0; i < shots.size(); i++) {
			shots.at(i)->Update(dt);
			if (hitCheck(shots.at(i)->GetBoundingBox()) || shots.at(i)->getTime() <= 0.0f) {
				theWorld.Remove(shots.at(i));
				shots.erase(shots.begin()+i);
			}
		}

		//do spawns
		if (spawntiming > spawnSpeed) {
			spawntiming -= spawnSpeed;
			for (int i = 0; i < spawners.size(); i++) {
				Vector2 vs = spawners.at(i)->GetPosition();
				//randomize around spawners
				vs.X += MathUtil::RandomFloat() * 10 - 5;
				vs.Y += MathUtil::RandomFloat() * 10 - 5;
				Monster *wallPiece = new Monster(vs, player, mHealth);
				wallPiece->SetPosition(vs);
				wallPiece->SetLayer("pause");
				mobs.push_back(wallPiece);
				theWorld.Add(wallPiece);
				_objects.push_back(wallPiece);
			}
		}

		//and redraw player
		player->SetPosition(x, y);
	}
	else {
		
	}
}

void GameScreen::MouseDownEvent(Vec2i screenCoordinates, MouseButtonInput button)
{
	//click to exit to main menu, broken in current version
	if (_active && !skip) {
		Vector2 v2 = MathUtil::ScreenToWorld(screenCoordinates.X, screenCoordinates.Y);
		if (shottiming > 0.2f) {
			shottiming = 0;
			v2 -= Vector2(x, y);
			v2.Normalize();
			v2 *= 10;
			float i = MathUtil::AngleFromVector(v2);
			Fireball *f = new Fireball(Vector2(x, y), v2, 1.0f, MathUtil::ToDegrees(i) - 85.0f);
			theWorld.Add(f);
			_objects.push_back(f);
			shots.push_back(f);
		}
	}
}

bool GameScreen::hitCheck(BoundingBox bb) {
	for (int i = 0; i < solidWalls.size(); i++) {
		if (solidWalls.at(i)->GetBoundingBox().Intersects(bb)) {
			return true;
			break;
		}
	}

	for (int i = 0; i < mobs.size(); i++) {
		if (mobs.at(i)->GetBoundingBox().Intersects(bb)) {
			mobs.at(i)->Damage(shots.at(0)->GetDamage());
			return true;
			break;
		}
	}

	return false;
}
