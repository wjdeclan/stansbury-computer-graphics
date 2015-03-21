#include "stdafx.h"
#include "LoseScreen.h"
#include "GameScreen.h"


LoseScreen::LoseScreen()
{
	//music = theSound.LoadSample("Resources/Sounds/xylophone.ogg", true /*stream*/);
	//if (music)
	//	theSound.PlaySound(music, 0.2f, true, 0);
}

void LoseScreen::Start()
{
	//create actors

	//and put them in the right place, color them, size them, etc.

	//and how to escape the credits screen
	instructions = new TextActor("Console", "Game Over\nYou Have Died\nPress Escape to give it another go.");
	theWorld.Add(instructions);
	_objects.push_back(instructions);
}

void LoseScreen::MessageHandler(String content)
{
	//handle escape messages
	if (content == "ESC") {
		OurGame._screens[3] = new GameScreen();
		OurGame.SetScreen(3);
	}
}

void LoseScreen::Update(float dt)
{
	//INPUT

	//PROCESSING
	Vector2 v2 = theCamera.GetPosition();

	instructions->SetPosition(v2.X, v2.Y);
	instructions->SetAlignment(TXT_Center);
	instructions->SetColor(Color(0.8f, 0.2f, 0.2f, 0.8f, true));

}