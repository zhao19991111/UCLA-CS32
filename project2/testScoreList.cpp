#include "ScoreList.h"
#include <iostream>
#include <cassert>
using namespace std;
int main()
{
	ScoreList s;
	assert(s.add(101) == 0);
	assert(s.add(-1) == 0);
	assert(s.add(92) == 1);
	assert(s.add(93) == 1);
	assert(s.add(99) == 1);
	assert(s.size() == 3);
	assert(s.add(23) == 1);
	assert(s.add(70) == 1);
	assert(s.size() == 5);
	assert(s.remove(34) == 0);
	assert(s.remove(23) == 1);
	assert(s.size() == 4);
	assert(s.minimum()==70);
	assert(s.maximum() == 99);
	ScoreList p;
	p = s;
	assert(p.minimum() == 70);
	cout << "all test passed!" << endl;

}
