#include <iostream>
#include<string>
#include<ctype.h>
using namespace std;
//the operator stack class (character class).
//------------------------------------------------------------------------------------------
class OperatorStk
{
public:
	//just prototypes :)
	OperatorStk(int);
	~OperatorStk();
	bool is_empty();
	bool is_full();
	void push(char);
	char pop();
	char peak();
	int stack_size();
	void display();
	void delete_all();
private:
	//the size of the dynamic stack array.
	int maxSize;
	//the pointer on the top item of the stack array.
	int topPointer;
	//the stack array pointer.
	char* stackItems;
};

//the operand stack class (integer class).
//------------------------------------------------------------------------------------------
class OperandStk
{
public:
	//just prototypes :)
	OperandStk(int);
	~OperandStk();
	bool is_empty();
	bool is_full();
	void push(int);
	int pop();
	int peak();
	int stack_size();
	void display();
	void delete_all();
private:
	//the size of the dynamic stack array.
	int maxSize;
	//the pointer on the top item of the stack array.
	int topPointer;
	//the stack array pointer.
	int* stackItems;
};

//----------------------------------------------------------------------------------
//functions prototypes only.
string input();
string space_deleter(string);
string infix_to_postfix(string);
int evaluate(string);
int calculate(int, int, char);
int percedence(char);
bool isOperator(char);
//------------------------------------------------------------------------------------------

//the main function of the project.
int main()
{
	/*
	the expressions strings,
	infix for the input string.
	postfix is the result string.
	*/
	string infix, postfix;
	int finalResult;//for the final result value after evaluation.
	infix = input();//calling input function for input.
	postfix = infix_to_postfix(infix);//calling the converting function.
	finalResult = evaluate(postfix);//assigning the final value of the result.


	cout << postfix << endl;//the output postfix.
	cout << "the result is :" << finalResult << endl;//the output result.
	system("pause");
	return 0;
}

//the operator stack class methods implimentation (integer class).
//------------------------------------------------------------------

//constructor for the class with param. for the stack array size.
OperatorStk::OperatorStk(int size)
{
	topPointer = -1;
	maxSize = size;
	stackItems = new char[size];
}
//destructor for deleting the dynamicly allocated array.
OperatorStk::~OperatorStk()
{
	topPointer = -1;
	delete[]stackItems;
	stackItems = NULL;
}
//class function for checking if the stack is empty.
bool OperatorStk::is_empty()
{
	if (topPointer < 0)
		return 1;
	return 0;
}
//class function for checking if the stack is full.
bool OperatorStk::is_full()
{
	if (topPointer == maxSize - 1)
		return 1;
	return 0;
}
//class function for adding character to the stack top.
void OperatorStk::push(char push)
{
	if (is_full())
	{
		cout << "the stack is full\n";
		return;
	}
	topPointer++;
	stackItems[topPointer] = push;
}
//class function for returning the character on the top of stack then deleting it.
char OperatorStk::pop()
{
	if (is_empty())
	{
		cout << "the stack is empty\n";
		return -1;
	}
	char temp = stackItems[topPointer];
	topPointer--;
	return temp;
}
//class function for only returning the character on the top of stack.
char OperatorStk::peak()
{
	if (is_empty())
	{
		cout << "the stack is empty\n";
		return -1;
	}
	char temp = stackItems[topPointer];
	return temp;
}
//class function for returning the stack size.
int OperatorStk::stack_size()
{
	return topPointer + 1;
}
//class function for deleting all items once.
void OperatorStk::delete_all()
{
	topPointer = -1;
}
//class function for display all items.
void OperatorStk::display()
{
	if (is_empty())
	{
		is_empty();
		return;
	}
	else
		for (size_t i = 0; i <= topPointer; i++)
		{
			cout << stackItems[i] << endl;
		}
}


//the operator stack class methods implimentation (integer class).
//-----------------------------------------------------------------------

//constructor for the class with param. for the stack array size.
OperandStk::OperandStk(int size)
{
	topPointer = -1;
	maxSize = size;
	stackItems = new int[size];
}
//destructor for deleting the dynamicly allocated array.
OperandStk::~OperandStk()
{
	topPointer = -1;
	delete[]stackItems;
	stackItems = NULL;
}
//class function for checking if the stack is empty.
bool OperandStk::is_empty()
{
	if (topPointer < 0)
		return 1;
	return 0;
}
//class function for checking if the stack is full.
bool OperandStk::is_full()
{
	if (topPointer == maxSize - 1)
		return 1;
	return 0;
}
//class function for adding integer to the stack top.
void OperandStk::push(int push)
{
	if (is_full())
	{
		cout << "the stack is full\n";
		return;
	}
	topPointer++;
	stackItems[topPointer] = push;
}
//class function for returning the integer on the top of stack then deleting it.
int OperandStk::pop()
{
	if (is_empty())
	{
		cout << "the stack is empty\n";
		return -1;
	}
	int temp = stackItems[topPointer];
	topPointer--;
	return temp;
}
//class function for only returning the integer on the top of stack.
int OperandStk::peak()
{
	if (is_empty())
	{
		cout << "the stack is empty\n";
		return -1;
	}
	int temp = stackItems[topPointer];
	return temp;
}
//class function for returning the stack size.
int OperandStk::stack_size()
{
	return topPointer + 1;
}
//class function for deleting all items once.
void OperandStk::delete_all()
{
	topPointer = -1;
}
//class function for display all items.
void OperandStk::display()
{
	if (is_empty())
	{
		is_empty();
		return;
	}
	else
		for (size_t i = 0; i <= topPointer; i++)
		{
			cout << stackItems[i] << endl;
		}
}


// all functions implimentation
//----------------------------------------------------

//function for taking the string input from user:
//return string infix.
string input()
{
	string infix = "";
	cout << "enter the infix expresion \n";
	getline(cin, infix);
	return space_deleter(infix);
}
//function for removing any spaces or taps in the infix string:
//param string the infix taken from user (raw infix).
//return string the infix without spaces or taps.
string space_deleter(string input)
{
	int size = input.size();//the size of the string infix.
	string infix_no_space = "";
	/*
	for loop to handle the space problem
	by skipping every space in the input string infix.*/
	for (int i = 0; i < size; i++)
	{
		if (input[i] == ' ' || input[i] == '	')
			continue;
		infix_no_space += input[i];
	}
	return infix_no_space;
}
//function for converting from infix to postfix:
//param string the infix without spaces or taps.
//return string the postfix expression.
string infix_to_postfix(string infix)
{
	string postfix = "";//string for saving the postfix exp.
	int size_of_infix = infix.size();//getting the size of the infix string.
	OperatorStk operatorStack(size_of_infix);//creating an object and sending the size of the stack array.
	/*first step in the algorithm is adding ')' to the infix string,
	* then pushing '(' to the stack.
	*/
	infix += ')';//1
	operatorStack.push('(');//2
	/*third step which is repeatedly scaning the infix string we have and doing one of two operations:
	push to the stack array if it is operator.
	add to the postfix string if it is operand or alphabet.
	and there is some conditions need to be done first which is shown in the next for loop.*/
	for (int i = 0; i < size_of_infix + 1; i++)
	{
		if (isOperator(infix[i]))
		{
			if (infix[i] == '(')
				operatorStack.push('(');
			else if (infix[i] == ')')
			{
				while (operatorStack.peak() != '(')
				{
					postfix += operatorStack.pop();
				}
				operatorStack.pop();
			}
			else
			{
				while (percedence(operatorStack.peak()) >= percedence(infix[i]) && operatorStack.peak() != '(')
					postfix += operatorStack.pop();
				operatorStack.push(infix[i]);
			}
		}
		
		else
		{
			while (!isOperator(infix[i]))
			{
				postfix += infix[i];
				i++;
			}
			postfix += ' ';
			i--;
		}
	}
	return postfix;
}
//function for evaluating the postfix expression:
//param string the postfix expression.
//return int the result value.
int evaluate(string postfix)
{
	OperandStk operandStack(postfix.size());//creating 
	string term = "";
	int operand1, operand2;
	for (size_t i = 0; i < postfix.size(); i++)
	{
		if (((postfix[i] - '0') >= 0 && (postfix[i] - '0') <= 9))  // ((postfix[i] - '0') >= 0 && (postfix[i] - '0') <= 0)
		{
			term += postfix[i];
		}
		else if (postfix[i] == ' ')
		{
			operandStack.push(stoi(term));
			term = "";
		}
		else if (isOperator(postfix[i]))
		{
			if (operandStack.stack_size() < 2)
			{
				cout << "not valid expression\n";
				system("pause");
				exit(0);
			}
			operand2 = operandStack.pop();
			operand1 = operandStack.pop();
			operandStack.push(calculate(operand1, operand2, postfix[i]));
		}
		else
		{
			cout << "not valid expression\n";
				system("pause");
				exit(0);
		}
	}
	int result = operandStack.pop();
	if (!operandStack.is_empty())
	{
		cout << "unknown error :( plz restart\n";
		return -1;
	}
	else
		return result;
}
//function for calculating the current operation:
//param:1 int operand 1.
//param:2 int operand 2.
//param:3 char operator.
//return int the result value.
int calculate(int opr1, int opr2, char oprat)
{
	switch (oprat)
	{
	case'+':return opr1 + opr2;
		break;
	case'-':return opr1 - opr2;
		break;
	case'*':return opr1 * opr2;
		break;
	case'/':
	{
		if (opr2 == 0)
		{
			cout << "error: can not divide by zero" << endl;
			system("pause");
			exit(0);
		}
		else
			return opr1 / opr2;
	}
	case'%':return opr1 % opr2;
		break;
	case'^':return pow(opr1, opr2);
		break;
	default:
	{
		cout << "unknown error :( plz restart\n";
		system("pause");
		exit(0);
	}
	break;
	}
}
//function for checking the percdence of each operator:
//param char the operator.
//return int the percedence order from 0 to 3 where 3 is the highest.
int percedence(char input_test)
{
	if (input_test == '^')
		return 3;
	else if (input_test == '*' || input_test == '/' || input_test == '%')
		return 2;
	else if (input_test == '-' || input_test == '+')
		return 1;
	else
		return 0;
}
//function for checking if is operator or not:
//param char the passed character.
//return bool true or false.....
bool isOperator(char input_char)
{
	switch (input_char)
	{
	case'+':return 1;
	case'-':return 1;
	case'*':return 1;
	case'/':return 1;
	case'%':return 1;
	case'^':return 1;
	case'(':return 1;
	case')':return 1;
		break;
	default:
		return 0;
		break;
	}
}
//the end of the code hope u like it and give us the full mark.