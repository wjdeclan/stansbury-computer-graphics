#pragma once

#include "../OurGameManager.h"

class SettingsScreen : public BaseScreen
{
public:
	SettingsScreen();

	virtual void Start();
	virtual void Update(float dt);

	virtual void MessageHandler(String content);

private:
	AngelSampleHandle music;
};
