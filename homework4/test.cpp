#include "Sequence.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

void test()
{
	Sequence<int> si;
	Sequence<string> ss;
	assert(ss.empty());
	assert(ss.size() == 0);
	assert(ss.insert("Hello") == 0);
	assert(si.insert(0, 20) == 0);
	assert(si.insert(10) == 0);
	assert(si.remove(10) == 1);
	assert(si.erase(0));
	assert(ss.remove("Goodbye") == 0);
	assert(ss.find("Hello") == 0);
	string s;
	assert(ss.get(0, s));
	assert(ss.set(0, "Hello"));
	Sequence<string> ss2(ss);
	ss2.swap(ss);
	ss2 = ss;
	assert(subsequence(ss, ss2) == 0);
	assert(subsequence(si, si) == -1);
	interleave(ss, ss2, ss);
	interleave(si, si, si);
}

class Coord
{
public:
	Coord(int r, int c) : m_r(r), m_c(c) {}
	Coord() : m_r(0), m_c(0) {}
	double r() const { return m_r; }
	double c() const { return m_c; }
private:
	double m_r;
	double m_c;
};


int main()
{
	test();
	cout << "Passed all tests" << endl;
}
