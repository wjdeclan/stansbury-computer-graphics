#include "stdafx.h"
#include "StartScreen.h"


StartScreen::StartScreen()
{
	//music = theSound.LoadSample("Resources/Sounds/xylophone.ogg", true /*stream*/);
	//if (music)
	//	theSound.PlaySound(music, 0.2f, true, 0);
}

void StartScreen::Start()
{
	select = new Actor();
	select->SetSize(8.0f, 2.0f);
	select->SetPosition(0, 5);
	select->SetColor(Color(0.5f, 0.5f, 0.5f, 1.0f, true));
	theWorld.Add(select);
	_objects.push_back(select);

	player = new Actor();
	player->SetPosition(0, 0);
	player->SetColor(Color(0.0f, 0.0f, 0.0f, 0.0f, true));

	TextActor *instructions = new TextActor("Console", "Space to select. W/S to move.");
	instructions->SetPosition(0, -9.5);
	instructions->SetAlignment(TXT_Center);
	instructions->SetColor(Color(1.0f, 1.0f, 1.0f, 0.8f, true));
	theWorld.Add(instructions);
	_objects.push_back(instructions);

	TextActor *title = new TextActor("Console", "Project R.O.H.A.N.");
	title->SetPosition(0, 7);
	title->SetAlignment(TXT_Center);
	title->SetColor(Color(0.8f, 0.2f, 0.2f, 1.0f, true));
	theWorld.Add(title);
	_objects.push_back(title);

	TextActor *begin = new TextActor("Console", "Start");
	begin->SetPosition(0, 5);
	begin->SetAlignment(TXT_Center);
	begin->SetColor(Color(1.0f, 1.0f, 1.0f, 1.0f, true));
	theWorld.Add(begin);
	_objects.push_back(begin);
	pos = 0;

	TextActor *settings = new TextActor("Console", "Settings");
	settings->SetPosition(0, 3);
	settings->SetAlignment(TXT_Center);
	settings->SetColor(Color(1.0f, 1.0f, 1.0f, 1.0f, true));
	theWorld.Add(settings);
	_objects.push_back(settings);

	TextActor *credits = new TextActor("Console", "Credits");
	credits->SetPosition(0, 1);
	credits->SetAlignment(TXT_Center);
	credits->SetColor(Color(1.0f, 1.0f, 1.0f, 1.0f, true));
	theWorld.Add(credits);
	_objects.push_back(credits);
}

void StartScreen::MessageHandler(String content)
{
	if (content == "W") {
		pos = (pos + 2) % 3;
	}
	if (content == "S") {
		pos = (pos + 1) % 3;
	}
	if (content == "SPC") {
		switch (pos) {
		case 0:
			OurGame.SetScreen(3);
			break;
		case 1:
			OurGame.SetScreen(2);
			break;
		case 2:
			OurGame.SetScreen(1);
			break;
		}
	}
}

void StartScreen::Update(float dt)
{
	//INPUT
	
	//PROCESSING
	select->SetPosition(0, 5 - 2 * pos);

}