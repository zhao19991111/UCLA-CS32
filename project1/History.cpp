#include "History.h"
#include "globals.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols)
	:numberOfKill(new int*[nRows]),m_row(nRows),m_col(nCols)
{
	for(int i=0;i<nRows;i++)
	{
		numberOfKill[i] = new int[nCols];
		for (int j = 0; j < nCols; j++)
		{
			numberOfKill[i][j] = 0;
		}
	}
}
History::~History()
{
	for (int i = 0; i < m_row; i++)
	{
		delete numberOfKill[i];
	}
}

bool History::record(int r, int c)
{
	if (r<1 || r>m_row || c<1 || c>m_col)
	{
		return false;
	}
	else
	{
		numberOfKill[r-1][c-1]++;
		return true;
	}
}

void History::display() const
{
	
	// Fill the grid with dots
	char grid[MAXROWS][MAXCOLS];
	int r, c;
	for (r = 0; r < m_row; r++)
		for (c = 0; c < m_col; c++)
		{
			if (numberOfKill[r][c] >= 26)
				grid[r][c] = 'Z';
			else if (numberOfKill[r][c] > 0)
			{
				grid[r][c] = 'A' + numberOfKill[r][c] - 1;
			}
			else
			{
				grid[r][c] = '.';
			}
		}
	// Draw the Grid
	clearScreen();
	for (r = 0; r < m_row; r++)
	{
		for (c = 0; c < m_col; c++)
		     cout << grid[r][c];
		cout << endl;
	}
	cout << endl;
}