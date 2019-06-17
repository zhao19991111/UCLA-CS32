#include "Game.h"
#include <iostream>

Game::Game(const Board& b, Player* south, Player* north)
	:m_south(south), m_north(north), currentPlayer(south), currentSide(SOUTH), m_board(b), isOver(false), isWinner(false)
{
	
}

void Game::display() const
{
	std::cout << std::endl << m_north->name() <<std::endl; //display the name of north player
	std::cout << "|  ";
	for (int i = 1; i <= m_board.holes(); i++)
	{
		std::cout << m_board.beans(NORTH, i) << " "; //display the north holes
	}
	std::cout << "  ";
	std::cout << std::endl;
	std::cout << "|" << m_board.beans(NORTH, POT) << " "; //display the pots
	for (int i = 1; i <= m_board.holes(); i++)
	{
		std::cout << "  ";
	}
	std::cout << m_board.beans(SOUTH, POT) << "" << std::endl; //display the south holes
	std::cout << "|  ";
	for (int i = 1; i <= m_board.holes(); i++)
	{
		std::cout << m_board.beans(SOUTH, i) << " ";
	}
	std::cout << "  ";
	std::cout << std::endl;
	std::cout<< m_south->name() << std::endl << "________________" << std::endl; //display the south player
}

void Game::status(bool& over, bool& hasWinner, Side& winner) const
{
	
	if (m_board.beansInPlay(SOUTH) == 0 || m_board.beansInPlay(NORTH) == 0) //game over
	{
		over = true; //set over to true
		int beansNorth = 0, beansSouth = 0;
		for (int i = 0; i <= m_board.holes(); i++) //calculate the beans in south and north
		{
			beansNorth += m_board.beans(NORTH, i);
			beansSouth += m_board.beans(SOUTH, i);
		}
		if (beansNorth == beansSouth) //if tie, no winner
			hasWinner = false;
		else if (beansNorth > beansSouth) //if not tie, assign winner
		{
			hasWinner = true;
			winner = NORTH;
		}
		else
		{
			hasWinner = true;
			winner = SOUTH;
		}
	}
	else //game not end
	{
		over = false;
	}
}

bool Game::move()
{
	status(isOver, isWinner, currentSide);
	if (isOver)
	{
		for (int i = 1; i <= m_board.holes(); i++) //move beans to each pot
		{
			m_board.moveToPot(SOUTH, i, SOUTH);
			m_board.moveToPot(NORTH, i, NORTH);
		}
		display(); //display the last scene
		return false;
	}
	else
	{
		display(); //display the board
		Side eSide;
		int eHole = 0;
		int hole = currentPlayer->chooseMove(m_board, currentSide); //choose move by player
		std::cout << currentPlayer->name() << " chooses hole " << hole << std::endl;
		if (hole == -1) //invalid or no move
			return false;
		else
			m_board.sow(currentSide, hole, eSide, eHole); //sow the move
		if (eSide == currentSide && eHole == POT) //end up in my pot
		{
			std::cout << currentPlayer->name() << " gets another turn!";
			return move();
		}
		else if (eSide == currentSide && m_board.beans(currentSide, eHole) == 1 && m_board.beans(opponent(currentSide), eHole) != 0) //do a capture
		{
			m_board.moveToPot(opponent(currentSide), eHole,currentSide);
			m_board.moveToPot(currentSide, eHole, currentSide);
		}
		currentSide = opponent(currentSide); //change the side
		if (currentSide == NORTH) //change the player
			currentPlayer = m_north;
		else
			currentPlayer = m_south;
		return true;
	}
}

void Game::play()
{
	int count = 0;
	status(isOver, isWinner, currentSide); //decide if the game is initiated properly
	if (isOver)
		move();
	if (!m_south->isInteractive() && !m_north->isInteractive()) //if both players are computer
	{
		while (!isOver)  //if game is not over
		{
			move();
			count++;
			if (count % 2 == 0) //break every two moves
			{
				std::cout << "PRESS 'ENTER' TO CONTINUE:" << std::endl;
				std::cin.ignore(10000, '\n');
			}
			status(isOver, isWinner, currentSide); //decide if over
		}
	}
	else //if anyone of them is human player
	{
		while (!isOver)
		{
			move();
			status(isOver, isWinner, currentSide);  //decide if over
		}
	}
	status(isOver, isWinner, currentSide); //decide the final results
	if (isOver)
	{
		std::cout << std::endl << "GAME OVER!" << std::endl;
	}
	if (isWinner)
	{
		if (currentSide == SOUTH)
			std::cout << "Winner is " << m_south->name()<<std::endl;
		else
			std::cout << "Winner is " << m_north->name()<<std::endl;
	}
	else
		std::cout << "No Winner!"<<std::endl;
}

int Game::beans(Side s, int hole) const
{
	return m_board.beans(s, hole);
}