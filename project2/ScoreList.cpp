#include "ScoreList.h"

ScoreList::ScoreList()
{

}

bool ScoreList::add(unsigned long score)
{
	if (score >= 0 && score <= 100 && scorelist.size() < DEFAULT_MAX_ITEMS)
	{
		scorelist.insert(score);
		return true;
	}
	else
	{
		return false;
	}
}

bool ScoreList::remove(unsigned long score)
{
	int pos = scorelist.find(score);
	if (pos==-1)
	{
		return false;
	}
	else
	{
		scorelist.erase(pos);
		return true;
	}
}

int ScoreList::size() const
{
	return scorelist.size();
}

unsigned long ScoreList::minimum() const
{
	if (scorelist.empty())
	{
	
		return NO_SCORE;
	}
	else
	{
		unsigned long min;
		scorelist.get(0, min);
		return min;
	}
}

unsigned long ScoreList::maximum() const
{
	if (scorelist.empty())
	{

		return NO_SCORE;
	}
	else
	{
		unsigned long max;
		scorelist.get(scorelist.size()-1, max);
		return max;
	}
}