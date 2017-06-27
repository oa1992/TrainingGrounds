#pragma once
/*************************************************
A class handling the Input Types for the Input Manager
Input types can be: Action, State, Range
Actions can be Executed or Stopped
States can be Pressed or Released
**************************************************/

enum InputType
{
	ACTION,
	STATE,
	RANGE
};

enum Action
{
	EXECUTE = true,
	STOPPED = false,
	MAX_ACTION_INDEX
};

enum State
{
	PRESSED = true,
	RELEASED = false,
	MAX_STATE_INDEX
};

enum CommandTypes
{
	KEY_LEFT,
	KEY_RIGHT,
	MAX_COMMAND_INDEX
};

