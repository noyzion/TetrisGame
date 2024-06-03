#include "point.h"
#include "gameDef.h"
#include "shapes.h"
#include <Windows.h>
#include "general.h"

// Constructor: Point
Point::Point(int x, int y, int diff_x, int diff_y) : x(x), y(y), diff_x(diff_x), diff_y(diff_y)
{}


// Method to draw the point on the screen at a specified distance.
void Point::draw(char ch, int distance, int backColor) const
{
	if (backColor != 0)
	{
		// Set the background color using bitwise OR with the current text color
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (backColor | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED));
	}

	gotoxy(x + distance - 1, y + GameDef::MIN_Y - 1);
	cout << ch;

	// Reset the text color to the default
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

// Method to move the point based on a specified key.
void Point::move(GameDef::CONVERTED_KEYS key)
{
	switch (key)
	{
	case GameDef::CONVERTED_KEYS::LEFT: //left
		diff_x = -1;
		diff_y = 0;
		break;
	case GameDef::CONVERTED_KEYS::RIGHT: //right
		diff_x = 1;
		diff_y = 0;
		break;
	case GameDef::CONVERTED_KEYS::DOWN: //default down
		diff_x = 0;
		diff_y = 1;
	}

	x += diff_x;
	y += diff_y;	
	diff_x = 0;
	diff_y = 1;
}

// Method to set the coordinates of the point to specified values.
void Point::setXY(int x, int y)
{
	this->x = x;
	this->y = y;
}

int Point::getY() const
{
	return this->y;
}

int Point::getX() const
{
	return this->x;
}

bool Point::operator!=(const Point& other) const
{
	return ((*this).x != other.x || (*this).y != other.y);
}

