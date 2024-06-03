#include "shapes.h"
#include "player.h"
#include <conio.h> // for kbhit+getch
#include <Windows.h> // for Sleep and colors
#include <cstdlib> //for random
#include <iostream>
#include "gameDef.h"
#include "board.h"


using namespace std;

// Constructor: Shapes
Shapes::Shapes(GameDef::eShapes shapeType, char ch, bool isColor, int backColor)
: shapeType(shapeType), ch(ch) ,isColor(isColor), backColor(backColor)
{
	// Initialize each Point in shapeCoord
	this->shapeCoord[0]=0;
	this->shapeCoord[1]=0;
	this->shapeCoord[2]=0;
	this->shapeCoord[3]=0;
}

// Method to create a random shape at a given x-coordinate.
void Shapes::createRandomShape(int x, bool isColor)
{
	int randomValue = rand() % 20;
	if (randomValue < 1) // 5% probability for the bomb shape
	{
		this->shapeCoord[0].setXY(x, 1);
		this->shapeCoord[1].setXY(x, 1);
		this->shapeCoord[2].setXY(x, 1);
		this->shapeCoord[3].setXY(x, 1);
		this->shapeType = GameDef::eShapes::BOMB;
		if (isColor)
			this->backColor = BACKGROUND_RED;
	}
	else // 95% probability for other shapes
	{
		GameDef::eShapes randomShape = GameDef::eShapes(rand() % (int)GameDef::eShapes::COUNT);
		switch (randomShape)
		{
		case GameDef::eShapes::L:
			this->shapeCoord[0].setXY(x, 1);
			this->shapeCoord[1].setXY(x, 2);
			this->shapeCoord[2].setXY(x, 3);
			this->shapeCoord[3].setXY(x + 1, 3);
			this->shapeType = GameDef::eShapes::L;
			if (isColor)
				this->backColor = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
			break;
		case GameDef::eShapes::J:
			this->shapeCoord[0].setXY(x + 1, 1);
			this->shapeCoord[1].setXY(x + 1, 2);
			this->shapeCoord[2].setXY(x + 1, 3);
			this->shapeCoord[3].setXY(x, 3);
			this->shapeType = GameDef::eShapes::J;
			if (isColor)
				this->backColor = BACKGROUND_BLUE;
			break;
		case GameDef::eShapes::T:
			this->shapeCoord[0].setXY(x, 1);
			this->shapeCoord[1].setXY(x + 1, 1);
			this->shapeCoord[2].setXY(x + 2, 1);
			this->shapeCoord[3].setXY(x + 1, 2);
			this->shapeType = GameDef::eShapes::T;
			if (isColor)
				this->backColor = BACKGROUND_RED | BACKGROUND_BLUE;
			break;
		case GameDef::eShapes::S:
			this->shapeCoord[0].setXY(x + 2, 1);
			this->shapeCoord[1].setXY(x + 1, 1);
			this->shapeCoord[2].setXY(x + 1, 2);
			this->shapeCoord[3].setXY(x, 2);
			this->shapeType = GameDef::eShapes::S;
			if (isColor)
				this->backColor = BACKGROUND_GREEN;

			break;
		case GameDef::eShapes::Z:
			this->shapeCoord[0].setXY(x, 1);
			this->shapeCoord[1].setXY(x + 1, 1);
			this->shapeCoord[2].setXY(x + 1, 2);
			this->shapeCoord[3].setXY(x + 2, 2);
			this->shapeType = GameDef::eShapes::Z;
			if (isColor)
				this->backColor = BACKGROUND_RED;
			break;
		case GameDef::eShapes::I:
			this->shapeCoord[0].setXY(x, 1);
			this->shapeCoord[1].setXY(x + 1, 1);
			this->shapeCoord[2].setXY(x + 2, 1);
			this->shapeCoord[3].setXY(x + 3, 1);
			this->shapeType = GameDef::eShapes::I;
			if (isColor)
				this->backColor = BACKGROUND_BLUE | BACKGROUND_GREEN;
			break;
		case GameDef::eShapes::O:
			this->shapeCoord[0].setXY(x, 1);
			this->shapeCoord[1].setXY(x + 1, 1);
			this->shapeCoord[2].setXY(x, 2);
			this->shapeCoord[3].setXY(x + 1, 2);
			this->shapeType = GameDef::eShapes::O;
			if (isColor)
				this->backColor = BACKGROUND_GREEN | BACKGROUND_RED;
			break;
		case GameDef::eShapes::BOMB:
			this->shapeCoord[0].setXY(x, 1);
			this->shapeCoord[1].setXY(x, 1);
			this->shapeCoord[2].setXY(x, 1);
			this->shapeCoord[3].setXY(x, 1);
			this->shapeType = GameDef::eShapes::BOMB;
			if (isColor)
				this->backColor = BACKGROUND_RED;
			break;
		}
	}
}

// Method to initialize the shape at the specified middle and distance.
void Shapes::init(int mid, int distance, bool isColor)
{
	this->isColor = isColor;
	int x = mid - distance;
	createRandomShape(x, isColor);
	for (int i = 0; i < 4; i++)
		shapeCoord[i].draw(ch, distance, this->backColor);
}

// Method to start the movement of the shape based on player input.
void Shapes::startShape( Player& player, GameDef::CONVERTED_KEYS updateKey, bool& endShape, bool isComp)
{
	endShape = moveShape(updateKey, player);
}

// Move the shape based on the player's input and update its position on the game board.
bool Shapes::moveShape(GameDef::CONVERTED_KEYS updateKey,  Player& player)
{
	bool endBoard = false;

	// Check if the shape has reached the top of the board 
	if (player.getBoard().getToTop(shapeCoord)) //end game
	{
		player.SetWinner(0); // Player loses when the shape reaches the top
		return true;
	}
	// Check if the shape cannot move or if it has reached the end of the board
	if (player.getBoard().cantMove(shapeCoord, updateKey, endBoard,false) || endBoard)
	{
		if (!endBoard)
			moveDowm(player);
		else
		{
			if (shapeType == GameDef::eShapes::BOMB)
			{
				explode(player);
			}
			else
			{
				// Set the shape on the game board and check if there is completed lines
				if(!isColor)
					player.getBoard().setInBoard(shapeCoord[0], shapeCoord[1], shapeCoord[2], shapeCoord[3], 1);
				else
					player.getBoard().setInBoard(shapeCoord[0], shapeCoord[1], shapeCoord[2], shapeCoord[3], backColor);
				player.setScore(player.getBoard().deleteLineAndALLDown(shapeCoord, ch, player.getDistance()));
			}
			return true; //end of shape
		}
	}
	else
	{
		// Handle rotation based on input
		// Move the shape down after rotation if possible
		if (updateKey == GameDef::CONVERTED_KEYS::ROTATE_CLOCKWISE 
			&& this->shapeType != GameDef::eShapes::O && player.getBoard().isValidRotation(shapeCoord, true))
		{
			rotateClockWise(player.getDistance());
			if (!player.getBoard().cantMove(shapeCoord, GameDef::CONVERTED_KEYS::DOWN, endBoard, false))
				moveDowm(player);
		}
		else if (updateKey == GameDef::CONVERTED_KEYS::ROTATE_COUNTERCLOCKWISE
			&& this->shapeType != GameDef::eShapes::O && player.getBoard().isValidRotation(shapeCoord, false))
		{
			rotateCounterClockWise(player.getDistance());
			if (!player.getBoard().cantMove(shapeCoord, GameDef::CONVERTED_KEYS::DOWN, endBoard, false))
				moveDowm(player);
		}

		else //move left, right or down 
		{
			
			for (int i = 0; i < 4; i++)
				shapeCoord[i].draw(' ',player.getDistance(), (int)Board::COLORS::BLACK);
			for (int i = 0; i < 4; i++)
			{
				shapeCoord[i].move(updateKey);
				shapeCoord[i].draw(ch, player.getDistance(),backColor);
			}
			if ((updateKey == GameDef::CONVERTED_KEYS::LEFT || updateKey == GameDef::CONVERTED_KEYS::RIGHT)
				&& !player.getBoard().cantMove(shapeCoord, GameDef::CONVERTED_KEYS::DOWN,endBoard, false))
				moveDowm(player);
		}
	}
	return false; // Shape is still active
}

// Method to rotate the shape clockwise around its center.
void Shapes::rotateClockWise(int distance)
{
	for (int i = 0; i < 4; i++)
		shapeCoord[i].draw(' ', distance, (int)Board::COLORS::BLACK);

	Point rotation = shapeCoord[1];
	int tempX, tempY, rotatedX, rotatedY;
	for (int i = 0; i < 4; i++)
	{
		tempX = shapeCoord[i].getX() - rotation.getX();
		tempY = shapeCoord[i].getY() - rotation.getY();

		rotatedX = -tempY;
		rotatedY = tempX;

		shapeCoord[i].setXY(rotation.getX() + rotatedX, rotation.getY() + rotatedY);
		shapeCoord[i].draw(ch, distance, backColor);
	}
}

//Calculates the new coordinates after rotation and sets them.
void Shapes::doRotate(int distance)
{
	Point rotation = shapeCoord[1];
	int tempX, tempY, rotatedX, rotatedY;
	for (int i = 0; i < 4; i++)
	{
		tempX = shapeCoord[i].getX() - rotation.getX();
		tempY = shapeCoord[i].getY() - rotation.getY();

		rotatedX = -tempY;
		rotatedY = tempX;

		shapeCoord[i].setXY(rotation.getX() + rotatedX, rotation.getY() + rotatedY);
	}
}

// Method to rotate the shape counterclockwise around its center.
void Shapes::rotateCounterClockWise(int distance)
{
	Point rotation = shapeCoord[1];
	int tempX, tempY, rotatedX, rotatedY;

	for (int i = 0; i < 4; i++)
		shapeCoord[i].draw(' ', distance, (int)Board::COLORS::BLACK);

	for (int i = 0; i < 4; i++)
	{
		tempX = shapeCoord[i].getX() - rotation.getX();
		tempY = shapeCoord[i].getY() - rotation.getY();

		rotatedX = tempY;
		rotatedY = -tempX;

		shapeCoord[i].setXY(rotation.getX() + rotatedX, rotation.getY() + rotatedY);
		shapeCoord[i].draw(ch,distance,backColor);
	}
}

// Method to move the shape down and update its position on the screen.
void Shapes::moveDowm( Player& player)
{
	for (int i = 0; i < 4; i++)
		shapeCoord[i].draw(' ',player.getDistance(), (int)Board::COLORS::BLACK);
	for (int i = 0; i < 4; i++)
	{
		shapeCoord[i].move(GameDef::CONVERTED_KEYS::DOWN);
		shapeCoord[i].draw(ch,player.getDistance(),backColor);
	}
}

//Handles the explosion of a bomb shape.
//Clears the surrounding areaand sets the score based on the lines removed.
void Shapes::explode( Player& player)
{
	for (int row = shapeCoord[0].getY() + 4; row >= shapeCoord[0].getY() - 4; row--)
	{
		for (int i = shapeCoord[0].getX() - 4; i <= shapeCoord[0].getX() + 4; i++)
		{
			if (i <= GameDef::GAME_WIDTH && i > 0 && row <= GameDef::GAME_HEIGHT && row > 0)   //if not end board
			{
				player.getBoard().initXYInBoard(row, i);
				Point line(i, row);
				line.draw(' ', player.getDistance(), (int)Board::COLORS::BLACK);
			}
		}
	}
	player.setScore(player.getBoard().moveAllDown(player.getDistance(), ch));

}

//Sets the coordinates of the shape points based on the provided points.
void Shapes::setPoints(const Point& p1,const Point& p2, const Point& p3, const Point& p4)
{
	this->shapeCoord[0].setXY(p1.getX(), p1.getY());
	this->shapeCoord[1].setXY(p2.getX(), p2.getY());
	this->shapeCoord[2].setXY(p3.getX(), p3.getY());
	this->shapeCoord[3].setXY(p4.getX(), p4.getY());
}

//Helper methods to find the maximumand minimum Xand Y coordinates of the shape.
int Shapes::findMaxY() const
{
	int maxY = shapeCoord[0].getY();

	for (int i = 1; i < 4; i++)
	{
		if (shapeCoord[i].getY() > maxY)
			maxY = shapeCoord[i].getY();
	}
	return maxY;
}
int Shapes::findMinY() const
{
	int minY = shapeCoord[0].getY();

	for (int i = 1; i < 4; i++)
	{
		if (shapeCoord[i].getY() < minY)
			minY = shapeCoord[i].getY();
	}
	return minY;
}
int Shapes::findMinX() const
{
	int minX = shapeCoord[0].getX();

	for (int i = 1; i < 4; i++)
	{
		if (shapeCoord[i].getX() < minX)
			minX = shapeCoord[i].getX();
	}
	return minX;
}
int Shapes::findMaxX() const
{
	int maxX = shapeCoord[0].getX();

	for (int i = 1; i < 4; i++)
	{
		if (shapeCoord[i].getX() > maxX)
			maxX = shapeCoord[i].getX();
	}
	return maxX;
}

//Sets new coordinates to move the shape down and left based on the current position.
void Shapes::setNewDownXY() 
{
	int yMax = findMaxY();
	int xMin = findMinX();

	Point newPoint0 = shapeCoord[0];
	newPoint0.setXY(newPoint0.getX() - xMin +1, newPoint0.getY() + 18 - yMax);

	Point newPoint1 = shapeCoord[1];
	newPoint1.setXY(newPoint1.getX() - xMin + 1, newPoint1.getY() + 18 - yMax);

	Point newPoint2 = shapeCoord[2];
	newPoint2.setXY(newPoint2.getX() - xMin + 1, newPoint2.getY() + 18 - yMax);

	Point newPoint3 = shapeCoord[3];
	newPoint3.setXY(newPoint3.getX() - xMin + 1, newPoint3.getY() + 18 - yMax);

	setPoints(newPoint0, newPoint1, newPoint2, newPoint3);

}

//Updates the coordinates of the shape based on the provided x and y values.
void Shapes::updateXY(int x, int y)
{

	Point newPoint0 = shapeCoord[0];
	newPoint0.setXY(newPoint0.getX() + x, newPoint0.getY() - y);

	Point newPoint1 = shapeCoord[1];
	newPoint1.setXY(newPoint1.getX() + x, newPoint1.getY() - y);

	Point newPoint2 = shapeCoord[2];
	newPoint2.setXY(newPoint2.getX() + x, newPoint2.getY() - y);

	Point newPoint3 = shapeCoord[3];
	newPoint3.setXY(newPoint3.getX() + x, newPoint3.getY() - y);

	setPoints(newPoint0, newPoint1, newPoint2, newPoint3);
}

Point& Shapes::getPoint(int i)  
{
	return shapeCoord[i];
}

Point* Shapes::getShapeCoord()
{
	return shapeCoord;
}

int Shapes::getBackColor() const
{
	return backColor;
}