#pragma once

#include "../OurGameManager.h"

class StartScreen : public BaseScreen
{
public:
	StartScreen();

	virtual void Start();
	virtual void Update(float dt);

	virtual void MessageHandler(String content);

private:
	int pos;
	Actor *select;
	AngelSampleHandle music;
};
