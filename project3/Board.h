#ifndef BOARD_H
#define BOARD_H

#include "Side.h"
#include <vector>

class Board
{
public:
	Board(int nHoles, int nInitialBeansPerHole); //constructor
	int holes() const; //return number of holes without pot
	int beans(Side s, int hole) const; //return the number of beans 
	int beansInPlay(Side s) const; //return the total number of beans in the holes of the Side
	int totalBeans() const; //return the total nubmer of beans in the game, including pots
	bool sow(Side s, int hole, Side& endSide, int& endHole); //return false of the s, hole are invalid, return true after sowing the beans
	bool moveToPot(Side s, int hole, Side potOwner); //return false of the hole is invlid or a pot, return true after moving all the beans to the potOwner 
	bool setBeans(Side s, int hole, int beans); //return false if the hole is invlid or beans is negative, return true after setting the number of beans to the third parameter
private:
	int m_nHoles;
	std::vector<int> m_holes;
	int m_size;
};

#endif

