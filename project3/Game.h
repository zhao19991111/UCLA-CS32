#ifndef GAME_H
#define GAME_H

#include "Player.h"

class Game
{
public:
	Game(const Board& b, Player* south, Player* north); //constructor
	void display() const; //Display in a certain manner
	void status(bool& over, bool& hasWinner, Side& winner) const; //set the status
	bool move(); //move
	void play(); //play
	int beans(Side s, int hole) const; //return the beans
private:
	Player* m_south;
	Player* m_north;
	Player* currentPlayer;
	Side currentSide;
	Board m_board;
	bool isOver;
	bool isWinner;
};

#endif
