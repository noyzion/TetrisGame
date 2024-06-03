#include "player.h"
#include "general.h"
#include "gameDef.h"
#include <iostream>
using namespace std;

// Constructor: Player
Player::Player(const int distance,int score, int winner) : distance(distance), score(score), winner(winner)
{
	this->middle = distance + (0.5 * GameDef::GAME_WIDTH);
}

//dtor
Player::~Player() {}

//Returns the distance attribute, representing the player's position on the screen.
int Player::getDistance() const
{
	return this->distance;
}

//Returns the middle attribute, calculated as the sum of distance and half of GameDef::GAME_WIDTH.
int Player::getMiddle() const
{
	return this->middle;
}

//Returns the current score of the player.
int Player::getScore() const
{
	return this->score;
}

//init the player's score.
void Player::initScore()
{
	this->score = 0;
}

//Update the player's score and display it.
void Player::setScore(int score) 
{
	this->score += score;
	this->displayScore();
}

// Displays the player's score on the screen.
void Player::displayScore() const
{
	gotoxy(this->distance, GameDef::GAME_HEIGHT + 5);
	cout << "Player score: " << this->getScore();

}

int Player::GetWinner() const
{
	return this->winner;
}
void Player::SetWinner(int win)
{
	this->winner = win;
}

Board& Player::getBoard() 
{
	return board;
}
