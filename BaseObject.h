/*************************************************************
This object will be the base class for every character in the game.
Known classes to inherit will be PlayerCharacter and Enemy.
*************************************************************/
#pragma once
#include "Position.h"
#include "LTexture.h"

enum KeyPressed
{
	LEFT,
	RIGHT,
	MAX_KEYS
};


class BaseObject
{
private:
	Position position;
	bool collidable;
	LTexture spriteSheet;

public:
	BaseObject();
	BaseObject(bool collidable);
	~BaseObject();

	virtual void isCollidable() = 0;
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void handleInput() = 0;

};

BaseObject::BaseObject()
{
	collidable = false;
}

BaseObject::BaseObject(bool collidable)
{
	this->collidable = collidable;
}

BaseObject::~BaseObject()
{

}
