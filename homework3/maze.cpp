

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
	if (sr == er && sc == ec) //end up in the destination
	{
		return true;
	}
	else
	{
		maze[sr][sc] = '@'; //move to this position
		if (sr+1 < 9 && maze[sr+1][sc] == '.' && pathExists(maze, sr + 1, sc, er, ec)) //if can move to the south and there is a path in the south
		{
			return true;
		}
		if (sc-1 > 0 && maze[sr][sc-1] == '.' && pathExists(maze, sr, sc - 1, er, ec))//if can move to the west and there is a path in the west
		{
			return true;
		}
		if (sr-1 > 0 && maze[sr - 1][sc] == '.' && pathExists(maze, sr - 1, sc, er, ec))//if can move to the north and there is a path in the north
		{
			return true;
		}
	    if (sc+1 < 9 && maze[sr][sc + 1] == '.' && pathExists(maze, sr, sc + 1, er, ec))//if can move to the east and there is a path in the east
		{
			return true;
		}
		return false;
	}
}

