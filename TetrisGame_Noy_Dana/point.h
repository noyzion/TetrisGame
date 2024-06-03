#ifndef POINT__H
#define POINT__H 
#include "gameDef.h"
#include <iostream>

using namespace std;
class Point
{
	int x, y, diff_x, diff_y;

public:
	Point(int x = 0, int y = 0, int diff_x = 0, int diff_y = 0);
	int getY() const;
	int getX() const;
	void setXY(int x, int y);
	void draw(char ch, int distance, int backColor) const;
	void move(GameDef::CONVERTED_KEYS key);
	bool operator!=(const Point& other) const;
};

#endif

