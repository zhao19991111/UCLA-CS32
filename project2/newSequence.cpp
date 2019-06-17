#include "newSequence.h"
#include <string>
#include <iostream>

Sequence::Sequence(int size)
	:m_size(0),
	 m_maxsize(size)
{
	seq = new ItemType[size];
}

Sequence::~Sequence()
{
	delete [] seq;
}

Sequence::Sequence(const Sequence &other)
	:m_size(other.m_size), 
	 m_maxsize(other.m_maxsize)
{
	seq = new ItemType[m_maxsize];
	for (int i = 0; i < m_size; i++)
	{
		seq[i] = other.seq[i];
	}
}

Sequence &Sequence::operator=(const Sequence &other)
{
	if (this != &other)
	{
		Sequence temp(other);
		swap(temp);
	}
	return *this;
}

bool Sequence::empty() const
{
	return (m_size == 0);
}

int Sequence::size() const
{
	return m_size;
}

int Sequence::insert(int pos, const ItemType& value)
{
	if (0 <= pos && pos <= size() && size() < m_maxsize)
	{
		if (size() > 0)
		{
			for (int i = size(); i > pos; i--)
			{
				seq[i] = seq[i - 1];
			}
			seq[pos] = value;
			m_size++;
			return pos;
		}
		else
		{
			seq[0] = value;
			m_size++;
			return 0;
		}
	}
	else
	{
		return -1;
	}
}

int Sequence::insert(const ItemType& value)
{
	if (size() < m_maxsize)
	{
		for (int i = 0; i < size(); i++)
		{
			if (value <= seq[i])
			{
				insert(i, value);
				return i;
			}
		}
		int p = size();
		insert(p, value);
		return p;
	}
	else
	{
		return -1;
	}
}

bool Sequence::erase(int pos)
{
	if (0 <= pos && pos < size())
	{

		if (pos < (size() - 1))
		{
			for (int i = pos; i < size() - 1; i++)
			{
				seq[i] = seq[i + 1];
			}
		}
		else
		{
			ItemType null = ItemType();
			seq[pos] = null;
		}
		m_size--;
		return true;
	}
	else
	{
		return false;
	}
}

int Sequence::remove(const ItemType& value)
{
	int num = 0;
	for (int i = 0; i < m_maxsize; i++)
	{
		if (seq[i] == value)
		{
			if (erase(i))
			{
				i--;
				num++;
			}
		}
	}
	return num;
}

bool Sequence::get(int pos, ItemType& value) const
{
	if (0 <= pos && pos < size())
	{
		value = seq[pos];
		return true;
	}
	else
	{
		return false;
	}
}

bool Sequence::set(int pos, const ItemType& value)
{
	if (0 <= pos && pos < size())
	{
		seq[pos] = value;
		return true;
	}
	else
	{
		return false;
	}
}

int Sequence::find(const ItemType& value) const
{
	for (int i = 0; i < m_maxsize; i++)
	{
		if (seq[i] == value)
		{
			return i;
		}
	}
	return -1;
}

void Sequence::swap(Sequence& other)
{
	ItemType *temp;
	int tempSize;

	temp = seq;
	seq = other.seq;
	other.seq = temp;

	tempSize = m_size;
	m_size = other.m_size;
	other.m_size = tempSize;

	tempSize = m_maxsize;
	m_maxsize = other.m_maxsize;
	other.m_maxsize = tempSize;
}