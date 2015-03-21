#include "stdafx.h"
#include "CreditsScreen.h"


CreditsScreen::CreditsScreen()
{
	//music = theSound.LoadSample("Resources/Sounds/xylophone.ogg", true /*stream*/);
	//if (music)
	//	theSound.PlaySound(music, 0.2f, true, 0);
}

void CreditsScreen::Start()
{
	//create actors
	TextActor *AuthorTitle = new TextActor("Console", "Authors:");
	TextActor *Authors = new TextActor("Console", "Declan Whitford Jones & Nick Brown");
	TextActor *Motto = new TextActor("Console", "If it fits, it ships.");

	//and put them in the right place, color them, size them, etc.
	AuthorTitle->SetPosition(0, 7);
	AuthorTitle->SetAlignment(TXT_Center);
	AuthorTitle->SetColor(Color(1.0f, 1.0f, 1.0f, 1.0f, true));
	theWorld.Add(AuthorTitle);
	_objects.push_back(AuthorTitle);

	Authors->SetPosition(0, 5);
	Authors->SetAlignment(TXT_Center);
	Authors->SetColor(Color(1.0f, 1.0f, 1.0f, 1.0f, true));
	theWorld.Add(Authors);
	_objects.push_back(Authors);

	Motto->SetPosition(0, 3);
	Motto->SetAlignment(TXT_Center);
	Motto->SetColor(Color(1.0f, 1.0f, 1.0f, 1.0f, true));
	theWorld.Add(Motto);
	_objects.push_back(Motto);


	//and how to escape the credits screen
	TextActor *instructions = new TextActor("Console", "Press Escape to return to menu.");
	instructions->SetPosition(0, -9.5);
	instructions->SetAlignment(TXT_Center);
	instructions->SetColor(Color(1.0f, 1.0f, 1.0f, 0.8f, true));
	theWorld.Add(instructions);
	_objects.push_back(instructions);
}

void CreditsScreen::MessageHandler(String content)
{
	//handle escape messages
	if (content == "ESC") {
		OurGame.SetScreen(0);
	}
}

void CreditsScreen::Update(float dt)
{
	//INPUT

	//PROCESSING
	
}