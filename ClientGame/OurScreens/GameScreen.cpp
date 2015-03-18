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
	shot = new Actor();
	theWorld.Remove(shot);

	//turn on clicks, turn off pause
	_active = true;
	paused = false;
	
	//speed used by the player
	speed = 6.5f;
	//default speed to reset to
	defspeed = 6.5f;

	//array counters to keep actor count lower
	mapPos = 0;
	transPos = 0;
	spawnPos = 0;
	mobPos = 0;

	//various timers
	timing = 0;
	shottiming = 0;

	//menu items
	pause = new TextActor("Console", "PAUSED");
	pause->SetColor(Color(1.0f, 1.0f, 1.0f, 0.2f, true));
	pause->SetAlignment(TXT_Center);
	pause->SetPosition(0, 50);
	pause->SetLayer("pause");
	theWorld.Add(pause);
	_objects.push_back(pause);

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
		//mob spawner timer
		timing += dt;
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
			if (bb.Contains(shot->GetPosition())) {
				theWorld.Remove(shot);
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

		for (int i = 0; i < shots.size(); i++) {
			shots.at(i)->Update(dt);
		}

		//do spawns
		if (timing > 7.0f && mobPos < 20) {
			timing -= 7.0f;
			for (int i = 0; i < spawners.size(); i++) {
				Vector2 vs = spawners.at(i)->GetPosition();
				//randomize around spawners
				vs.X += MathUtil::RandomFloat() * 10 - 5;
				vs.Y += MathUtil::RandomFloat() * 10 - 5;
				Monster *wallPiece = new Monster(vs.X, vs.Y);
				wallPiece->SetPosition(vs);
				wallPiece->SetLayer("hud");
				mobs[mobPos] = wallPiece;
				mobPos++;
				theWorld.Add(wallPiece);
				_objects.push_back(wallPiece);
			}
		}

		for (int i = 0; i < mobPos; i++) {
			mobs[i]->Update(dt);
		}

		//and redraw player
		player->SetPosition(x, y);

		if (shottiming > 1.0f) {
			theWorld.Remove(shot);
		}
	}
	else {
		
	}
}

void GameScreen::MouseDownEvent(Vec2i screenCoordinates, MouseButtonInput button)
{
	//click to exit to main menu, broken in current version
	if (_active) {
		Vector2 v2 = MathUtil::ScreenToWorld(screenCoordinates.X, screenCoordinates.Y);
		if (shottiming > 0.5f) {
			shottiming = 0;
			v2 -= Vector2(x, y);
			v2.Normalize();
			v2 *= 10;
			v2 += Vector2(x, y);
			float i = MathUtil::AngleFromVector(v2 - Vector2(x, y));
			Fireball *f = new Fireball(Vector2(x, y), v2, 1.0f, MathUtil::ToDegrees(i) - 90.0f);
			theWorld.Add(f);
			_objects.push_back(f);
			shots.push_back(f);
		}
	}
}