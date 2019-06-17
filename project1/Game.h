#ifndef GAME_H
#define GAME_H
#include "Arena.h"

class Game
{
public:
	// Constructor/destructor
	Game(int rows, int cols, int nZombies);
	~Game();

	// Mutators
	void play();

private:
	Arena* m_arena;
};
int decodeDirection(char dir);

#endif

