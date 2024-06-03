#ifndef  BOARD__H
#define BOARD__H
#include "gameDef.h"
#include "point.h"

class Board
{
	int board[GameDef::GAME_HEIGHT + 1][GameDef::GAME_WIDTH + 1];

public:
	Board();
	enum class COLORS { BLACK = 0 };
	void setInBoard(Point& p1, Point& p2, Point& p3, Point& p4, int insert);
	void initBoard();
	void allDown(int row);
	bool isFullLine(int row) const;
	int getGameBoardValue(int i, int j) const;
	void setXYInBoard(int x, int y, int insert);
	int findLastRow() const;
	bool cantMove(Point* shapeCoord, GameDef::CONVERTED_KEYS updateKey, bool& endShape, bool comp) const;
	bool isValidRotation(Point* shapeCoord, bool clockwise) const;
	bool isValidLocation(Point* shapeCoord) const;
	bool isShapeUp(Point* shapeCoord) const;
	bool getToTop(Point* shapeCoord) const;
	void initXYInBoard(int x, int y);
	int moveAllDown(int distance, char ch);
	int deleteLineAndALLDown(Point* shapeCoord, char ch, int distance);
	int deleteIfBombMadeLine(char ch, int distance);

};
#endif // ! BOARD__H
