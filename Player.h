#pragma once
#include "Point.h"
#include <string.h>
class Player {
private:
	Point obj;
	int score;
public:
	Player() {
		this->obj = Point(300,300);
		this->score = 0;
	}
	void setScore(int score);
	void setX(int x);
	void setY(int y);
	int getScore();
	int getX();
	int getY();
};
