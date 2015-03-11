#pragma once

#include "../OurGameManager.h"

class CreditsScreen : public BaseScreen
{
public:
	CreditsScreen();

	virtual void Start();
	virtual void Update(float dt);

	virtual void MessageHandler(String content);

private:
	AngelSampleHandle music;
};
