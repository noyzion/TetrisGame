#ifndef  MENU__H
#define MENU__H

class Menu
{
	static void openMessage();
	static void openMessagePause();
	static void instructions();
	static bool chooseColors();
	static void startGameAnnouncement();


public:

	enum class DEFINES {
		START_GAME = 0, START_GAME_HH = '1', START_GAME_HC = '2', START_GAME_CC = '3',
		WITH_COLORS = 1, WITHOUT_COLORS = 2, CONTINUE = '4',
		INSTRUCTIONS = '8', END_GAME = '9', LEFT = 1, RIGHT = 2, NOT_VALID
	};

	static char gameStatus(bool& paused, bool& continueGame, bool& endGame, char option);
	static char menu(bool& gamePaused, bool& exitGame);

};

#endif // ! MENU__H
