#include "stdafx.h"
#include "SettingsScreen.h"


SettingsScreen::SettingsScreen()
{
	//music = theSound.LoadSample("Resources/Sounds/xylophone.ogg", true /*stream*/);
	//if (music)
	//	theSound.PlaySound(music, 0.2f, true, 0);
}

void SettingsScreen::Start()
{
	TextActor *Settings = new TextActor("Console", "Settings");
	TextActor *Notice = new TextActor("Console", "We don't have any settings yet, sorry about that.");

	Settings->SetPosition(0, 9);
	Settings->SetAlignment(TXT_Center);
	Settings->SetColor(Color(0.8f, 0.2f, 0.2f, 1.0f, true));
	theWorld.Add(Settings);
	_objects.push_back(Settings);
	Notice->SetPosition(0, 5);
	Notice->SetAlignment(TXT_Center);
	Notice->SetColor(Color(1.0f, 1.0f, 1.0f, 1.0f, true));
	theWorld.Add(Notice);
	_objects.push_back(Notice);

	TextActor *instructions = new TextActor("Console", "Press Escape to return to menu.");
	instructions->SetPosition(0, -9.5);
	instructions->SetAlignment(TXT_Center);
	instructions->SetColor(Color(1.0f, 1.0f, 1.0f, 0.8f, true));
	theWorld.Add(instructions);
	_objects.push_back(instructions);
}

void SettingsScreen::MessageHandler(String content)
{
	if (content == "ESC") {
		OurGame.SetScreen(0);
	}
}

void SettingsScreen::Update(float dt)
{
	//INPUT

	//PROCESSING

}