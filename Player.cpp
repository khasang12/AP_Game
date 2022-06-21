#include "Player.h"
#include <fstream>

int Player::getScore()
{
	return this->score;
}

void Player::setScore(int score)
{
	this->score = score;
}

void Player::setX(int x)
{
	this->obj.x = x;
}

void Player::setY(int y)
{
	this->obj.y = y;
}

int Player::getX()
{
	return this->obj.x;
}

int Player::getY()
{
	return this->obj.y;
}


