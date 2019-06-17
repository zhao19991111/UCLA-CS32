#ifndef SIDE_H
#define SIDE_H
#include <string>
class Board;
enum Side { NORTH, SOUTH};
const int NSIDES = 2;
const int POT = 0;
const int MAXV = 99999; //default maximum value
inline
Side opponent(Side s)
{
	return Side(NSIDES - 1 - s);
}
int position(Side s, int hole, int nHoles);
void chooseSmartMove(Side s, Side m_s, const Board& b, int& bestHole, int& value, int layer = 7); //choose the move that will result in the largest pot difference

#endif
