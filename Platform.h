#pragma once
#include <string>
#include <iostream>
#include <time.h>
#include "Point.h"
#include "Player.h"
using namespace std;
class IPlatform
{
public:
	virtual Point getCenter() = 0;
	virtual void setCenterX(int x) = 0;
	virtual void setCenterY(int y) = 0;
	virtual bool getVisible() = 0;
	virtual void setVisible(bool v) = 0;
	virtual void actionAfterJumped(int i) = 0;
};

class Platform : public IPlatform {
protected:
	Point center;
	bool visible;
public:
	Platform();
	Point getCenter();
	void setCenterX(int x);
	void setCenterY(int y);
	bool getVisible();
	void setVisible(bool v);
	virtual void actionAfterJumped(int i);
};

class OneTimePlatform : public Platform {
private:
public:
	OneTimePlatform() : Platform() {};
	void actionAfterJumped(int i);
};