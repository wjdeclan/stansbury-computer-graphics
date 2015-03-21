#pragma once

#include "../OurGameManager.h"

class LoseScreen : public BaseScreen
{
public:
	LoseScreen();

	virtual void Start();
	virtual void Update(float dt);

	virtual void MessageHandler(String content);

private:
	AngelSampleHandle music;

	TextActor *instructions;
};
