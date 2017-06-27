/*************************************************************
The input manager using the command patern. 

We code each action as a command that can be passed which will call
a function on the actor that uses it.

With pointers, this allows the ability for the user to customize 
keybindings. This may not be used for the current game, but
will be reusable at a later time.
*************************************************************/


#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "PlayerCharacter.h"
#include "InputType.h"
#include <map>

// This is the Command Interface. Base for manager
class Command
{
public:
	virtual ~Command() {}
	virtual void execute(PlayerCharacter *character) = 0;
};

class MoveLeftCommand : public Command
{
public:
	void execute(PlayerCharacter *character) 
	{ 
		character->moveLeft(); 
	}
};

class MoveRightCommand : public Command
{
public:
	void execute(PlayerCharacter *character) { character->moveRight(); }
};

class InputManager
{
private:
	// Pointers to every command necessary for movement
	Command* moveLeft;
	Command* moveRight;

	// Used to map each command with each key
	Command* commands[MAX_COMMAND_INDEX];
public:
	InputManager();
	~InputManager();

	Command* handleInput();
	void setup_input_mapping();
	void bind(int key, Command *command);
};


InputManager::InputManager()
{
	// Give functions to they keywords
	moveLeft = new MoveLeftCommand();
	moveRight = new MoveRightCommand();

	// Initialize the default binding
	commands[KEY_LEFT] = moveLeft;
	commands[KEY_RIGHT] = moveRight;
}

InputManager::~InputManager()
{
	delete moveLeft;
	delete moveRight;

	for (int i = 0; i < MAX_COMMAND_INDEX; i++)
	{
		if (commands[i] != NULL)
		{
			delete commands[i];
			commands[i] = NULL;
		}
	}

	moveLeft = NULL;
	moveRight = NULL;
}

Command* InputManager::handleInput()
{

}
