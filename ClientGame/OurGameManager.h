#pragma once

#include "stdafx.h"
#include <vector>
#include <string>

class BaseScreen : public Renderable
{
public:
	BaseScreen();

	virtual void Start();
	virtual void Stop(); //calls remove on all _objects and deletes them
	virtual void Update(float dt);
	virtual void Render();

	virtual void MessageHandler(String content) {}
	virtual void ReceiveMessage(Message *message) {}

protected:
	std::vector<Renderable*> _objects;
};

#define OurGame OurGameManager::GetInstance()

class OurGameManager : public GameManager
{
public:

	
	
	//=============================================

	//Define functions in here
	void SetScreen(int screen_number);

	//=============================================



	static OurGameManager &GetInstance();

	BaseScreen* GetCurrentScreen();

	virtual void Render();

	virtual void SoundEnded(AngelSoundHandle sound);

	virtual void ReceiveMessage(Message* message);

protected:
	OurGameManager();
	static OurGameManager *s_OurGameManager;

private:
	std::vector<BaseScreen*> _screens;
	int _current;
	AngelSampleHandle sample;
};
