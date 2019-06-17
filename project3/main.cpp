#if defined(_MSC_VER)  &&  !defined(_DEBUG)
#include <iostream>
#include <windows.h>
#include <conio.h>

struct KeepWindowOpenUntilDismissed
{
	~KeepWindowOpenUntilDismissed()
	{
		DWORD pids[1];
		if (GetConsoleProcessList(pids, 1) == 1)
		{
			std::cout << "Press any key to continue . . . ";
			_getch();
		}
	}
} keepWindowOpenUntilDismissed;
#endif


#include <iostream>
#include "Board.h"
#include "Player.h"
#include "Game.h"
#include <cassert>

// implemetation of position function//
int position(Side s, int hole, int nHoles)
{
	if (s == NORTH)
	{
		if (hole >= 0 && hole <= nHoles) //(0,1,2,....m_nHoles)
			return hole;
		else
			return -1;
	}
	else if (s == SOUTH)
	{
		if (hole == 0)
			return nHoles + 1; //0
		else if (hole > 0 && hole <= nHoles) //(1,2,....m_nHoles)
			return nHoles * NSIDES + NSIDES - hole;
		else
			return -1;
	}
	else
		return -1;
}
//implementation of chooseSmartMove
void chooseSmartMove(Side s, Side m_s, const Board& b, int& bestHole, int& value, int layer)
{
	Board m_b = b;
	if (m_b.beansInPlay(SOUTH) == 0 || m_b.beansInPlay(NORTH) == 0) //if game ends
	{
		bestHole = -1;
		for (int i = 1; i <= m_b.holes(); i++) //move beans to each pot
		{
			m_b.moveToPot(SOUTH, i, SOUTH);
			m_b.moveToPot(NORTH, i, NORTH);
		}
		value = m_b.beans(m_s, POT) - m_b.beans(opponent(m_s), POT); //set value to the difference
		if (value < 0)
			value = -MAXV; //set to a large negative value
		else if (value > 0)
			value = MAXV; //set to a large positive value
		return;
	}
	if (layer <= 1) //if we should not continue
	{
		bestHole = -1;
		int beansM = 0, beansO = 0;
		for (int i = 0; i <= m_b.holes(); i++)
		{
			beansM += m_b.beans(m_s, i);
			beansO += m_b.beans(opponent(m_s), i);
		}
		value = beansM - beansO; //set value to the difference
		return;
	}
	int v2 = 0, h2 = 0;
	if (s == m_s) //we need to find the largest value
		value = -MAXV - 1; //initialize value a default large negative number less than the smallest situation
	else //we need to find the smallest value
		value = MAXV + 1; //initialize value to a default small negative number more than the largest situation
	//else
	for (int h = 1; h <= b.holes(); h++) //for every possible hole
	{
		if (m_b.beans(s, h) != 0) //if the player can choose
		{
			//make the move//
			Side eSide;
			int eHole = 0;
			m_b.sow(s, h, eSide, eHole); //sow that hole
			if (eSide == s && eHole == POT) //if the last one end up in my pot
			{
				int hExtra, vExtra;
				chooseSmartMove(s, m_s, m_b, hExtra, vExtra, layer); //choose my second move
				m_b.sow(s, hExtra, eSide, eHole); //sow that hole
				//adjust value if possible//
				if (s == m_s) //if my side
				{
					if (vExtra > value) //choose the largest value
					{
						bestHole = h;
						value = vExtra;
					}
					else if (vExtra == value && m_s == SOUTH) //if side is SOUTH and values are equal, choose the latter one
					{
						bestHole = h;
						value = vExtra;
					}
				}
				else
				{
					if (vExtra < value) //choose the smallest value
					{
						bestHole = h;
						value = vExtra;
					}
					else if (vExtra == value && m_s == SOUTH) //if side of SOUTH and values are equal, choose the latter one
					{
						bestHole = h;
						value = vExtra;
					}
				}
			}
			else if (eSide == s && b.beans(s, eHole) == 1 && b.beans(opponent(s), eHole) != 0) //if capture
			{
				m_b.moveToPot(opponent(s), eHole, s);
				m_b.moveToPot(s, eHole, s); //do the capture
			}
			//recursion//
			chooseSmartMove(opponent(s), m_s, m_b, h2, v2, layer - 1); //do the next layer
			//unmake the move//
			m_b = b;
			//adjust value//
			if (s == m_s) //if my side
			{
				if (v2 > value) //choose the largest value
				{
					bestHole = h;
					value = v2;
				}
				else if (v2 == value && m_s == SOUTH) //if side is SOUTH and values are equal, choose the latter one
				{
					bestHole = h;
					value = v2;
				}
			}
			else
			{
				if (v2 < value) //choose the smallest value
				{
					bestHole = h;
					value = v2;
				}
				else if (v2 == value && m_s == SOUTH) //if side of SOUTH and values are equal, choose the latter one
				{
					bestHole = h;
					value = v2;
				}
			}
		}
	}
	return;
}


using namespace std;

int main()
{
	//test "Board.h"//
	Board s(6, 2);
	assert(s.holes() == 6);
	assert(s.beans(NORTH, 1) == 2);
	assert(s.beans(NORTH, 0) == 0);
	assert(s.beans(SOUTH, 0) == 0);
	assert(s.beans(SOUTH, 6) == 2);
	assert(s.beansInPlay(SOUTH) == 12);
	assert(s.totalBeans() == 24);


	Side end;
	int hole;
	s.sow(NORTH, 2, end, hole);
	assert(s.beans(NORTH, 2) == 0); //   3 0 2 2 2 2
	assert(s.beans(NORTH, 1) == 3); // 1             0
	assert(s.beans(NORTH, 0) == 1); //   2 2 2 2 2 2
	assert(end == NORTH);
	assert(hole == 0);
	assert(s.totalBeans() == 24);

	s.sow(SOUTH, 6, end, hole);
	assert(s.beans(SOUTH, 6) == 0); //   3 0 2 2 2 3  
	assert(s.beans(SOUTH, 0) == 1); // 1             1
	assert(s.beans(NORTH, 6) == 3); //   2 2 2 2 2 0
	assert(end == NORTH);
	assert(hole == 6);
	assert(s.totalBeans() == 24);
	assert(s.beansInPlay(SOUTH) == 10);

	s.sow(NORTH, 6, end, hole);
	assert(s.beans(NORTH, 6) == 0); //   3 0 3 3 3 0 
	assert(s.beans(NORTH, 5) == 3); // 1             1 
	assert(s.beans(NORTH, 4) == 3); //   2 2 2 2 2 0 
	assert(s.beans(NORTH, 3) == 3);
	assert(end == NORTH);
	assert(hole == 3);
	assert(s.totalBeans() == 24);
	assert(s.beansInPlay(NORTH) == 12);
	

	s.sow(NORTH, 1, end, hole);
	assert(s.beans(NORTH, 1) == 0); //   0 0 3 3 3 0
	assert(s.beans(NORTH, 0) == 2); // 2             1
	assert(s.beans(SOUTH, 1) == 3); //   3 3 2 2 2 0 
	assert(s.beans(SOUTH, 2) == 3);
	assert(end == SOUTH);
	assert(hole == 2);
	assert(s.totalBeans() == 24);
	assert(s.beansInPlay(NORTH) == 9);


	if (!s.moveToPot(SOUTH, 1, SOUTH))  //   0 0 3 3 3 0
	assert(s.beans(SOUTH, 0) == 0);     // 2             4
	                                    //   0 3 2 2 2 0 

	assert(s.beans(SOUTH, 0) == 4); 
	assert(s.beans(SOUTH, 1) == 0); 

	if (s.setBeans(SOUTH, 1, 20))    
	assert(s.beans(SOUTH, 1) == 20);    //   0 0 3 3 3 0
										// 2             4
										//   20 3 2 2 2 0 
	s.sow(SOUTH, 1, end, hole);
	assert(s.beans(SOUTH, 2) == 5);
	assert(end == NORTH);
	assert(hole == 6);
	assert(s.totalBeans() == 44);      //   1 1 4 4 4 2
	assert(s.beansInPlay(SOUTH) == 20);// 2             6
	assert(s.beansInPlay(NORTH) == 16);//   1 5 4 4 4 2

	//test "Board.h" for negative initialization//

	Board stupid(-1, -1);
	assert(stupid.beans(SOUTH, 1) == 0);
	assert(stupid.beans(NORTH, POT) == 0);
	assert(stupid.beans(NORTH, 2) == -1);
	assert(stupid.holes() == 1);
	assert(stupid.setBeans(NORTH, 2, 2)== false);
	assert(stupid.beans(NORTH, 2) == -1);
	assert(stupid.sow(NORTH, 2, end, hole) == false);
	//test "Game.h//

	BadPlayer bp1("Bart");
	BadPlayer bp2("Homer");
	HumanPlayer bp3("Me");
	Board b(3, 0);
	b.setBeans(SOUTH, 1, 2);
	b.setBeans(NORTH, 2, 1);
	b.setBeans(NORTH, 3, 2);
	Game g(b, &bp1, &bp2);
	bool over;
	bool hasWinner;
	Side winner;
	//    Homer
	//   0  1  2
	// 0         0
	//   2  0  0
	//    Bart
	g.status(over, hasWinner, winner);
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 0 &&
		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
		g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);

	g.move();

	//   0  1  0
	// 0         3
	//   0  1  0
	g.status(over, hasWinner, winner);
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

	g.move();
	//   1  0  0
	// 0         3
	//   0  1  0
	g.status(over, hasWinner, winner);
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
		g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

	g.move();
	//   1  0  0
	// 0         3
	//   0  0  1
	g.status(over, hasWinner, winner);
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
		g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 1);

	g.move();
	//   0  0  0
	// 1         4
	//   0  0  0
	g.status(over, hasWinner, winner);
	assert(over && g.beans(NORTH, POT) == 1 && g.beans(SOUTH, POT) == 4 &&
		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
	assert(hasWinner && winner == SOUTH);


	//test "Game.h" for no move at the beginning
	Board o(3, 0);
	o.setBeans(NORTH, 2, 2);
	Game stupidg(o, &bp1, &bp2);
	stupidg.play();
	assert(stupidg.beans(NORTH, POT) == 2);
	

	cout << "all test passed!";

	SmartPlayer j("super1");
	SmartPlayer l("super2");
	Board c(6, 4);
	Game k(c, &l, &bp2);
	k.play();

	Board m(5, 4);
	Game q(m, &l, &bp2);
	q.play();

	Board n(4, 10);
	Game p(n, &l, &bp2);
	p.play();

	Game z(c, &l, &bp3); //test if super will win against human
	z.play();
	

}

