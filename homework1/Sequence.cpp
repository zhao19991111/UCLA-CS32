#include "Sequence.h"
#include <iostream>
Sequence::Sequence()
{
	head = nullptr;
	tail = nullptr;
	m_size = 0;
}

Sequence::~Sequence()
{
	Node *p = head;
	while (head != nullptr)
	{
		head = head->next;
		delete p;
		p = head;
	}
}


Sequence::Sequence(const Sequence &other)
{
	head = nullptr;
	tail = nullptr;
	m_size = 0;
	Node *p = other.head;
	int n = 0;
	while (p != nullptr)
	{
		insert(n, p->data);
		n++;
		p = p->next;
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
	if (m_size == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Sequence::size() const
{
	return m_size;
}

int Sequence::insert(int pos, const ItemType& value)
{
	if (pos >= 0 && pos <= size()) //can be inserted
	{
		Node *q = new Node;
		q->data = value;
		int n = 0;
		if (pos == 0)
		{
			if (head == nullptr && tail == nullptr)
			{
				q->next = nullptr;
				q->prev = nullptr;
				head = q;
				tail = q;
			}
			else
			{
				q->next = head;
				q->prev = nullptr;
				head = q;
			}
		}
		else if (pos == size())
		{
			q->prev = tail;
			q->next = nullptr;
			tail->next = q;
			tail = q;
		}
		else
		{
			Node *p = head;
			while (n != pos)
			{
				p = p->next;
				n++;
			}
			p->prev->next = q;
			q->prev = p->prev;
			p->prev = q;
			q->next = p;
		}
		m_size++;
		return pos;
	}
	else //cannot be inserted
	{
		return -1; 
	}
}

int Sequence::insert(const ItemType& value)
{
	Node* p = head;
	int n = 0;
	if (p != nullptr)
	{
		while (value > p->data)
		{
			n++;
			p = p->next;
			if (p == nullptr)
			{
				break;
			}
		}
	}
    insert(n, value);
	return n;
}

bool Sequence::erase(int pos)
{
	if (0 <= pos && pos < size()) //can be erased
	{
		Node *p;
		int n = 0;
		if (pos == 0)
		{
			p = head;
			p = p->next;
			delete head;
			head = p;
			if( head == nullptr)
			{
				tail = nullptr;
			}
		}
		else if (pos == size() - 1)
		{
			p = tail;
			p = p->prev;
			delete tail;
			tail = p;
			if( tail == nullptr)
			{ 
				head = nullptr;
			}
		}
		else
		{
			p = head;
			while (n != pos)
			{
				n++;
				p = p->next;
			}
			p->prev->next = p->next;
			p->next->prev = p->prev;
			delete p;
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
	Node* p = head;
	int t = 0;
	int n = 0;
	while (p != nullptr)
	{
		if (p->data == value)
		{
			p = p->next;
			if (erase(n))
			{
				t++;
			}
		}
		else
		{
			n++;
			p = p->next;
		}
	}
	return t;
}

bool Sequence::get(int pos, ItemType& value) const
{
	int n = 0;
	Node *p = head;
	if (0 <= pos && pos < size()) //can be gotten
	{
		while (n != pos)
		{
			n++;
			p = p->next;
		}
		value = p->data;
		return true;
	}
	else
	{
		return false;
	}
}

bool Sequence::set(int pos, const ItemType& value)
{
	int n = 0;
	Node *p = head;
	if (0 <= pos && pos < size())  //can be set
	{
		while (n != pos)
		{
			n++;
			p = p->next;
		}
		p->data = value;
		return true;
	}
	else
	{
		return false;
	}
}

int Sequence::find(const ItemType& value) const
{
	Node *p = head;
	int n = 0;
	if (p == nullptr)
	{
		std::cerr << "here";
		return -1;
	}
	else
	{
		while (p->data != value)
		{
			n++;
			p = p->next;
			if (p == nullptr)
			{
				return -1;
			}
		}
		return n;
	}
}

void Sequence::swap(Sequence& other)
{
	int temp = m_size;
	m_size = other.m_size;
	other.m_size = temp;  //exchange size()

	Node *p = head;
	Node *q = tail;
	head = other.head;
	tail = other.tail;
	other.head = p;
	other.tail = q; //exchange linked list

}

void Sequence::dump() const
{
	Node* p = head;
	while (p != nullptr)
	{
		std::cerr << p->data;
		p = p->next;
	}
}

int subsequence(const Sequence& seq1, const Sequence& seq2)
{
	if (&seq1 == &seq2) //if seq1 and seq2 are the same 
	{
		return 0;
	}
	else if (seq2.size() == 0 || seq2.size() > seq1.size())
	{
		return -1;
	}
	else
	{
		ItemType x, y;

		for (int i = 0; i < (seq1.size() - seq2.size() + 1); i++)
		{
			seq2.get(0, y);
			seq1.get(i, x);
			if (x == y)
			{
				int count = 0;
				for (int j = 0; j < seq2.size(); j++)
				{
					seq2.get(j, y);
					seq1.get(i + j, x);
					if (x == y)
					{
						count++;
					}
					else
					{
						break;
					}
				}
				if (count == seq2.size())
				{
					return i;
				}
			}
		}
		return -1;
	}
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
	ItemType x, y;
	Sequence s;  //temporary storage for result
	if (seq1.size() == 0 && seq2.size() == 0) 
		{
			result = Sequence();
		}
		else if (seq1.size() == 0)
		{
			for (int i = 0; i < seq2.size(); i++)
			{
				seq2.get(i, y);
				s.insert(i, y);
			}
			result = s;
		}
		else if (seq2.size() == 0)
		{
			for (int i = 0; i < seq1.size(); i++)
			{
				seq1.get(i, x);
				s.insert(i, x);
			}
			result = s;
		}
		else
		{
			if (seq1.size() == seq2.size())
			{
				for (int i = 0; i < seq1.size(); i++)
				{
					seq1.get(i, x);
					seq2.get(i, y);
					s.insert(2 * i, x);
					s.insert(2 * i + 1, y);
				}
				result = s;
			}
			else if (seq1.size() < seq2.size())
			{
				for (int i = 0; i < seq1.size(); i++)
				{
					seq1.get(i, x);
					seq2.get(i, y);
					s.insert(2 * i, x);
					s.insert(2 * i + 1, y);
				}
				for (int j = seq1.size(); j < seq2.size(); j++)
				{
					seq2.get(j, y);
					s.insert(seq1.size() + j, y);
				}
				result = s;
			}
			else
			{
				for (int i = 0; i < seq2.size(); i++)
				{
					seq1.get(i, x);
					seq2.get(i, y);
					s.insert(2 * i, x);
					s.insert(2 * i + 1, y);
				}
				for (int j = seq2.size(); j < seq1.size(); j++)
				{
					seq1.get(j, y);
					s.insert(seq2.size() + j, y);
				}
				result = s;
			}
		}

}