#ifndef HISTORY_H
#define HISTORY_H

class History
{
public:
	History(int nRows, int nCols);
	bool record(int r, int c);
	void display() const;
	~History();
private:
	int **numberOfKill;
	int m_row;
	int m_col;
};


#endif
