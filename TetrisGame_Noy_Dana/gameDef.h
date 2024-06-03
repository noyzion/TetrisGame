#ifndef GAMEDEF__H
#define GAMEDEF__H

class GameDef
{

public:
	// game dimensions
	static constexpr int GAME_WIDTH = 12;
	static constexpr int GAME_HEIGHT = 18;

	// the left side of the game grid
	static constexpr int MIN_X_LEFT = 10;
	static constexpr int MID_X_LEFT = 16;

	// the top of the game grid
	static constexpr int MIN_Y = 3;

	// the right side of the game grid
	static constexpr int MIN_X_RIGHT = 32;
	static constexpr int MID_X_RIGHT = 38;

	static constexpr int SPEED = 200;

	//key inputs, representing player controls
	enum class eKeys {
		LEFT_L = 'a', RIGHT_L = 'd', ROTATE_CLOCKWISE_L = 's', ROTATE_COUNTERCLOCKWISE_L = 'w', DROP_L = 'x'
		, LEFT_UPPER_L = 'A', RIGHT_UPPER_L = 'D', ROTATE_CLOCKWISE_UP_L = 'S', ROTATE_COUNTERCLOCKWISE_UP_L = 'W', DROP_UPPER_L = 'X', DOWN_DEFAULT,
		LEFT_R = 'j', RIGHT_R = 'l', ROTATE_CLOCKWISE_R = 'k', ROTATE_COUNTERCLOCKWISE_R = 'i', DROP_R = 'm', ESC = 27
		, LEFT_UPPER_R = 'J', RIGHT_UPPER_R = 'L', ROTATE_CLOCKWISE_UP_R = 'K', ROTATE_COUNTERCLOCKWISE_UP_R = 'I', DROP_UPPER_R = 'M'
	};

	enum class CONVERTED_KEYS { LEFT = 'a', RIGHT = 'b', ROTATE_CLOCKWISE = 'c', ROTATE_COUNTERCLOCKWISE = 'd', DOWN = '0', DROP = 'e' };

	//different shapes in the game
	enum class eShapes { J, O, T, I, S, Z, L,BOMB, COUNT };


};

#endif