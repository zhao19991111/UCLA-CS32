#include <iostream>
#include "Sequence.h"
#include <cassert>
using namespace std;

int main()
{
	Sequence s1,s2;
	unsigned long s;
	assert(s1.empty());
	assert(s1.find(1) == -1);
	assert(s1.insert(1) == 0);
	assert(s1.insert(2) == 1);
	assert(s1.insert(3) == 2);
	assert(s1.insert(1,1) == 1);
	assert(s1.get(2,s) == 1);
	assert(s1.size() == 4);
	assert(s==2);
	assert(s2.insert(5) == 0);
	assert(s2.insert(1,6) == 1);
	assert(s2.insert(2,7) == 2);
	assert(s2.insert(4,5) == -1);
	assert(s2.insert(3,8) == 3);
	assert(s2.insert(9) == 4);
	assert(s2.insert(9) == 4);
	assert(s2.remove(9) == 2);
	assert(s2.size() == 4);
	s1.swap(s2);
	assert(s1.get(2, s) == 1);
	assert(s == 7);
	s2 = s1;
	assert(s2.get(2, s) == 1);
	assert(s == 7);


	cout << "Passed all tests" << endl;
	
}
