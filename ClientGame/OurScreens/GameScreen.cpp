#include "stdafx.h"
#include "GameScreen.h"
#include <iostream>


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
	
	//speed used by the player
	speed = 6.5f;
	//default speed to reset to
	defspeed = 6.5f;

	//array counters to keep actor count lower
	mapPos = 0;
	transPos = 0;
	spawnPos = 0;

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

	exit = new Actor();
	exit->SetSprite(/*"C:\\Users\\Declan\\Downloads\\angel2d-master\\Code\\ClientGame*/"./Resources/Images/G2B.png", 0, GL_REPEAT, GL_LINEAR, false);
	exit->SetUVs(Vector2(0.0, 0.0), Vector2(1.0, 1.0));
	exit->SetSize(2.0f, 1.0f);
	exit->SetPosition(0, 50);
	exit->SetLayer("pause");
	//exit->SetColor(Color(1.0f, 1.0f, 1.0f, 1.0f, true));
	theWorld.Add(exit);
	_objects.push_back(exit);

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
			theWorld.Add(wallPiece);
			_objects.push_back(wallPiece);
			walls[mapPos] = wallPiece;
			mapPos++;
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
			theWorld.Add(wallPiece);
			_objects.push_back(wallPiece);
			transp[transPos] = wallPiece;
			transPos++;
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
			theWorld.Add(wallPiece);
			_objects.push_back(wallPiece);
			spawners[spawnPos] = wallPiece;
			spawnPos++;
		}
	}

	//and finally the player
	player = new Actor();
	player->SetSprite("C:\\Users\\Declan\\Downloads\\angel2d-master\\Code\\ClientGame\\Resources\\Images\\G2B.png");
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
			exit->SetPosition(x+12, y-9.5);
		}
		else {
			pause->SetPosition(0, 50);
			exit->SetPosition(0, 50);
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
			if (shottiming > 1.0f) {
				shottiming = 0;
				Vector2 vs = Vector2(x, y);
				Actor *wallPiece = new Actor();
				wallPiece->SetColor(1.0f, 1.0f, 0.0f, 0.1f);
				wallPiece->SetPosition(vs);
				wallPiece->SetLayer("hud");
				theWorld.Add(wallPiece);
				_objects.push_back(wallPiece);
			}
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
		for (int i = 0; i < mapPos; i++) {
			Vector2 v2 = Vector2(x, y);
			if (walls[i]->GetBoundingBox().Contains(v2)) {
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
			for (int i = 0; i < mapPos; i++) {
				Vector2 v2 = Vector2(x, y);
				if (walls[i]->GetBoundingBox().Contains(v2)) {
					x = lastX;
					y = lastY;
					break;
				}
			}
		
		//PROCESSING
		//transparency checking
		bool flag = false;
		for (int i = 0; i < transPos; i++) {
			Vector2 v2 = Vector2(x, y);
			if (transp[i]->GetBoundingBox().Contains(v2)) {
				flag = true;
				foreground->SetAlpha(0.2f);
				break;
			}
		}
		if (!flag) {
			foreground->SetAlpha(1.0f);
		}

		//do spawns
		if (timing > 1.0f) {
			timing -= 1.0f;
			for (int i = 0; i < spawnPos; i++) {
				Vector2 vs = spawners[i]->GetPosition();
				//randomize around spawners
				vs.X += MathUtil::RandomFloat() * 2 - 1;
				vs.Y += MathUtil::RandomFloat() * 2 - 1;
				Actor *wallPiece = new Actor();
				wallPiece->SetColor(1.0f, 0.0f, 1.0f, 0.1f);
				wallPiece->SetPosition(vs);
				wallPiece->SetLayer("hud");
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
	if (_active) {
		Vector2 v2 = MathUtil::ScreenToWorld(screenCoordinates.X, screenCoordinates.Y);
		if (paused) {
			if (exit->GetBoundingBox().Contains(v2)) {
				OurGame.SetScreen(0);
			}
		}
	}
}