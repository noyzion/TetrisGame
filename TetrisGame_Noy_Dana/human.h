#ifndef HUMAN__H
#define HUMAN__H
#include "player.h"
#include "shapes.h"

class Human : public Player
{
public:
	Human(const int distance, int score, int winner = 1);
	 ~Human();

	int handleMove(GameDef::CONVERTED_KEYS updateKey, Shapes& shape, bool& endShape, int& rotate);
	int findBestMove(bool& endShape, Shapes& shape);
	void chooseLevel(int player);
	GameDef::CONVERTED_KEYS convertToDirections(GameDef::eKeys key) const;


};

#endif // !
