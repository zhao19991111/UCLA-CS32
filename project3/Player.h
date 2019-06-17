#ifndef PLAYER_H
#define PLAYER_H

#include "Side.h"
#include <iostream>
#include "Board.h"

class Player
{
public:
	Player(std::string name); //constructor
	std::string name() const; //name
	virtual bool isInteractive() const; //false if computer, true if human, default is computer
	virtual int chooseMove(const Board& b, Side s) const = 0; //play the side s and inplement in own way
	virtual ~Player(); //virtual destructor
private:
	std::string m_name;
};

class HumanPlayer :public Player
{
public:
	HumanPlayer(std::string name);
	virtual bool isInteractive() const;
	virtual int chooseMove(const Board& b, Side s) const;
	~HumanPlayer();
};

class BadPlayer :public Player
{
public:
	BadPlayer(std::string name);
	virtual bool isInteractive() const;
	virtual int chooseMove(const Board& b, Side s) const;
	~BadPlayer();
};

class SmartPlayer :public Player
{
public:
	SmartPlayer(std::string name);
	virtual bool isInteractive() const;
	virtual int chooseMove(const Board& b, Side s) const;
	~SmartPlayer();
};

#endif

