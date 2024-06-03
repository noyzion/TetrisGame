#ifndef COMPUTER__H
#define COMPUTER__H
#include "Player.h"
#include "shapes.h"
#include "general.h"

class Computer : public Player
{
	int bestGrade;
	Point bestMove[4];
	Point lastBestMove[4];
	int level; // 1= best, 2 = good, 3= novice
	int countMoves;


public:
	enum class Levels{ BEST = 1, GOOD = 2, NOVICE = 3, NOT_VALID };
	Computer(const int distance, int score, int winner = 1, int bestGrade = 0, int level = 1, int countMoves = 0);
	 ~Computer();
	int handleMove(GameDef::CONVERTED_KEYS updateKey, Shapes& shape, bool& endShape, int& rotate);
	int findBestMove(bool& endShape, Shapes& shape);
	GameDef::CONVERTED_KEYS convertToDirections(GameDef::eKeys key) const;
	void chooseLevel(int player);
	int calculateGrade(Shapes& s);
	void setBestMove(Point& p0, Point& p1, Point& p2, Point& p3);
	void setLastBestMove(Point& p0, Point& p1, Point& p2, Point& p3);
	int getMaxBestMovePoint() const;
	Point& getBestMovePoint(int i) { return bestMove[i]; }
	int howMuchWidth(Shapes& s, int maxY);
	int howMuchRows(Shapes& s);
	int howMuchLines(Shapes& s);
	int howMuchShapesInSidesAndWall(Shapes& s, int& wall);

};

#endif