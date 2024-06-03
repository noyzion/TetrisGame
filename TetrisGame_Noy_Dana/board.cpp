#include "board.h"


//ctor
Board::Board()
{
	initBoard();
}

// Sets the player's elements in the game board based on their positions.
void Board::setInBoard(Point& p1, Point& p2, Point& p3, Point& p4, int insert)
{
	this->board[p1.getY()][p1.getX()] = insert;
	this->board[p2.getY()][p2.getX()] = insert;
	this->board[p3.getY()][p3.getX()] = insert;
	this->board[p4.getY()][p4.getX()] = insert;
}

// Initializes the player's game board.
void Board::initBoard()
{
	for (int i = 0; i < GameDef::GAME_HEIGHT + 1; i++)
	{
		for (int j = 0; j < GameDef::GAME_WIDTH + 1; j++)
		{
			this->board[i][j] = (int)COLORS::BLACK;
		}
	}
}

// Checks if a row in the player's game board is full.
bool Board::isFullLine(int row) const
{

	for (int j = 1; j < GameDef::GAME_WIDTH + 1; j++)
	{
		if (board[row][j] == (int)COLORS::BLACK)
			return false;
	}
	return true;

}

// Return the value of a specific cell in the player's game board.
int Board::getGameBoardValue(int i, int j) const
{
	return board[i][j];
}

// Moves all elements above a given row down by one row.
void Board::allDown(int row)
{
	int lastRow = findLastRow();
	for (int rowT = row; rowT >= lastRow; rowT--)
	{
		for (int i = 1; i < GameDef::GAME_WIDTH + 1; i++)
		{
			board[rowT][i] = board[rowT - 1][i];
		}
	}
}

//Initializes a specific cell in the player's game board.
void Board::initXYInBoard(int x, int y) 
{
	board[x][y] = (int)COLORS::BLACK;
}

//Sets the value of a specific cell in the player's game board
void Board::setXYInBoard(int x, int y, int insert)
{
	board[x][y] = insert;
}

//Finds the last row in the player's game board that is not full
int Board::findLastRow() const
{
	int i = 0;
	int j = 0;
	bool isFull = false;
	for (; i <= GameDef::GAME_HEIGHT && !isFull; i++)
	{
		j = 0;
		while (board[i][j] == (int)COLORS::BLACK && j < GameDef::GAME_WIDTH)
		{
			j++;
		}
		if (j == GameDef::GAME_WIDTH)
			isFull = false;
		else
			isFull = true;

	}
	return i - 1;
}

//Moves all elements down by a specified distance and updates the game board.
int Board::moveAllDown(int distance, char ch)
{
	int lastRow = findLastRow();
	int i = GameDef::GAME_HEIGHT - 1;

	while (i >= lastRow)
	{
		for (int j = 1; j < GameDef::GAME_WIDTH + 1; j++)
		{
			if (getGameBoardValue(i, j) != (int)COLORS::BLACK && getGameBoardValue(i + 1, j) == (int)COLORS::BLACK)
			{
				int k = i + 1;
				while ((int)COLORS::BLACK == getGameBoardValue(k, j) && k != GameDef::GAME_HEIGHT + 1)
				{
					k++;
				}
				int backColorPrev = getGameBoardValue(i, j);
				setXYInBoard(k - 1, j, backColorPrev);
				initXYInBoard(i, j);
				Point line(j, i);
				line.draw(' ', distance, (int)COLORS::BLACK);
				line.setXY(j, k - 1);
				line.draw(ch, distance, backColorPrev);
			}

		}
		i--;
	}
	return deleteIfBombMadeLine(ch, distance);
}

//Checks if a shape's location is valid on the game board.
bool Board::isValidLocation(Point* shapeCoord) const
{
	//there is shape in my place
	if (getGameBoardValue(shapeCoord[0].getY(), shapeCoord[0].getX()) != (int)COLORS::BLACK)
		return false;
	if (getGameBoardValue(shapeCoord[1].getY(), shapeCoord[1].getX()) != (int)COLORS::BLACK)
		return false;
	if (getGameBoardValue(shapeCoord[2].getY(), shapeCoord[2].getX()) != (int)COLORS::BLACK)
		return false;
	if (getGameBoardValue(shapeCoord[3].getY(), shapeCoord[3].getX()) != (int)COLORS::BLACK)
		return false;
	//bottom
	if (shapeCoord[0].getY() == GameDef::GAME_HEIGHT || shapeCoord[1].getY() == GameDef::GAME_HEIGHT ||
		shapeCoord[2].getY() == GameDef::GAME_HEIGHT || shapeCoord[3].getY() == GameDef::GAME_HEIGHT)
	{
		return true;
	}
	//no shape under me and this is not the end of the board
	else if (getGameBoardValue(shapeCoord[0].getY() + 1, shapeCoord[0].getX()) == (int)COLORS::BLACK && getGameBoardValue(shapeCoord[1].getY() + 1, shapeCoord[1].getX()) == (int)COLORS::BLACK &&
		getGameBoardValue(shapeCoord[2].getY() + 1, shapeCoord[2].getX()) == (int)COLORS::BLACK && getGameBoardValue(shapeCoord[3].getY() + 1, shapeCoord[3].getX()) == (int)COLORS::BLACK)
		return false;

	return true;

}

// Method to check if a rotation is valid.
bool Board::isValidRotation(Point* shapeCoord, bool clockwise) const
{
	Point rotation = shapeCoord[1];
	for (int i = 0; i < 4; i++)
	{
		// Calculate the new position after rotation
		int tempX = shapeCoord[i].getX() - rotation.getX();
		int tempY = shapeCoord[i].getY() - rotation.getY();

		int rotatedX = clockwise ? -tempY : tempY;
		int rotatedY = clockwise ? tempX : -tempX;

		int newX = rotation.getX() + rotatedX;
		int newY = rotation.getY() + rotatedY;

		// Check if the new position is within the game board boundaries
		if (newX < 1 || newX > GameDef::GAME_WIDTH || newY < 1 || newY > GameDef::GAME_HEIGHT)
			return false;

		// Check if the new position collides with existing blocks on the game board
		if (getGameBoardValue(newY, newX) != (int)COLORS::BLACK)
			return false;
	}

	return true;
}

// Method to delete filled lines and move all elements above down.
int Board::deleteLineAndALLDown(Point* shapeCoord, char ch, int distance)
{
	int score = 0;
	for (int j = 3; j >= 0; j--)
	{
		while (isFullLine(shapeCoord[j].getY()))
		{
			int lastRow = findLastRow();
			score += 10;
			allDown(shapeCoord[j].getY());
			for (int row = lastRow; row <= shapeCoord[j].getY(); row++)
			{
				for (int m = 1; m < GameDef::GAME_WIDTH + 1; m++)
				{
					Point line(m, row);
					if (getGameBoardValue(row, m) != (int)COLORS::BLACK)
						line.draw(ch, distance, getGameBoardValue(row, m));
					else
						line.draw(' ', distance, (int)Board::COLORS::BLACK);
				}

			}
		}

	}
	return score;
}

//Deletes lines if a bomb made them and moves elements down.
int Board::deleteIfBombMadeLine(char ch, int distance)
{
	int score = 0;
	int lastRow = findLastRow();
	for (int i = lastRow + 1; i < GameDef::GAME_HEIGHT + 1; i++)
	{
		for (int j = 1; j < GameDef::GAME_WIDTH + 1; j++)
		{
			if (isFullLine(i))
			{
				score += 10;
				allDown(i);
				for (int row = 1; row <= i; row++)
				{
					for (int m = 1; m < GameDef::GAME_WIDTH + 1; m++)
					{
						Point line(m, row);
						if (getGameBoardValue(row, m) != (int)COLORS::BLACK)
							line.draw(ch, distance, getGameBoardValue(row, m));
						else
							line.draw(' ', distance, (int)Board::COLORS::BLACK);
					}

				}
			}
		}
	}
	return score;
}

// Method to check if the shape got to the top of the board.
bool Board::getToTop(Point* shapeCoord) const
{
	int i = 0;
	bool top1 = false;
	bool top2 = false;

	if (shapeCoord[0].getY() == 1|| shapeCoord[1].getY() == 1 || shapeCoord[2].getY() == 1|| shapeCoord[3].getY() ==1)  //Top
		top1 = true;
	if (getGameBoardValue(shapeCoord[0].getY() + 1, shapeCoord[0].getX()) != (int)COLORS::BLACK || getGameBoardValue(shapeCoord[1].getY() + 1, shapeCoord[1].getX()) != (int)COLORS::BLACK
		|| getGameBoardValue(shapeCoord[2].getY() + 1, shapeCoord[2].getX()) != (int)COLORS::BLACK || getGameBoardValue(shapeCoord[3].getY() + 1, shapeCoord[3].getX()) != (int)COLORS::BLACK)
		top2 = true;
	return (top1 && top2);
}

// Method to check if the shape cannot move in a certain direction.
bool Board::cantMove(Point* shapeCoord ,GameDef::CONVERTED_KEYS updateKey, bool& endShape, bool comp) const
{
	if (!comp)
	{
		//Bottom
		if (shapeCoord[0].getY() == GameDef::GAME_HEIGHT || shapeCoord[1].getY() == GameDef::GAME_HEIGHT ||
			shapeCoord[2].getY() == GameDef::GAME_HEIGHT || shapeCoord[3].getY() == GameDef::GAME_HEIGHT)
		{
			endShape = true;
			return true;
		}
		//shape under
		else if (getGameBoardValue(shapeCoord[0].getY() + 1, shapeCoord[0].getX()) != (int)COLORS::BLACK || getGameBoardValue(shapeCoord[1].getY() + 1, shapeCoord[1].getX()) != (int)COLORS::BLACK ||
			getGameBoardValue(shapeCoord[2].getY() + 1, shapeCoord[2].getX()) != (int)COLORS::BLACK || getGameBoardValue(shapeCoord[3].getY() + 1, shapeCoord[3].getX()) != (int)COLORS::BLACK)
		{
			endShape = true;
			return true;
		}
	}
	int i = 0;
	while (i < 4)
	{
		//right wall
		if (shapeCoord[i].getX() + 1 > GameDef::GAME_WIDTH && (updateKey == GameDef::CONVERTED_KEYS::RIGHT))
			return true;
		//left wall
		else if (shapeCoord[i].getX() - 1 < 1 && (updateKey == GameDef::CONVERTED_KEYS::LEFT))
			return true;
		//shape from right
		else if (getGameBoardValue(shapeCoord[i].getY(), shapeCoord[i].getX() + 1) != (int)COLORS::BLACK && (updateKey == GameDef::CONVERTED_KEYS::RIGHT))
			return true;
		//shape from left
		else if (getGameBoardValue(shapeCoord[i].getY(), shapeCoord[i].getX() - 1) != (int)COLORS::BLACK && (updateKey == GameDef::CONVERTED_KEYS::LEFT))
			return true;
		i++;
	}
	return false;
}

//Checks if there is a shape above the current shape
bool Board::isShapeUp(Point* shapeCoord) const
{
	int i = 0;
	while (i < 4)
	{
		//shape from top
		if (getGameBoardValue(shapeCoord[i].getY() - 1, shapeCoord[i].getX()) != (int)COLORS::BLACK)
			return true;
		i++;
	}
	return false;
}
