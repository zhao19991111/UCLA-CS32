
#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	Sequence s;
	Sequence o;
	assert(s.empty() == true);
	s.insert(0, "a");
	s.insert(1, "b");
	s.insert(2, "c");
	s.insert(3, "b");
	s.insert(4, "e"); //size()==5
	assert(s.size() == 5);
	assert(s.remove("b") == 2);
	assert(s.size() == 3);
	string x;
	assert(s.get(0, x) && x == "a");
	assert(s.get(1, x) && x == "c");
	assert(s.get(2, x) && x == "e");
	s.insert("b");
	assert(s.get(1, x) && x == "b");
	assert(s.set(1, "j") && s.get(1, x) && x == "j");
	o = s;
	o.swap(s);
	assert(o.get(2, x) && x == "c");
	s.erase(0);
	assert(subsequence(o, s) == 1);
	s.insert("d");
	s.dump();
	cerr << endl;
	o.dump();
	cerr << endl;
	assert(subsequence(o, s) == -1);
	s.insert("k");
	Sequence k;
	interleave(s, o, k);
	k.dump();
	assert(k.find("j") == 2); //dajjcceek
	interleave(s, o, s);
	assert(s.find("j") == 2); //dajjcceek

	Sequence z;
	assert(!z.get(0, x));
	assert(!z.set(0, x));
	z.insert("a");
	z.insert("z");
	assert(z.get(1, x) && x == "z");
	Sequence a(z);
	a.insert("c");
	a.insert("i");
	a.dump();
	assert(a.get(3, x) && x == "z");
	cerr << "all test passed" << endl;
	
}
