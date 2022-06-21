#include "Platform.h"
#include <random>
Platform::Platform()
{
	this->center = Point();
	this->visible = true;
}

Point Platform::getCenter()
{
	return this->center;
}

void Platform::setCenterX(int x)
{
	this->center.x = x;
}

void Platform::setCenterY(int y)
{
	this->center.y = y;
}

bool Platform::getVisible()
{
	return this->visible;
}

void Platform::setVisible(bool v)
{
	this->visible = v;
}

void Platform::actionAfterJumped(int i)
{
	this->visible = true;
}

void OneTimePlatform::actionAfterJumped(int i)
{
	this->visible = false;
}
