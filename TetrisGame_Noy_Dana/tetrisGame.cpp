#include "tetrisGame.h"
#include <windows.h> // for gotoxy
#include <process.h> // for system
#include <iostream>
#include "general.h"
#include <conio.h> // for kbhit+getch
#include "player.h"
#include "gameDef.h"
#include "shapes.h"
#include "computer.h"
#include "human.h"
#include "menu.h"


using namespace std;


//Initializes the game state for both left and right players.
void TetrisGame::initGame(Player* playerLeft, Player* playerRight) const
{
    (*playerLeft).getBoard().initBoard();
    (*playerRight).getBoard().initBoard();
    (*playerRight).SetWinner(1);
    (*playerLeft).SetWinner(1);
    (*playerRight).setScore(0);
    (*playerLeft).setScore(0);
}

//Runs the main game loop.
void TetrisGame::run(Player* playerLeft, Player* playerRight, bool& continueGame, bool& endGame, bool isColor)
{
    bool gamePaused = false;
    bool endShapeL = true;
    bool endShapeR = true;
    Shapes shapeL;
    Shapes shapeR;
    GameDef::CONVERTED_KEYS updateKeyLeft;
    GameDef::CONVERTED_KEYS updateKeyRight;
    initGame(playerLeft, playerRight);
    initGameDraw(playerLeft, playerRight, continueGame);

    int rotateLeft = 0;
    int rotateRight = 0;

    while (true)
    {
        int speed = GameDef::SPEED;
        int speedTemp = GameDef::SPEED;
        int option = 0;
        int key = 0;
        initNewShapeIfEnd(playerLeft, endShapeL, shapeL, isColor, rotateLeft);
        initNewShapeIfEnd(playerRight, endShapeR, shapeR, isColor, rotateRight);

        if (_kbhit())
        {
            key = _getch();
            if (key == (int)GameDef::eKeys::ESC) //handle pause game
            {
                gamePaused = true;
                option = Menu::menu(gamePaused, endGame);

                if (option == (char)Menu::DEFINES::END_GAME)
                {
                    delete playerLeft;
                    delete playerRight;
                    endGame = true;
                    return;
                }
                else
                {
                    continueGame = true;
                    initGameDraw(playerLeft, playerRight, continueGame);
                }
            }
            if (key == 0)
                key = (int)GameDef::eKeys::DOWN_DEFAULT;

        }

        updateKeyLeft = playerLeft->convertToDirections((GameDef::eKeys)key);
        updateKeyRight = playerRight->convertToDirections((GameDef::eKeys)key);

        if (updateKeyLeft != GameDef::CONVERTED_KEYS::DOWN) //player left
        {
            speed = playerLeft->handleMove(updateKeyLeft, shapeL, endShapeL, rotateLeft);
            if (speed == GameDef::SPEED)
                speedTemp = playerRight->handleMove(GameDef::CONVERTED_KEYS::DOWN, shapeR, endShapeR, rotateRight);
        }
        else if (updateKeyRight != GameDef::CONVERTED_KEYS::DOWN) //player right
        {
            speed = playerRight->handleMove(updateKeyRight, shapeR, endShapeR, rotateRight);
            if (speed == GameDef::SPEED)
                speedTemp = playerLeft->handleMove(GameDef::CONVERTED_KEYS::DOWN, shapeL, endShapeL, rotateLeft);
        }
        else //no key - both down 
        {
            speedTemp = playerLeft->handleMove(GameDef::CONVERTED_KEYS::DOWN, shapeL, endShapeL, rotateLeft);
            speedTemp = playerRight->handleMove(GameDef::CONVERTED_KEYS::DOWN, shapeR, endShapeR, rotateRight);
        }
        Sleep(speed);


        if (theWinner(playerLeft, playerRight))
        {
            gotoxy(GameDef::GAME_WIDTH - 3, GameDef::GAME_HEIGHT + 8);
            cout << "press any key to get back to the menu." << endl;
            _getch();
            break;
        }


    }
}

//Draw the game board on the console.
void TetrisGame::drawBoard(int distance) const
{
    for (int col = distance; col < GameDef::GAME_WIDTH + distance; col++)
    {
        gotoxy(col, GameDef::MIN_Y - 1);
        cout << "-";

        gotoxy(col, GameDef::GAME_HEIGHT + GameDef::MIN_Y);
        cout << "-";
    }

    for (int row = GameDef::MIN_Y - 1; row <= GameDef::GAME_HEIGHT + GameDef::MIN_Y; row++)
    {
        gotoxy(distance - 1, row);
        cout << "|";

        gotoxy(GameDef::GAME_WIDTH + distance, row);
        cout << "|";
    }

}

//Draw the shapes on the player's board based on the current game state used for continue
void TetrisGame::drawShapes(Player& player) const
{
    for (int i = 0; i < GameDef::GAME_HEIGHT + 1; i++)
    {
        for (int j = 0; j < GameDef::GAME_WIDTH + 1; j++)
        {
            if (player.getBoard().getGameBoardValue(i,j) != (int)Board::COLORS::BLACK)
            {
                Point p(j,i);
                p.draw('*', player.getDistance(), player.getBoard().getGameBoardValue(i,j));
            }
        }
    }
}

//Choose and display the winner of the Tetris game.
void TetrisGame::chooseWinner(Player* playerLeft, Player* playerRight) const
{
    if ((*playerLeft).getScore() > (*playerRight).getScore())
    {
        gotoxy(GameDef::GAME_WIDTH + 38, GameDef::GAME_HEIGHT - 10);
        cout << "The winner is: " << endl;
        gotoxy(GameDef::GAME_WIDTH + 38, GameDef::GAME_HEIGHT - 9);
        cout << "the left player!" << endl;
    }
    else if ((*playerLeft).getScore() < (*playerRight).getScore())
    {
        gotoxy(GameDef::GAME_WIDTH + 38, GameDef::GAME_HEIGHT - 10);
        cout << "The winner is: " << endl;
        gotoxy(GameDef::GAME_WIDTH + 38, GameDef::GAME_HEIGHT - 9);
        cout << "the right player!" << endl;
    }
    else
    {
        gotoxy(GameDef::GAME_WIDTH + 38, GameDef::GAME_HEIGHT - 10);
        cout << "Its a tie!" << endl;
    }

}
bool TetrisGame::theWinner(Player* playerLeft, Player* playerRight) const
{
    //annonce winner
    if ((*playerLeft).GetWinner() == 0 && (*playerRight).GetWinner() == 0)
    {
        chooseWinner(playerLeft, playerRight);
        return true;
    }
    else if ((*playerLeft).GetWinner() == 0)
    {
        gotoxy(GameDef::GAME_WIDTH + 38, GameDef::GAME_HEIGHT - 10);
        cout << "The winner is: " << endl;
        gotoxy(GameDef::GAME_WIDTH + 38, GameDef::GAME_HEIGHT - 9);
        cout << "the right player!" << endl;
        return true;
    }
    else if ((*playerRight).GetWinner() == 0)
    {
        gotoxy(GameDef::GAME_WIDTH + 38, GameDef::GAME_HEIGHT - 10);
        cout << "The winner is: " << endl;
        gotoxy(GameDef::GAME_WIDTH + 38, GameDef::GAME_HEIGHT - 9);
        cout << "the left player!" << endl;
        return true;
    }
    else
        return false;
}

//Initialize the game by drawing the initial state of the boards.
void TetrisGame::initGameDraw(Player* playerLeft, Player* playerRight, bool& contniueGame) const
{
    drawBoard((*playerLeft).getDistance());
    drawBoard((*playerRight).getDistance());

    (*playerLeft).displayScore();
    (*playerRight).displayScore();

    if (contniueGame)
    {
        drawShapes((*playerLeft));
        drawShapes((*playerRight));
    }

}

//Initializes a new shape for the player if the current shape has reached its end.
void TetrisGame::initNewShapeIfEnd(Player* player, bool& endShape, Shapes& s, bool isColor, int& rotate)
{
    if (endShape)
    {
        s.init((*player).getMiddle(), (*player).getDistance(), isColor);
        rotate = player->findBestMove(endShape, s);
        endShape = false;
    }
}

