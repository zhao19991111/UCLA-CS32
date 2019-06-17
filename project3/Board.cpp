#include "Board.h"
#include <iostream>



Board::Board(int nHoles, int nInitialBeansPerHole)
{
	if (nHoles <= 0) //if nHoles is not valid
	{
		m_nHoles = 1;
	}
	else
	{
		m_nHoles = nHoles;
	}
	m_size = m_nHoles * NSIDES + NSIDES; //calculate the size of the vector
	m_holes.resize(m_size);
	for (int i = 0; i < m_size; i++)  //assign each hole
	{
		if (i != 0 && i != m_nHoles + 1)
		{
			if (nInitialBeansPerHole < 0) //if number is not valid
				m_holes[i] = 0;
			else
				m_holes[i] = nInitialBeansPerHole;
		}
	}
}

int Board::holes() const
{
	return m_nHoles;
}

int Board::beans(Side s, int hole) const
{
	if (s == NORTH)
	{
		if (hole >= 0 && hole <= m_nHoles) //(0,1,2,....m_nHoles)
			return m_holes[hole];
		else
			return -1;
	}
	else if (s == SOUTH)
	{
		if (hole == 0)
			return m_holes[m_nHoles + 1]; //0
		else if (hole > 0 && hole <= m_nHoles) //(1,2,....m_nHoles)
			return m_holes[m_size - hole];
		else
			return -1;
	}
	else
		return -1;
}

int Board::beansInPlay(Side s) const
{
	int numInPlay = 0;
	for (int i = 1; i <= m_nHoles; i++)
	{
		numInPlay += beans(s, i);
	}
	return numInPlay;
}

int Board::totalBeans() const
{
	int totalNumber = 0;
	for (int i = 0; i < m_size; i++) //start from the first pot and end at the last pot
	{
		totalNumber += m_holes[i];
	}
	return totalNumber;
}

bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{
	if (hole <= 0 || hole > m_nHoles || beans(s, hole) <= 0)
		return false;
	else
	{
		int pos = 0;
		int count = 0;
		int numOfBeans = beans(s, hole); //take the beans in the hole
		m_holes[position(s, hole, m_nHoles)] = 0; //set the hole to empty
		if (hole == POT)
			return false;
		else if (s == NORTH)
		{
			if (hole >= numOfBeans) //lest than one loop
			{
				for (int i = 1; i <= numOfBeans;i++)
					m_holes[hole-i]++;
				pos = m_size - (hole - numOfBeans); //set the final position
			}
			else
			{
				for (int i = 1; i <= hole; i++) //add the first loop
					m_holes[hole - i]++;
				
				int size = numOfBeans - hole;
		    //add loops to each of the elements except opponent's pot
				int loops = size / (m_size-1); //num of loops needed
				for (int i = 0; i < m_size; i++)
					if (i!=m_nHoles+1)
					m_holes[i] += loops;
				
				int extra = size % (m_size-1); //extra times 
				while (count < extra)
				{
					pos++;
					if ((m_size - pos) != (m_nHoles + 1)) //not in the opponent's pot
					{
						m_holes[m_size - pos]++;
						count++;
					}
				}
			}
		}
		else // s==SOUTH
		{
			if (m_size - hole > numOfBeans) //less than a loop
			{
				for (int i = 1; i <= numOfBeans ;i++)
					m_holes[m_size - hole - i]++;
				pos = hole + numOfBeans;
			}
			else
			{
				for (int i = 1; i < m_size - hole; i++) //add the first loop
					m_holes[i]++;
				int size = numOfBeans - (m_size - hole -1); //substract the number of execution
				//add loops to each of the elements except opponent's pot
				int loops = size / (m_size - 1); //num of loops needed
				for (int i = 1; i < m_size; i++) //skip over 0
					m_holes[i] += loops;

				int extra = size % (m_size - 1); //find extra moves after complete loops
				while (count < extra)
				{
					pos++;
					if ((m_size - pos) != 0)
					{
						m_holes[m_size-pos]++;
						count++;
					}
				}
			}
		}
		if (pos < m_nHoles + 1) //decide the position
		{
			endSide = SOUTH;
			endHole = pos;
		}
		else if (pos == m_nHoles + 1)
		{
			endSide = SOUTH;
			endHole = 0;
		}
		else
		{
			endSide = NORTH;
			endHole = m_size - pos;
		}
		return true;
	}
}

bool Board::moveToPot(Side s, int hole, Side potOwner)
{
	if (hole > 0 && hole < m_nHoles + 1) //valid hole
	{
		m_holes[position(potOwner, 0, m_nHoles)] += beans(s, hole); //move to the pot
		m_holes[position(s, hole, m_nHoles)] = 0; //clear the beans
		return true;
	}
	else
		return false;
}

bool Board::setBeans(Side s, int hole, int beans)
{
	if (hole < 0 || hole > holes() || beans < 0) //invalid hole and beans
		return false;
	else
	{
		m_holes[position(s, hole, m_nHoles)] = beans; //set beans
		return true;
	}
}