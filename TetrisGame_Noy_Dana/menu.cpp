#include "menu.h"
#include "player.h"
#include "shapes.h"
#include "human.h"
#include "computer.h"
#include <stdio.h>
#include <windows.h> // for gotoxy
#include <process.h> // for system
#include <conio.h> // for kbhit+getch
#include "tetrisGame.h"

using namespace std;

//Handle the game status based on the selected option.
char Menu::gameStatus(bool& paused, bool& continueGame, bool& endGame, char option)
{
    TetrisGame game;

    Player* playerLeft;
    Player* playerRight;
    bool isColor;
    switch (option)
    {
    case (char)DEFINES::START_GAME_HH:
        playerLeft = new Human(GameDef::MIN_X_LEFT, 0);
        playerRight = new Human(GameDef::MIN_X_RIGHT, 0);
        continueGame = false;
        paused = false;
        isColor = chooseColors();
        startGameAnnouncement();
        game.run(playerLeft, playerRight, continueGame, endGame, isColor);
        return (char)DEFINES::START_GAME;
    case (char)DEFINES::START_GAME_CC:
        playerLeft = new Computer(GameDef::MIN_X_LEFT, 0);
        playerRight = new Computer(GameDef::MIN_X_RIGHT, 0);
        playerLeft->chooseLevel(1);
        playerRight->chooseLevel(2);
        continueGame = false;
        paused = false;
        isColor = chooseColors();
        startGameAnnouncement();
        game.run(playerLeft, playerRight, continueGame, endGame, isColor);
        return (char)DEFINES::START_GAME;
    case (char)DEFINES::START_GAME_HC:
        playerLeft = new Human(GameDef::MIN_X_LEFT, 0);
        playerRight = new Computer(GameDef::MIN_X_RIGHT, 0);
        playerRight->chooseLevel(2);
        continueGame = false;
        paused = false;
        isColor = chooseColors();
        startGameAnnouncement();
        game.run(playerLeft, playerRight, continueGame, endGame, isColor);
        return (char)DEFINES::START_GAME;
    case (char)DEFINES::CONTINUE:
        if (!paused)
        {
            gotoxy(GameDef::GAME_WIDTH + 10, GameDef::GAME_HEIGHT + 3);
            cout << "Invalid choice. Please press a key from the menu." << endl;
            return (char)DEFINES::NOT_VALID;
        }
        else
        {
            clrscr();
            continueGame = true;
            paused = false;
            break;
        }
    case (char)DEFINES::INSTRUCTIONS:
        instructions();
        return (char)DEFINES::INSTRUCTIONS;
    case (char)DEFINES::END_GAME:
        endGame = true;
        continueGame = false;
        paused = false;
        clrscr();
        gotoxy(GameDef::GAME_WIDTH + 10, GameDef::GAME_HEIGHT - 10);
        cout << "Exiting Tetris. Goodbye!" << endl;
        break;
    default:
        gotoxy(GameDef::GAME_WIDTH + 10, GameDef::GAME_HEIGHT + 3);
        cout << "Invalid choice. Please press a key from the menu." << endl;
        return (char)DEFINES::NOT_VALID;
    }
    return option;

}

//Display the main menu and handle user input.
char Menu::menu(bool& gamePaused, bool& exitGame)
{
    char option = 0;
    bool continueGame = false;

    while (!exitGame)
    {
        if (!gamePaused)
        {
            clrscr();
            openMessage();
            gotoxy(GameDef::GAME_WIDTH + 10, GameDef::GAME_HEIGHT + 2);
            cout << "Please press your choice:" << endl;
            gotoxy(GameDef::GAME_WIDTH + 36, GameDef::GAME_HEIGHT + 2);
            cin >> option;
            option = gameStatus(gamePaused, continueGame, exitGame, option);
            while (option == (char)DEFINES::NOT_VALID)
            {
                gotoxy(GameDef::GAME_WIDTH + 60, GameDef::GAME_HEIGHT + 3);
                cin >> option;
                option = gameStatus(gamePaused, continueGame, exitGame, option);
            }
        }
        else
        {
            clrscr();
            openMessagePause();
            gotoxy(GameDef::GAME_WIDTH + 10, GameDef::GAME_HEIGHT + 3);
            cout << "Please press your choice:" << endl;
            gotoxy(GameDef::GAME_WIDTH + 36, GameDef::GAME_HEIGHT + 3);
            cin >> option;
            option = gameStatus(gamePaused, continueGame, exitGame, option);
            while (option == (char)DEFINES::NOT_VALID)
            {
                gotoxy(GameDef::GAME_WIDTH + 60, GameDef::GAME_HEIGHT + 4);
                cin >> option;
                option = gameStatus(gamePaused, continueGame, exitGame, option);

            }
            if (exitGame)
                return (char)DEFINES::END_GAME;
            if (continueGame)
                return 0;
        }
        if (option == (char)DEFINES::END_GAME)
        {
            exitGame = true;

        }

    }
    return option;
}

//Display a countdown announcement before starting the game.
void Menu::startGameAnnouncement() 
{
    clrscr();

    gotoxy(GameDef::GAME_WIDTH + 15, GameDef::GAME_HEIGHT - 10);
    cout << "  33333  \n";
    gotoxy(GameDef::GAME_WIDTH + 15, GameDef::GAME_HEIGHT - 9);
    cout << "      33  \n";
    gotoxy(GameDef::GAME_WIDTH + 15, GameDef::GAME_HEIGHT - 8);
    cout << "     33   \n";
    gotoxy(GameDef::GAME_WIDTH + 15, GameDef::GAME_HEIGHT - 7);
    cout << "   333    \n";
    gotoxy(GameDef::GAME_WIDTH + 15, GameDef::GAME_HEIGHT - 6);
    cout << "     33   \n";
    gotoxy(GameDef::GAME_WIDTH + 15, GameDef::GAME_HEIGHT - 5);
    cout << "      33  \n";
    gotoxy(GameDef::GAME_WIDTH + 15, GameDef::GAME_HEIGHT - 4);
    cout << "  33333   \n";
    Sleep(700);

    clrscr();

    gotoxy(GameDef::GAME_WIDTH + 15, GameDef::GAME_HEIGHT - 10);
    cout << "  22222  \n";
    gotoxy(GameDef::GAME_WIDTH + 15, GameDef::GAME_HEIGHT - 9);
    cout << "     22  \n";
    gotoxy(GameDef::GAME_WIDTH + 15, GameDef::GAME_HEIGHT - 8);
    cout << "    22   \n";
    gotoxy(GameDef::GAME_WIDTH + 15, GameDef::GAME_HEIGHT - 7);
    cout << "   22    \n";
    gotoxy(GameDef::GAME_WIDTH + 15, GameDef::GAME_HEIGHT - 6);
    cout << "  22     \n";
    gotoxy(GameDef::GAME_WIDTH + 15, GameDef::GAME_HEIGHT - 5);
    cout << " 22      \n";
    gotoxy(GameDef::GAME_WIDTH + 15, GameDef::GAME_HEIGHT - 4);
    cout << " 222222   \n";
    Sleep(700);

    clrscr();

    gotoxy(GameDef::GAME_WIDTH + 15, GameDef::GAME_HEIGHT - 10);
    cout << "    1    \n";
    gotoxy(GameDef::GAME_WIDTH + 15, GameDef::GAME_HEIGHT - 9);
    cout << "   11    \n";
    gotoxy(GameDef::GAME_WIDTH + 15, GameDef::GAME_HEIGHT - 8);
    cout << "    1    \n";
    gotoxy(GameDef::GAME_WIDTH + 15, GameDef::GAME_HEIGHT - 7);
    cout << "    1    \n";
    gotoxy(GameDef::GAME_WIDTH + 15, GameDef::GAME_HEIGHT - 6);
    cout << "    1    \n";
    gotoxy(GameDef::GAME_WIDTH + 15, GameDef::GAME_HEIGHT - 5);
    cout << "    1    \n";
    gotoxy(GameDef::GAME_WIDTH + 15, GameDef::GAME_HEIGHT - 4);
    cout << "  11111  \n";
    Sleep(700);

    clrscr();
    gotoxy(GameDef::GAME_WIDTH + 7, GameDef::GAME_HEIGHT - 10);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
    cout << " SSSSS  TTTTT  AAAAA  RRRR   TTTTT\n";
    gotoxy(GameDef::GAME_WIDTH + 7, GameDef::GAME_HEIGHT - 9);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED);
    cout << "S         T   A     A R   R    T  \n";
    gotoxy(GameDef::GAME_WIDTH + 7, GameDef::GAME_HEIGHT - 8);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
    cout << " SSS      T   AAAAAAA RRRR     T  \n";
    gotoxy(GameDef::GAME_WIDTH + 7, GameDef::GAME_HEIGHT - 7);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "    S     T   A     A R  R     T  \n";
    gotoxy(GameDef::GAME_WIDTH + 7, GameDef::GAME_HEIGHT - 6);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
    cout << "SSSS      T   A     A R   RR   T  \n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    Sleep(800);

    // Clear the screen             
    clrscr();

}

// Display game instructions to the console.
void Menu::instructions() 
{
    clrscr();
    int key = 0;
    cout << "Instructions:" << endl;
    cout << "you must arrange a sequence of small shapes, called Tetraminos" << endl;
    cout << "into complete lines." << endl;
    cout << "As each line is completed, it will disappear from the screen." << endl;
    cout << "Tetraminos fall from the top of the play field to the bottom." << endl;
    cout << "Each Tetramino is made up of four blocks," << endl;
    cout << "arranged into seven different patterns." << endl;
    cout << "Keys:" << endl;
    cout << "                            Left player:           Right player:" << endl;
    cout << "LEFT                        a or A                 j or J       " << endl;
    cout << "RIGHT                       d or D                 l or L       " << endl;
    cout << "ROTATE clockwise            s or S                 k or K       " << endl;
    cout << "ROTATE counterclockwise     w or W                 i or I       " << endl;
    cout << "DROP                        x or X                 m or M       " << endl;
    cout << endl;
    cout << "press any key to get back to the menu." << endl;
    key = _getch();
}

//Displays a menu to the user to choose whether to play the game with colors or without colors.
bool Menu::chooseColors()
{

    int colors = (int)DEFINES::NOT_VALID;
    while (colors == (int)DEFINES::NOT_VALID)
    {
        clrscr();
        gotoxy(GameDef::GAME_WIDTH + 15, GameDef::GAME_HEIGHT - 12);
        cout << "(1) with colors" << endl;
        gotoxy(GameDef::GAME_WIDTH + 15, GameDef::GAME_HEIGHT - 11);
        cout << "(2) without colors" << endl;
        gotoxy(GameDef::GAME_WIDTH + 15, GameDef::GAME_HEIGHT - 10);
        cout << "your choice is: ";
        gotoxy(GameDef::GAME_WIDTH + 31, GameDef::GAME_HEIGHT - 10);
        cin >> colors;
        if (colors == (int)DEFINES::WITH_COLORS)
            return true;
        else if (colors == (int)DEFINES::WITHOUT_COLORS)
            return false;
        else
            colors = (int)DEFINES::NOT_VALID;
    }

}

//Display the opening message of the Tetris game.
void Menu::openMessage() 
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
    gotoxy(GameDef::GAME_WIDTH + 7, GameDef::GAME_HEIGHT - 12);
    cout << "TTTTT  EEEEE  TTTTT  RRRR   III  SSSS \n";
    gotoxy(GameDef::GAME_WIDTH + 7, GameDef::GAME_HEIGHT - 11);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED);
    cout << "  T    E        T    R   R   I   S    \n";
    gotoxy(GameDef::GAME_WIDTH + 7, GameDef::GAME_HEIGHT - 10);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
    cout << "  T    EEEE     T    RRRR    I    SSS \n";
    gotoxy(GameDef::GAME_WIDTH + 7, GameDef::GAME_HEIGHT - 9);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "  T    E        T    R  R    I       S\n";
    gotoxy(GameDef::GAME_WIDTH + 7, GameDef::GAME_HEIGHT - 8);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
    cout << "  T    EEEEE    T    R   RR III  SSSS \n";
    gotoxy(GameDef::GAME_WIDTH + 10, GameDef::GAME_HEIGHT - 5);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    gotoxy(GameDef::GAME_WIDTH + 10, GameDef::GAME_HEIGHT - 4);
    cout << "Without colors:" << endl;
    gotoxy(GameDef::GAME_WIDTH + 10, GameDef::GAME_HEIGHT - 3);
    cout << "(1) Start a new game Human VS Human" << endl;
    gotoxy(GameDef::GAME_WIDTH + 10, GameDef::GAME_HEIGHT - 2);
    cout << "(2) Start a new game Computer VS Human" << endl;
    gotoxy(GameDef::GAME_WIDTH + 10, GameDef::GAME_HEIGHT - 1);
    cout << "(3) Start a new game Computer VS Computer" << endl;
    gotoxy(GameDef::GAME_WIDTH + 10, GameDef::GAME_HEIGHT);
    cout << "(8) Present instructions and keys" << endl;
    gotoxy(GameDef::GAME_WIDTH + 10, GameDef::GAME_HEIGHT + 1);
    cout << "(9). EXIT" << endl;
    cout << endl;
}

//Display the opening message of the Tetris game when paused.
void Menu::openMessagePause() 
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
    gotoxy(GameDef::GAME_WIDTH + 7, GameDef::GAME_HEIGHT - 12);
    cout << "TTTTT  EEEEE  TTTTT  RRRR   III  SSSS \n";
    gotoxy(GameDef::GAME_WIDTH + 7, GameDef::GAME_HEIGHT - 11);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED);
    cout << "  T    E        T    R   R   I   S    \n";
    gotoxy(GameDef::GAME_WIDTH + 7, GameDef::GAME_HEIGHT - 10);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
    cout << "  T    EEEE     T    RRRR    I    SSS \n";
    gotoxy(GameDef::GAME_WIDTH + 7, GameDef::GAME_HEIGHT - 9);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "  T    E        T    R  R    I       S\n";
    gotoxy(GameDef::GAME_WIDTH + 7, GameDef::GAME_HEIGHT - 8);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
    cout << "  T    EEEEE    T    R   RR III  SSSS \n";
    gotoxy(GameDef::GAME_WIDTH + 10, GameDef::GAME_HEIGHT - 5);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    gotoxy(GameDef::GAME_WIDTH + 10, GameDef::GAME_HEIGHT - 4);
    cout << "Without colors:" << endl;
    gotoxy(GameDef::GAME_WIDTH + 10, GameDef::GAME_HEIGHT - 3);
    cout << "(1) Start a new game Human VS Human" << endl;
    gotoxy(GameDef::GAME_WIDTH + 10, GameDef::GAME_HEIGHT - 2);
    cout << "(2) Start a new game Computer VS Human" << endl;
    gotoxy(GameDef::GAME_WIDTH + 10, GameDef::GAME_HEIGHT - 1);
    cout << "(3) Start a new game Computer VS Computer" << endl;
    gotoxy(GameDef::GAME_WIDTH + 10, GameDef::GAME_HEIGHT);
    cout << "(4) Continue a paused game" << endl;
    gotoxy(GameDef::GAME_WIDTH + 10, GameDef::GAME_HEIGHT + 1);
    cout << "(8) Present instructions and keys" << endl;
    gotoxy(GameDef::GAME_WIDTH + 10, GameDef::GAME_HEIGHT + 2);
    cout << "(9). EXIT" << endl;
    cout << endl;
}
