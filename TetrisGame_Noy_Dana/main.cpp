//Noy Zion - 212198766
//Dana Reshef - 314652439

#include "Menu.h"
#include <stdlib.h>
#include <iostream>
#include <time.h>
using namespace std;

int main()
{
	srand(time(NULL));

	bool gamePaused = false;
	bool exitGame = false;

	char status = Menu::menu(gamePaused,exitGame);
	while (status == (char)Menu::DEFINES::START_GAME && !exitGame)
	{
		status = Menu::menu(gamePaused, exitGame);
		if (status == (char)Menu::DEFINES::END_GAME)
		{
			break;
		}
		status = (char)Menu::DEFINES::START_GAME;
	}
}