
#include <iostream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <string>
#include <cassert>
#include <sstream>
#include <vector>

using namespace std;

//constant//

const int MAXCHAR = 8; //number of chars in each segment
const char zero = '\0';

//structure declaration//

struct HashNode
{
	int offset; //the offset
	char m_value[MAXCHAR]; //the value
	HashNode* m_next; //next Node
};


//function declaration//

void createDiff(istream& fold, istream& fnew, ostream& fdiff);
bool applyDiff(istream& fold, istream& fdiff, ostream& fnew);
string readFile(istream& file); //read the file into a string
int compareChar(const string l, const char r[], int len_r); 
HashNode* insertNewPos(vector<HashNode*> &table, vector<HashNode*> &tableTail, int pos);
int small(int a, int b);
bool getInt(istream& inf, int& n);
bool getCommand(istream& inf, char& cmd, int& length, int& offset);


//function implementation//

string readFile(istream& file) //read file from txt to string
{
	char temp;
	string str = "";
	while (file.get(temp)) //not to the end of the file
	{
		str += temp;
	}
	return str;
}

int compareChar(const string l, const char r[], int len_r) //compare a string to a char array
{
	if (l.length() <= len_r)
		for (int i = 0; i < l.length(); i++)
		{
			if (l[i] > r[i])
				return 1;
			if (l[i] < r[i])
				return -1;
		}
	else
		for (int i = 0; i < len_r; i++)
		{
			if (l[i] > r[i])
				return 1;
			if (l[i] < r[i])
				return -1;
		}
	return 0;
}

HashNode* insertNewPos(vector<HashNode*> &table, vector<HashNode*> &tableTail, int pos) // insert a new input into the table
{
	if (table[pos] == nullptr) //if no previous elements
	{
		table[pos] = new HashNode; //create a new node
		tableTail[pos] = table[pos];
	}
	else
	{ 
		tableTail[pos]->m_next = new HashNode; //insert a new node in the end
		tableTail[pos] = tableTail[pos]->m_next;
	}
	return tableTail[pos];
}

int small(int a, int b)  // return the smaller one between two
{
	if (a > b)
		return b;
	else
		return a;
}

bool getInt(istream& inf, int& n) //get the interger from istream
{
	char ch;
	if (!inf.get(ch) || !isascii(ch) || !isdigit(ch))
		return false;
	inf.unget();
	inf >> n;
	return true;
}

bool getCommand(istream& inf, char& cmd, int& length, int& offset) //get the command from istream
{
	if (!inf.get(cmd))
	{
		cmd = 'x';  // signals end of file
		return true;
	}
	char ch;
	switch (cmd)
	{
	case 'A':
		return getInt(inf, length) && inf.get(ch) && ch == ':'; //set the length and return if command is valid
	case 'C':
		return getInt(inf, length) && inf.get(ch) && ch == ',' && getInt(inf, offset);//set the length and the offset and return if command is valid
	case '\r':
	case '\n':
		return true;
	}
	return false;
}

void createDiff(istream& fold, istream& fnew, ostream& fdiff)
{
	string oldStr = readFile(fold); //read the file from fold
	string newStr = readFile(fnew); //read the file from fnew
	vector<HashNode*> Tab (150, nullptr); //create a hashtable for different characters
	vector<HashNode*> TabTail(150, nullptr); //keep track of the tail of each linked list
	string temp = ""; //temporary storage of substrings
	int i; //the position in oldStr
	for (i = 0; i < oldStr.length()-MAXCHAR; i++) //loop through the oldStr
	{
		int pos = oldStr[i]-zero;
		temp = oldStr.substr(i, MAXCHAR);
		HashNode* insertPos = insertNewPos(Tab, TabTail, pos); //set a new Node in approprite position
		if (insertPos != nullptr)
		{
			insertPos->offset = i; //set the offset
			insertPos->m_next = nullptr;
			for (int j = 0; j < MAXCHAR; j++) //set the char sequence
				insertPos->m_value[j] = temp[j];
		}
	}
	for (int s = 0; s < newStr.length()-MAXCHAR; s++)
	{
	    temp = newStr.substr(s, MAXCHAR); //read the MAXHCHAR segment
		int pos = temp[0]-zero; //find the position
		HashNode* current = Tab[pos]; //point to the position
		int length = 0, temp_length = 0, m_offset = 0;
		while (current != nullptr) //search through the table to the end
		{
			if (compareChar(temp, current->m_value, MAXCHAR) == 0 ) //if there is a match
			{
				temp_length = 0;
				int max = small(oldStr.length() - current->offset, newStr.length() - s); //find the maximum length that could be copied
				for (int v = 0; v < max; v++)
				{
					if (oldStr[current->offset + v] == newStr[s + v]) //if the next chars are still the same
						temp_length++; // increase the length to copy
					else
						break;
				}
				if (temp_length > length) // choose the largest one and set the length and offset
				{
					length = temp_length;
					m_offset = current->offset;
				}
			}
			current = current->m_next;
		}
		if (length!=0) //there are elements to copy
		   fdiff << "C" << length << "," << m_offset;
		else //no element copied
		{
			int v = 0;
			for (v = s; v < newStr.length(); v++) //find the next segment that could be copied
			{
				string n_temp= newStr.substr(v, MAXCHAR); //repeat what is done above
				int n_pos = n_temp[0] - zero;
				HashNode* n_current = Tab[n_pos];
				bool isOver = false;
				while (n_current != nullptr)
				{
					if (compareChar(n_temp, n_current->m_value, MAXCHAR) == 0) //if the next segment is found
						isOver = true; //end the search
					n_current = n_current->m_next;
				}
				if (isOver && v < (newStr.length() - MAXCHAR)) //if the string to add is not too close to the end 
					break; //stop there
			}
			length = v - s ; //the length to be added
			string Toadd = newStr.substr(s, length); // the string to be added
			fdiff << "A" << length << ":" << Toadd; // write in the file
		}
		s += length-1; //move s to the new position
	}
}

bool applyDiff(istream& fold, istream& fdiff, ostream& fnew)
{
	int temp_length = 0, temp_offset = 0;
	char signal= zero;
	string oldStr = readFile(fold);
	while (signal != 'x') //when the istream isn't ended
	{
		temp_length = -1;
		temp_offset = -1;
		if (getCommand(fdiff, signal, temp_length, temp_offset)) //get command and set the length and offset
		{
			if (signal == 'C')//case 'C'
			{
				fnew << oldStr.substr(temp_offset, temp_length); //copy from the old file to new file
			}
			else if (signal == 'A')//case 'A'
			{
				for (int i = 0; i < temp_length; i++) //add the new characters
				{
					char c;
					fdiff.get(c);
					fnew << c;
				}
			}
			else if (signal == '\n' || signal == '\r')//change the line if there is any instruction on that
			{
				fnew << signal;
			}
		}
		else
			return false;
	}
	return true;
}


//main routine//

int main() 
{   
	
	ifstream f1("C:/Users/zhao1/OneDrive/Desktop/UCLA/2019 spring/CS32/project 4/smallmart1.txt");
	if (!f1)		        // Did opening the file fail?
	{
		cerr << "Error: Cannot open the file! " << endl;
		return -100;
	}
	ifstream f2("C:/Users/zhao1/OneDrive/Desktop/UCLA/2019 spring/CS32/project 4/smallmart2.txt");
	if (!f2)		        // Did opening the file fail?
	{
		cerr << "Error: Cannot open the file! " << endl;
		return -100;
	}
	int i;
	cout << "choose action (1: createDiff, 2: applyDiff, 3: compare Old&New):"; //choose the action you want to perform 
	cin >> i;
	if (i == 1)
	{
		ofstream path("C:/Users/zhao1/OneDrive/Desktop/UCLA/2019 spring/CS32/project 4/methods.txt");
		createDiff(f1, f2, path);
	}
	else if (i == 2)
	{
		ifstream method("C:/Users/zhao1/OneDrive/Desktop/UCLA/2019 spring/CS32/project 4/methods.txt");
		ofstream result("C:/Users/zhao1/OneDrive/Desktop/UCLA/2019 spring/CS32/project 4/results.txt");
		applyDiff(f1, method, result);
	}
	else
	{
		ifstream result2("C:/Users/zhao1/OneDrive/Desktop/UCLA/2019 spring/CS32/project 4/results.txt");
		string s1 = readFile(result2);
		string s2 = readFile(f2);
		if (s1 == s2)
			cerr << "passed the test";
		else
			cerr << "failed";
	}
}