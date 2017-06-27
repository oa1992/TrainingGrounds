#pragma once
#include "BaseObject.h"

class PlayerCharacter : public BaseObject
{
private:
	KeyPressed keyPressed;
public:
	void moveLeft();
	void moveRight();
};