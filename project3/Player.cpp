#include "Player.h"
#include <iostream>



//implementation of Player//
Player::Player(std::string name) //constructor
	:m_name(name)
{}

std::string Player::name() const  //name
{
	return m_name;
}

bool Player::isInteractive() const //default not interactive
{
	return false;
}

Player::~Player() //destructor
{
}

//implementation of BadPlayer//

BadPlayer::BadPlayer(std::string name) //constructor
	:Player(name)
{
}

bool BadPlayer::isInteractive() const //computer is not interactive
{
	return false;
}

int BadPlayer::chooseMove(const Board& b, Side s) const //choose the hole with the most beans to sow
{
	int most = -1;
	int move = 0;
	for (int i = 1; i <= b.holes(); i++) //loop through holes to find the one with the most beans
	{
		if (b.beans(s, i) >= most)
		{
			most = b.beans(s, i);
			move = i;
		}
	}
	if (move == 0)
		return -1;
	else
		return move;
}

BadPlayer::~BadPlayer() //destructor
{ 

}

//implementation of SmartPlayer//

SmartPlayer::SmartPlayer(std::string name) //constructor
	:Player(name)
{

}

bool SmartPlayer::isInteractive() const //computer is not interactive
{
	return false;
}

int SmartPlayer::chooseMove(const Board& b, Side s) const //choose the hole with the most beans to sow
{
	int most = 0;
	int best = 0;
	for (int i = 1; i <= b.holes(); i++) //loop through holes to find the one with the most beans
	{
		if (b.beans(s, i) >= most)
		{
			most = b.beans(s, i);
			best = i;
		}
	} //set the default best
	int val = b.beans(s,POT) - b.beans(opponent(s),POT); //defalut value
	chooseSmartMove( s, s, b, best, val);
	return best;
}


SmartPlayer::~SmartPlayer() //destructor
{

}
//implementation of HumanPlayer

HumanPlayer::HumanPlayer(std::string name) //constructor
	:Player(name)
{
}

bool HumanPlayer::isInteractive() const //human is interactive
{
	return true;
}

int HumanPlayer::chooseMove(const Board& b, Side s) const
{
	int move;
	std::cout << "Please choose your move between 1 and " << b.holes() << ":" << std::endl; //prompt the user
	std::cin >> move;
	if (move >= 1 && move<=b.holes() && b.beans(s, move) > 0) //if the move is valid
	{
		return move;
	}
	else
	{
		std::cout << "You cannot sow this hole!" << std::endl;
		return chooseMove(b, s); //recursion
	}
	return -1;
}

HumanPlayer::~HumanPlayer() //destructor
{

}

