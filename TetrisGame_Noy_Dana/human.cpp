#include "human.h"
#include "general.h"
#include "gameDef.h"
#include <windows.h> // for gotoxy
#include <process.h> // for system
#include <conio.h> // for kbhit+getch
#include <iostream>
using namespace std;

//ctor
Human::Human(const int distance, int score, int winner) : Player(distance, score, winner)
{};

//dtor
Human::	~Human() {};

//Handle left player movement based on a given key
int Human::handleMove( GameDef::CONVERTED_KEYS updateKey, Shapes& shape, bool& endShape, int& rotate)
{
    int speed = GameDef::SPEED;
    if (updateKey == GameDef::CONVERTED_KEYS::DROP)
    {
        speed = 100;
        shape.startShape((*this), GameDef::CONVERTED_KEYS::DOWN, endShape, false);
    }
    else
        shape.startShape((*this), updateKey, endShape, false);
	return speed;
}

//not relevant to human
int Human::findBestMove( bool& endShape, Shapes& shape)
{
    return 0;
}

//not relevant to human
void Human::chooseLevel(int player)
{

}

// Method to convert player input keys to movement directions.
GameDef::CONVERTED_KEYS Human::convertToDirections(GameDef::eKeys key) const
{
	//the movement directions based on the player's position
	// Handle left player's input
	if ((*this).getDistance() == GameDef::MIN_X_LEFT)
	{
		if (key == GameDef::eKeys::LEFT_L || key == GameDef::eKeys::LEFT_UPPER_L)
			return GameDef::CONVERTED_KEYS::LEFT;
		else if (key == GameDef::eKeys::RIGHT_L || key == GameDef::eKeys::RIGHT_UPPER_L)
			return  GameDef::CONVERTED_KEYS::RIGHT;
		else if (key == GameDef::eKeys::ROTATE_CLOCKWISE_L || key == GameDef::eKeys::ROTATE_CLOCKWISE_UP_L)
			return  GameDef::CONVERTED_KEYS::ROTATE_CLOCKWISE;
		else if (key == GameDef::eKeys::ROTATE_COUNTERCLOCKWISE_L || key == GameDef::eKeys::ROTATE_COUNTERCLOCKWISE_UP_L)
			return  GameDef::CONVERTED_KEYS::ROTATE_COUNTERCLOCKWISE;
		else if (key == GameDef::eKeys::DOWN_DEFAULT)
			return GameDef::CONVERTED_KEYS::DOWN;
		else if (key == GameDef::eKeys::DROP_L || key == GameDef::eKeys::DROP_UPPER_L)
			return GameDef::CONVERTED_KEYS::DROP;

	}
	// Handle right player's input
	else if ((*this).getDistance() == GameDef::MIN_X_RIGHT)
	{
		if (key == GameDef::eKeys::LEFT_R || key == GameDef::eKeys::LEFT_UPPER_R)
			return GameDef::CONVERTED_KEYS::LEFT;
		else if (key == GameDef::eKeys::RIGHT_R || key == GameDef::eKeys::RIGHT_UPPER_R)
			return  GameDef::CONVERTED_KEYS::RIGHT;
		else if (key == GameDef::eKeys::ROTATE_CLOCKWISE_R || key == GameDef::eKeys::ROTATE_CLOCKWISE_UP_R)
			return  GameDef::CONVERTED_KEYS::ROTATE_CLOCKWISE;
		else if (key == GameDef::eKeys::ROTATE_COUNTERCLOCKWISE_R || key == GameDef::eKeys::ROTATE_COUNTERCLOCKWISE_UP_R)
			return  GameDef::CONVERTED_KEYS::ROTATE_COUNTERCLOCKWISE;
		else if (key == GameDef::eKeys::DOWN_DEFAULT)
			return GameDef::CONVERTED_KEYS::DOWN;
		else if (key == GameDef::eKeys::DROP_R || key == GameDef::eKeys::DROP_UPPER_R)
			return GameDef::CONVERTED_KEYS::DROP;
	}
	return GameDef::CONVERTED_KEYS::DOWN;

}
