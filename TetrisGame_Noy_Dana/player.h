#ifndef PLAYER__H
#define PLAYER__H
#include "gameDef.h"
#include "point.h"
#include <Windows.h>
#include "board.h"
#include "shapes.h"

class Player
{
private:
	const int distance;
	 int middle;
	 Board board;
	 int score;
	 int winner; //1-winner 0-loser

public:

	Player(const int distance, int score, int winner = 1);
	virtual ~Player();
	virtual int handleMove(GameDef::CONVERTED_KEYS updateKey, Shapes& shape, bool& endShape, int& rotate) = 0;
	virtual int findBestMove(bool& endShape, Shapes& shape) = 0;
	virtual void chooseLevel(int player) = 0;
	virtual GameDef::CONVERTED_KEYS convertToDirections(GameDef::eKeys key) const = 0;
	int getDistance() const;
	int getMiddle() const;
	int getScore() const;
	void initScore();
	void setScore(int score) ;
	void displayScore() const;
	void SetWinner(int win) ;
	int GetWinner() const;
	Board& getBoard();

};


#endif // !PLAYER__H
