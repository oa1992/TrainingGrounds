/***************************************************
The position class will have an X and Y position for
Whoever uses it. Merely a resource.
***************************************************/
#pragma once

class Position
{
private:
	int x;
	int y;
public:
	Position();
	Position(int x, int y);
	~Position();

	int getX();
	int getY();
	
	void setX(int x);
	void setY(int y);

	int move(int x, int y);
	int moveBy(int x, int y);

};

Position::Position()
{
	x = 0;
	y = 0;
}

Position::Position(int x, int y)
{
	this->x = x;
	this->y = y;
}

Position::~Position() {}

int Position::getX() { return x; }
int Position::getY() { return y; }

void Position::setX(int x) { this->x = x; }
void Position::setY(int y) { this->y = y; }

// The move function will change the current x and y position to a new x and y position
int Position::move(int x, int y)
{
	this->x = x;
	this->y = y;
}

// The moveBy function will change the current x and y position by the value passed respectively
int Position::moveBy(int x, int y)
{
	this->x += x;
	this->y += y;
}

