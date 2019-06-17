#include <iostream>
#include <string>
#include <cctype>
#include <stack>
#include <cassert>
using namespace std;

//function declaration
int precedence(char c);

//evaluate function
int evaluate(string infix, string& postfix, bool& result)
{
	postfix = ""; //empty postfix
	stack <char> charStack;
	char first, last = ' ';
	char prev = ' ';  //initialize characters used in the program
	for (int k = infix.size() - 1; k >= 0; k--)  //find the last character
	{
		if (infix[k] != ' ')
		{
			last = infix[k];
			break;
		}
	}
	for (size_t n = 0; n < infix.size(); n++) //find the first character
	{
		if (infix[n] != ' ')
		{
			first = infix[n];
			break;
		}
	}

	if (last != 'T' && last != 'F'&& last != ')') //end with illegal characters
		return 1;
	if (first != 'T'&& first != 'F'&& first != '(' && first != '!') //begin with illegal characters
		return 1;
	for (size_t i = 0; i < infix.size(); i++) //loop throught the infix string
	{
		prev = ' ';
		switch (infix[i]) //examine each character
		{
		case 'T':
		case 'F':
			for (int j = i - 1; j >= 0; j--) //find the previous character
			{
				if (infix[j] != ' ')
				{
					prev = infix[j];
					break;
				}
			}
			if (prev == 'T' || prev == 'F' || prev == ')') //decide if it is valid
				return 1;
			postfix += infix[i];  //add to the postfix
			break;
		case '(':
			for (int j = i - 1; j >= 0; j--) //find the previous character
			{
				if (infix[j] != ' ')
				{
					prev = infix[j];
					break;
				}
			}
			if (prev == 'T' || prev == 'F' || prev == ')')  //decide if it is valid
				return 1;
			charStack.push('('); //add to the stack
			break;
		case ')':
			for (int j = i - 1; j >= 0; j--) //find the previous character
			{
				if (infix[j] != ' ')
				{
					prev = infix[j];
					break;
				}
			}
			if (prev == '!' || prev == '&' || prev == '^' || prev == '(') //decide if it is valid
				return 1;
			while (charStack.top() != '(')  //when in the brackets
			{
				char top = charStack.top(); 
				postfix += top;          
				charStack.pop();       //add the stack to the postfix
				if (charStack.empty())  //if no '('
				{
					return 1;
				}
			}
			charStack.pop();
			break;

		case '&':
		case '^':
			for (int j = i - 1; j >= 0; j--)  //find the previous character
			{
				if (infix[j] != ' ')
				{
					prev = infix[j];
					break;
				}
			}
			if (prev == '!' || prev == '&' || prev == '^' || prev == '(') //decide if it is valid
				return 1;
			while (!charStack.empty()
				&& (charStack.top() != '(')
				&& (precedence(infix[i]) <= precedence(charStack.top()))
				)  //if could be added to the postfix
			{
				postfix += charStack.top();
				charStack.pop();
			}
			charStack.push(infix[i]);
			break;
		case '!':
			for (int j = i - 1; j >= 0; j--) //find the previous character
			{
				if (infix[j] != ' ')
				{
					prev = infix[j];
					break;
				}
			}
			if (prev == 'T' || prev == 'F' || prev == ')') //decide if it is valid
				return 1;
			charStack.push(infix[i]);
			break;
		case ' ':
			break;
		default:
			return 1;
		}
	}
	while(!charStack.empty())  //push remaining characters
	{
		postfix += charStack.top();
		charStack.pop();
	}
	cerr << postfix << endl;
	//get the postfix
	stack <char> postStack; 
	for (size_t i = 0; i < postfix.size(); i++) //loop through characters
	{
		char ch = postfix[i];
		if (ch == 'T' || ch == 'F') //if it is operand
		{
			postStack.push(ch); //push to the stack
		}
		else //if it is operator
		{
			char operand1, operand2;
			switch (ch)  //find the situation and do the operations
			{
			case '!':
				operand1 = postStack.top();  
				postStack.pop();
				if (operand1 == 'T')
				{
					postStack.push('F');
				}
				else
				{
					postStack.push('T');
				}
				break;
			case '&':
				operand2 = postStack.top();
				postStack.pop();
				operand1 = postStack.top();
				postStack.pop();
				if (operand1 == 'T' && operand2 == 'T')
				{
					postStack.push('T');
				}
				else
				{
					postStack.push('F');
				}
				break;
			case '^':
				operand2 = postStack.top();
				postStack.pop();
				operand1 = postStack.top();
				postStack.pop();
				if ((operand1 == 'T' && operand2 == 'F' )||( operand1 == 'F' && operand2 == 'T'))
				{
					postStack.push('T');
				}
				else
				{
					postStack.push('F');
				}
				break;
			default:
				return 1;
			}
	    }
	}
	if (postStack.top() == 'T')  //conversion
	{
		result = true;
	}
	else if (postStack.top() == 'F')
	{
		result = false;
	}
	else
	{
		return 1;
	}
	return 0;
}

//implementation of precedence
int precedence(char c)  
{
	switch (c)
	{
	case '!':
		return 3;
		break;
	case '&':
		return 2;
		break;
	case '^':
		return 1;
		break;
	default:
		return -1;
	}
}

int main()
{
	string pf;
	bool answer;
	assert(evaluate("T^ F", pf, answer) == 0 && pf == "TF^"  &&  answer);
	assert(evaluate("T^", pf, answer) == 1);
	assert(evaluate("F F", pf, answer) == 1);
	assert(evaluate("TF", pf, answer) == 1);
	assert(evaluate("()", pf, answer) == 1);
	assert(evaluate("()T", pf, answer) == 1);
	assert(evaluate("T(F^T)", pf, answer) == 1);
	assert(evaluate("T(&T)", pf, answer) == 1);
	assert(evaluate("(T&(F^F)", pf, answer) == 1);
	assert(evaluate("T|F", pf, answer) == 1);
	assert(evaluate("", pf, answer) == 1);
	assert(evaluate("(!!!!)&F", pf, answer) == 1);
	assert(evaluate("(!!!!F&F)", pf, answer) == 0 && pf == "F!!!!F&" && !answer);
	assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0 && pf == "FF!TF&&^" && !answer);
	assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
	assert(evaluate("((T))", pf, answer) == 0 && pf == "T"  &&  answer);
	assert(evaluate(" (!F  & T)& !F  ", pf, answer) == 0 && pf == "F!T&F!&" && answer);
	assert(evaluate("T", pf, answer) == 0 && pf == "T" && answer);
	assert(evaluate("(F)", pf, answer) == 0 && pf == "F" && !answer);
	assert(evaluate("T^(F) ", pf, answer) == 0 && pf == "TF^" && answer);
	assert(evaluate("T ^ !F", pf, answer) == 0 && pf == "TF!^" && !answer);
	assert(evaluate("!(T&F) ", pf, answer) == 0 && pf == "TF&!" && answer);
	assert(evaluate("!T&F", pf, answer) == 0 && pf == "T!F&" && !answer);
	assert(evaluate("T^F&F", pf, answer) == 0 && pf == "TFF&^" && answer);
	assert(evaluate("T&!(F^T&T^F)^!!!(F&T&F)", pf, answer) == 0 && pf == "TFTT&^F^!&FT&F&!!!^" && answer);
	assert(evaluate("(T^F&F)^T&!F&!!!!!!F", pf, answer) == 0 && pf == "TFF&^TF!&F!!!!!!&^" && answer);
	assert(evaluate("T^", pf, answer) == 1);
	assert(evaluate("T&!F", pf, answer) == 0);
	assert(evaluate("T^!!F", pf, answer) == 0);
	assert(evaluate("T&(^F)", pf, answer) == 1);
	assert(evaluate("T&^F", pf, answer) == 1);
	assert(evaluate("T^(FF)", pf, answer) == 1);
	assert(evaluate("T&!(F^T&T^F)^!!!(F&T&FF)", pf, answer) == 1);
	assert(evaluate("T&!T(F^T&T^F)^!!!(F&T&F)", pf, answer) == 1);
	assert(evaluate("T&!(F^T&T^F)F^!!!(F&T&F)", pf, answer) == 1);
	assert(evaluate("T&(!F", pf, answer) == 1);
	assert(evaluate("T&!F)", pf, answer) == 1);
	assert(evaluate("T&(!F))", pf, answer) == 1);
	assert(evaluate("!F", pf, answer) == 0 && answer);
	assert(evaluate("dsvfwerg", pf, answer) == 1 && answer);
	cout << "Passed all tests" << endl;
}