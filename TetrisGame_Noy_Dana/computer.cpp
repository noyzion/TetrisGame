#include "computer.h"
#include <windows.h> // for gotoxy
#include <process.h> // for system
#include <conio.h> // for kbhit+getch

//ctor
Computer::Computer(const int distance, int score, int winner, int bestGrade, int level, int countMoves) : Player(distance, score, winner), bestGrade(bestGrade), level(level), countMoves(countMoves)
{
	// Initialize each Point in shapeCoord
	this->bestMove[0] = 0;
	this->bestMove[1] = 0;
	this->bestMove[2] = 0;
	this->bestMove[3] = 0;
};

//dtor
Computer::~Computer() {};

//Sets the best move for the computer player based on four provided points.
void Computer::setBestMove(Point& p0, Point& p1, Point& p2, Point& p3)
{
	bestMove[0] = p0;
	bestMove[1] = p1;
	bestMove[2] = p2;
	bestMove[3] = p3;
}

//Sets the last best move for the computer player based on four provided points.
void Computer::setLastBestMove(Point& p0, Point& p1, Point& p2, Point& p3)
{
    lastBestMove[0] = p0;
    lastBestMove[1] = p1;
    lastBestMove[2] = p2;
    lastBestMove[3] = p3;
}

//Returns the maximum X-coordinate among the best move points.
int Computer::getMaxBestMovePoint() const
{

	int maxX = bestMove[0].getX();
	for (int i = 1; i < 4; i++)
	{
		if (bestMove[i].getX() > maxX)
			maxX = bestMove[i].getX();
	}
	return maxX;
}

//Handles the computer player's move based on the best move points, including rotation and lateral movement.
int Computer::handleMove(GameDef::CONVERTED_KEYS updateKey, Shapes& shape, bool& endShape, int& rotate)
{
    if ((*this).getBestMovePoint(0) != shape.getPoint(0) || (*this).getBestMovePoint(1) != shape.getPoint(1) ||
        (*this).getBestMovePoint(2) != shape.getPoint(2) || (*this).getBestMovePoint(3) != shape.getPoint(3))
    {
        if (rotate > 0)
        {
            if (!getBoard().isValidRotation(shape.getShapeCoord(), true))
            {
                shape.startShape((*this),GameDef::CONVERTED_KEYS::DOWN, endShape, true);
                return GameDef::SPEED;

            }
            shape.startShape((*this),GameDef::CONVERTED_KEYS::ROTATE_CLOCKWISE, endShape, true);
            rotate--;
            return GameDef::SPEED;
        }

        bool moveRight = false;
        bool moveLeft = false;
        int maxX = shape.findMaxX();

        if (maxX < getMaxBestMovePoint())
        {
            moveRight = true;
        }
        else if (maxX > getMaxBestMovePoint())
        {
            moveLeft = true;
        }


        // Move the shape left or right based on the destination column
        if (moveRight)
        {
            // Move right
            shape.startShape((*this), GameDef::CONVERTED_KEYS::RIGHT, endShape, true);
        }
        else if (moveLeft)
        {
            // Move left
            shape.startShape((*this), GameDef::CONVERTED_KEYS::LEFT, endShape, true);
        }
        else
            shape.startShape((*this), GameDef::CONVERTED_KEYS::DOWN, endShape, true);
    }
    else
        shape.startShape((*this), GameDef::CONVERTED_KEYS::DOWN, endShape, true);
    return GameDef::SPEED;
}

//Finds the best move for the computer player based on different rotations and lateral movements.
//Evaluates the quality of moves using a grading system.
int Computer::findBestMove(bool& endShape, Shapes& shape)
{
    countMoves++;
    bestGrade = -1000;
    bool comp = true;
    int i = GameDef::GAME_HEIGHT;
    int tempBestGrade = 0, tempRotation = 0, tempGrade =0, howMuchRotateBest = 0,maxX=0;
    Point p0 = shape.getPoint(0), p1 = shape.getPoint(1),p2 = shape.getPoint(2), p3 = shape.getPoint(3);
    Point* shapeCoord = shape.getShapeCoord();
    int lastRow = getBoard().findLastRow();

    for (int rotation = 0; rotation < 4; rotation++)
    {
        i = GameDef::GAME_HEIGHT;
        shape.setNewDownXY();
        int j = 0;
        while (i >= lastRow)
        {
            while (!getBoard().cantMove(shapeCoord, GameDef::CONVERTED_KEYS::RIGHT, endShape, comp) || maxX != GameDef::GAME_WIDTH + 1)
            {

                if (getBoard().isValidLocation(shapeCoord) && !(getBoard().isShapeUp(shapeCoord)))
                {
                    tempBestGrade = calculateGrade(shape);
                    if (tempBestGrade > bestGrade)
                    {
                        bestGrade = tempBestGrade;
                        setBestMove(shape.getPoint(0), shape.getPoint(1), shape.getPoint(2), shape.getPoint(3));
                        howMuchRotateBest = rotation;
                    }
                    else if (tempBestGrade < bestGrade)
                    {
                        tempGrade = tempBestGrade;
                        tempRotation = howMuchRotateBest;
                        setLastBestMove(shape.getPoint(0), shape.getPoint(1), shape.getPoint(2), shape.getPoint(3));
                    }
                }
                shape.updateXY(1, 0);
                maxX = shape.findMaxX();
            }
            i--;
            int xMin = shape.findMinX();
            shape.updateXY(-xMin + 1, 1);
            maxX = shape.findMaxX();

        }
        int yMax = shape.findMaxY();
        shape.updateXY(1, 18 - yMax);
        shape.doRotate((*this).getDistance());

    }
    if ((countMoves == 10 && level == 3) || (countMoves == 40 && level == 2))
    {
        countMoves = 0;
        bestGrade = tempGrade;
        setBestMove(lastBestMove[0], lastBestMove[1], lastBestMove[2], lastBestMove[3]);
        howMuchRotateBest = tempRotation;
    }

    shape.setPoints(p0, p1, p2, p3);
    return howMuchRotateBest;
}

//Calculates the grade for a given shape
//based on various criteria such as the number of lines cleared, shape height, width, and more.
int Computer::calculateGrade(Shapes& s) 
{
    int lines = 0;
    int maxY = s.findMaxY();
    int count = 0;
    int grade = 0;
    int shapesInSides = 0;
    int wall = 0;
    int holesAfter = 0;

    count = howMuchWidth(s, maxY);

    if (s.getBackColor() == (int)Board::COLORS::BLACK)
        getBoard().setInBoard(s.getPoint(0), s.getPoint(1), s.getPoint(2), s.getPoint(3), 1);
    else
        getBoard().setInBoard(s.getPoint(0), s.getPoint(1), s.getPoint(2), s.getPoint(3), s.getBackColor());

    shapesInSides = howMuchShapesInSidesAndWall(s, wall);
    holesAfter = howMuchRows(s);
    lines = howMuchLines(s);

    getBoard().initXYInBoard(s.getPoint(0).getY(), s.getPoint(0).getX());
    getBoard().initXYInBoard(s.getPoint(1).getY(), s.getPoint(1).getX());
    getBoard().initXYInBoard(s.getPoint(2).getY(), s.getPoint(2).getX());
    getBoard().initXYInBoard(s.getPoint(3).getY(), s.getPoint(3).getX());

    grade = lines * 2500 + maxY * 40 + count * 25 + shapesInSides * 30 + wall * 10 - holesAfter * 300;
    return grade;
}

//Allows the player to choose the computer's level (BEST, GOOD, or NOVICE)
void Computer::chooseLevel(int player)
{
    level = (int)Levels::NOT_VALID;
    while (level == (int)Levels::NOT_VALID)
    {
        clrscr();
        gotoxy(GameDef::GAME_WIDTH + 15, GameDef::GAME_HEIGHT - 12);
        cout << "(1) Best" << endl;
        gotoxy(GameDef::GAME_WIDTH + 15, GameDef::GAME_HEIGHT - 11);
        cout << "(2) Good" << endl;
        gotoxy(GameDef::GAME_WIDTH + 15, GameDef::GAME_HEIGHT - 10);
        cout << "(3) Novice" << endl;
        gotoxy(GameDef::GAME_WIDTH + 15, GameDef::GAME_HEIGHT - 9);
        cout << "choose ";
        if (player == 1)
            cout << "left ";
        else
            cout << "right ";
        cout << "computer level: " << endl;
        gotoxy(GameDef::GAME_WIDTH + 43, GameDef::GAME_HEIGHT - 9);
        cin >> level;
        if(level != (int)Levels::BEST && level != (int)Levels::GOOD && level != (int)Levels::NOVICE)
            level = (int)Levels::NOT_VALID;
    }
}

//Converts input keys to converted keys specific - not relevant for computer
GameDef::CONVERTED_KEYS Computer::convertToDirections(GameDef::eKeys key) const
{
    return GameDef::CONVERTED_KEYS::DOWN;
}

//Determines the number of blocks at the maximum Y-coordinate for a given shape.
int Computer::howMuchWidth(Shapes& s, int maxY)
{
    int count = 0;
    for (int i = 0; i < 4; i++)
    {
        if (s.getPoint(i).getY() == maxY)
            count++;
    }
    return count; 
}

//Calculates the number of empty points below each block of a given shape.
int Computer::howMuchRows(Shapes& s)
{
    int holesAfter = 0;
    for (int i = 0; i < 4; i++)
    {
        int x = s.getPoint(i).getX();
        int y = s.getPoint(i).getY();

        // Check each row below the shape's block
        for (int j = y + 1; j < GameDef::GAME_HEIGHT + 1 && getBoard().getGameBoardValue(j, x) == (int)Board::COLORS::BLACK; j++)
        {

            holesAfter++;

        }
    }
    return holesAfter;
}

//Determines the number of filled lines that would be cleared by placing a shape on the board.
int Computer::howMuchLines(Shapes& s)
{
    int lines = 0;
    if (getBoard().isFullLine(s.getPoint(0).getY()))
        lines++;
    if (getBoard().isFullLine(s.getPoint(1).getY()) && s.getPoint(1).getY() != s.getPoint(0).getY())
        lines++;
    if (getBoard().isFullLine(s.getPoint(2).getY()) && s.getPoint(1).getY() != s.getPoint(2).getY() && s.getPoint(0).getY() != s.getPoint(2).getY())
        lines++;
    if (getBoard().isFullLine(s.getPoint(3).getY()) && s.getPoint(1).getY() != s.getPoint(3).getY() && s.getPoint(0).getY() != s.getPoint(3).getY() && s.getPoint(2).getY() != s.getPoint(3).getY())
        lines++;
    return lines;
}

//Determines the number of points that is next to another shape
// and counts the number of points that is next to left and right walls.
int Computer::howMuchShapesInSidesAndWall(Shapes& s, int& wall)
{
    int minX = s.findMinX();
    int maxX = s.findMaxX();
    int shapesInSides = 0;
    int i = 0;
    if (s.getPoint(0).getX() < GameDef::GAME_WIDTH
        && s.getPoint(1).getX() < GameDef::GAME_WIDTH
        && s.getPoint(2).getX() < GameDef::GAME_WIDTH
        && s.getPoint(3).getX() < GameDef::GAME_WIDTH)
    {
        while (i < 4)
        {
            if (s.getPoint(i).getX() == maxX)
            {
                if (getBoard().getGameBoardValue(s.getPoint(i).getY(), maxX + 1) != (int)Board::COLORS::BLACK)
                    shapesInSides++;
            }

            i++;
        }
    }
    else
    {
        while (i < 4)
        {
            if (s.getPoint(i).getX() == minX)
            {
                wall++;
            }
            i++;

        }
    }

    i = 0;
    if (s.getPoint(0).getX() > 1 && s.getPoint(1).getX() > 1 && s.getPoint(2).getX() > 1 && s.getPoint(3).getX() > 1)
    {
        while (i < 4)
        {
            if (s.getPoint(i).getX() == minX)
            {
                if (getBoard().getGameBoardValue(s.getPoint(i).getY(), minX - 1) != (int)Board::COLORS::BLACK)
                    shapesInSides++;
            }
            i++;

        }
    }
    else
    {
        while (i < 4)
        {
            if (s.getPoint(i).getX() == minX)
            {
                wall++;
            }
            i++;

        }
    }
    return shapesInSides;
}

