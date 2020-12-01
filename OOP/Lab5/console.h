#pragma once
#include "controller.h"

class TaskConsole {
private:
	TaskControllerModeA consoleVectorModeA;
	TaskControllerModeB consoleVectorModeB;
public:
	TaskConsole() {};
	void run();
	TElem uiAddOrUpdateTask(char* token, char title[], char date[], char mirrorImage[], char type[], int numberOfRepetitions);
	bool validInput(char title[], char date[], char mirrorImage[], char type[], int numberOfRepetitions);
};