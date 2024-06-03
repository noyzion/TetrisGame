#ifndef TETRIS__GAME__H
#define TETRIS__GAME__H
#include "gameDef.h"
#include "player.h"
#include "shapes.h"

class TetrisGame
{
   
public:

	void run(Player* playerLeft, Player* playerRight, bool& continueGame, bool& endGame, bool isColor);
	void initGame(Player* playerLeft, Player* playerRight) const;
	void drawBoard(int distance) const;
	void drawShapes( Player& player) const;
	void initGameDraw(Player* playerLeft, Player* playerRight, bool& contniueGame) const;
	bool theWinner(Player* playerLeft, Player* playerRight) const;
	void chooseWinner(Player* playerLeft, Player* playerRight) const;
	void initNewShapeIfEnd(Player* player, bool& endShape, Shapes& s, bool isColor, int& rotate);

};




#endif