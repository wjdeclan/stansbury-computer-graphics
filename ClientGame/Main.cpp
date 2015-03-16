
#include "stdafx.h"

#include "OurGameManager.h"

int main(int argc, char* argv[])
{
	// get things going
	//  optional parameters:
	//		int windowWidth			default: 1024
	//		int windowHeight		default: 768
	//		std::string windowName	default: "Angel Engine"
	//		bool antiAliasing		default: false
	//		bool fullScreen			default: false
	//		bool resizable			default: false
	theWorld.Initialize(780, 600, "Hello World", false, false, false);
	


	//==============================================================================
	
	//defining layers actors can be added to, lower numbers are further back, can be negative
	theWorld.NameLayer("scene", 0);
	theWorld.NameLayer("background", 1);
	theWorld.NameLayer("foreground", 2);
	theWorld.NameLayer("hud", 3);
	theWorld.NameLayer("pause", 4);

	//adds the default grid so you can more easily place Actors
	//theWorld.Add(new GridActor(), 5);
	
	//black screen, cause that's useful
	theWorld.SetBackgroundColor(Color(0.0f, 0.0f, 0.0f, 1.0f, true));
	
	//give this game a manager so that things can actually happen
	theWorld.SetGameManager(&OurGame);
	
	//==============================================================================
	


	// do all your setup first, because this function won't return until you're exiting
	theWorld.StartGame();
	
	// any cleanup can go here
	theWorld.Destroy();
	
	return 0;
}
