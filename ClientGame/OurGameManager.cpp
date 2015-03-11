
#include "stdafx.h"
#include "OurGameManager.h"

//==================================================================

//#include [INSERT SCREEN NAME]
//etc.

#include "OurScreens/StartScreen.h"
#include "OurScreens/CreditsScreen.h"
#include "OurScreens/SettingsScreen.h"
#include "OurScreens/GameScreen.h"

//===================================================================

BaseScreen::BaseScreen() {}

void BaseScreen::Start(){}

void BaseScreen::Stop()
{
	std::vector<Renderable*>::iterator it = _objects.begin();
	while (_objects.end() != it)
	{
		// we're pre-destroying physics bodies here because it 
		//  can mess with the pathfinding regeneration.
		PhysicsActor* pa = dynamic_cast<PhysicsActor*> (*it);
		if (pa != NULL)
		{
			if (pa->GetBody() != NULL)
			{
				pa->GetBody()->SetUserData(NULL);
				theWorld.GetPhysicsWorld().DestroyBody(pa->GetBody());
				pa->ResetBody();
			}
		}
		(*it)->Destroy();
		it++;
	}
	_objects.clear();
}

void BaseScreen::Update(float dt) {}
void BaseScreen::Render() {}



OurGameManager* OurGameManager::s_OurGameManager = NULL;

OurGameManager::OurGameManager()
{
	//subscribe to messages
	//theSwitchboard.SubscribeTo(this, "MoveForwards");
	//theSwitchboard.SubscribeTo(this, "MoveBackwards");
	theSwitchboard.SubscribeTo(this, "SPC");
	theSwitchboard.SubscribeTo(this, "W");
	theSwitchboard.SubscribeTo(this, "A");
	theSwitchboard.SubscribeTo(this, "S");
	theSwitchboard.SubscribeTo(this, "D");
	theSwitchboard.SubscribeTo(this, "ESC");


	//===========================================================================

	//Do this \/ for every screen, keeping track of what the hell goes where
	//_screens.push_back(new BaseScreenMainMenu());							// 0
	
	_screens.push_back(new StartScreen());
	_screens.push_back(new CreditsScreen());
	_screens.push_back(new SettingsScreen());
	_screens.push_back(new GameScreen());

	//And this defines where we gon start
	unsigned int startingIndex = 0;
	
	//===========================================================================

	if (_screens.size() > startingIndex)
	{
		theWorld.Add(_screens[startingIndex]);
		_screens[startingIndex]->Start();
		_current = startingIndex;
	}
	else
	{
		_current = -1;
	}

	// We must set the sound callback method.  Although, I'm wondering if we should 
	// allow them to not specify it if they don't need the functionality.
	theSound.SetSoundCallback(this, &GameManager::SoundEnded);

	sample = theSound.LoadSample("Resources/Sounds/click.ogg", false /*no stream*/);
}

OurGameManager& OurGameManager::GetInstance()
{
	if (s_OurGameManager == NULL)
	{
		s_OurGameManager = new OurGameManager();
	}
	return *s_OurGameManager;
}

BaseScreen* OurGameManager::GetCurrentScreen()
{
	return _screens[_current];
}

void OurGameManager::ReceiveMessage(Message* message)
{
	_screens[_current]->MessageHandler(message->GetMessageName());
	//===============================================
	//if (message->GetMessageName() == "SpaceBar" && _current = 0) {
	//	_current++;
	//}
	//message->GetMessageName() is the name of a given message, check if it matches something, then run a function

	//===============================================
}

void OurGameManager::SetScreen(int screen_number)
{
	_screens[_current]->Stop();
	theWorld.Remove(_screens[_current]);
	_screens[screen_number]->Start();
	theWorld.Add(_screens[screen_number]);
	_current = screen_number;	
}

void OurGameManager::Render()
{
	glColor3f(0.5f, 0.5f, 0.5f);
	char* infoString = "";
	int xOffset = 0;
	if (_current == 0)
	{
		infoString = "[A/Space]: Next";
		xOffset = 887;
	}
	else if (_current == _screens.size() - 1)
	{
		infoString = "[Back/Minus]: Previous";
		xOffset = 824;
	}
	else
	{
		infoString = "[A/Space]: Next [Back/Minus]: Previous";
		xOffset = 680;
	}

	int yOffset = 763;
	if (theWorld.IsHighResScreen())
	{
		// the perils of using pixel coordinates in a post-retina world
		xOffset *= 2;
		yOffset *= 2;
	}

	DrawGameText(infoString, "ConsoleSmall", xOffset, yOffset);
}

void OurGameManager::SoundEnded(AngelSoundHandle sound)
{
	// Detect sounds that have ended here.
}