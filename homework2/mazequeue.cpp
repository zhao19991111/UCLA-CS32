#include <iostream>
#include <queue>
using namespace std;

//function declaration
bool pathExists(char maze[][10], int sr, int sc, int er, int ec);

//coord class from the website
class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

//function PathExist
bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
	queue<Coord> coordStack;
	coordStack.push(Coord(sr, sc));
	maze[sr][sc] = '*';
	while (!coordStack.empty())
	{
		Coord t = coordStack.front();
		coordStack.pop();
		int r = t.r();
		int c = t.c();
		if (r == er && c == ec)  //check if our coordinates are the end coordinates, if so return true
		{
			return true;
		}
		else
		{
			if (r + 1 < 9 && maze[r + 1][c] == '.') //move SOUTH
			{
				coordStack.push(Coord(r + 1, c));
				maze[r + 1][c] = '*';
			}
			if (c - 1 > 0 && maze[r][c - 1] == '.')//move WEST
			{
				coordStack.push(Coord(r, c - 1));
				maze[r][c - 1] = '*';
			}
			if (r - 1 > 0 && maze[r - 1][c] == '.') //move NORTH
			{
				coordStack.push(Coord(r - 1, c));
				maze[r - 1][c] = '*';
			}
			if (c + 1 < 9 && maze[r][c + 1] == '.') //move EAST
			{
				coordStack.push(Coord(r, c + 1));
				maze[r][c + 1] = '*';
			}
		}
	}
	return false;
}

/*
int main()
{
	char maze[10][10] = {
		{ 'X','X','X','X','X','X','X','X','X','X' },
		{ 'X','.','.','.','.','X','.','.','.','X' },
		{ 'X','.','X','X','.','X','X','X','.','X' },
		{ 'X','X','X','.','.','.','.','X','.','X' },
		{ 'X','.','X','X','X','.','X','X','X','X' },
		{ 'X','.','X','.','.','.','X','.','.','X' },
		{ 'X','.','.','.','X','.','X','.','.','X' },
		{ 'X','X','X','X','X','.','X','.','X','X' },
		{ 'X','.','.','.','.','.','.','.','.','X' },
		{ 'X','X','X','X','X','X','X','X','X','X' }
	};

	if (pathExists(maze, 3, 5, 8,8))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;
}
*/