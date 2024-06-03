#ifndef SHAPES__H
#define SHAPES__H
#include "point.h"
#include "gameDef.h"

class Player;

class Shapes
{
private:
	GameDef::eShapes shapeType;
	const char ch;
	Point shapeCoord[4];
	bool isColor;
	int backColor;


public:

	Shapes(GameDef::eShapes shapeType = GameDef::eShapes::O, char ch = '*', bool isColor = false, int backColor = 0);

	void createRandomShape(int x, bool isColor);
	void startShape( Player& player, GameDef::CONVERTED_KEYS updateKey, bool& endShape,bool isComp);
	void init(int mid, int distance, bool isColor);
	bool moveShape(GameDef::CONVERTED_KEYS updateKey, Player& player);
	void rotateClockWise(int distance);
	void doRotate(int distance);
	void rotateCounterClockWise(int distance);
	void moveDowm( Player& player);
	void explode( Player& player);
	void setPoints(const Point& p1, const Point& p2, const Point& p3, const Point& p4);
	int findMaxY() const;
	int findMinY() const;
	int findMinX() const;
	int findMaxX() const;
	void setNewDownXY();
	void updateXY(int x, int y);
	Point& getPoint(int i);
	Point* getShapeCoord();
	int getBackColor() const;


};

#endif // !SHAPES__H
