#include "stdafx.h"
#include "LoseScreen.h"


LoseScreen::LoseScreen()
{
	//music = theSound.LoadSample("Resources/Sounds/xylophone.ogg", true /*stream*/);
	//if (music)
	//	theSound.PlaySound(music, 0.2f, true, 0);
}

void LoseScreen::Start()
{
	//create actors
	TextActor *AuthorTitle = new TextActor("Console", "Game Over");
	TextActor *Authors = new TextActor("Console", "YOU DIED");

	//and put them in the right place, color them, size them, etc.
	Vector2 v2 = theCamera.GetPosition();
	AuthorTitle->SetPosition(v2.X, v2.Y+7);
	AuthorTitle->SetAlignment(TXT_Center);
	AuthorTitle->SetColor(Color(1.0f, 1.0f, 1.0f, 1.0f, true));
	theWorld.Add(AuthorTitle);
	_objects.push_back(AuthorTitle);
	Authors->SetPosition(v2.X, v2.Y+5);
	Authors->SetAlignment(TXT_Center);
	Authors->SetColor(Color(1.0f, 1.0f, 1.0f, 1.0f, true));
	theWorld.Add(Authors);
	_objects.push_back(Authors);

	//and how to escape the credits screen
	TextActor *instructions = new TextActor("Console", "Press Escape to return to menu.");
	instructions->SetPosition(0, -9.5);
	instructions->SetAlignment(TXT_Center);
	instructions->SetColor(Color(1.0f, 1.0f, 1.0f, 0.8f, true));
	theWorld.Add(instructions);
	_objects.push_back(instructions);
}

void LoseScreen::MessageHandler(String content)
{
	//handle escape messages
	if (content == "ESC") {
		OurGame.SetScreen(0);
	}
}

void LoseScreen::Update(float dt)
{
	//INPUT

	//PROCESSING

}