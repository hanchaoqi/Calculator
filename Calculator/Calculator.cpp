#include "symbol_table.h"

Token_stream ts;
Symbol_table sym_table;


//For Arithmetic Calculator
double statement();
double expression();
double term();
double primary();
double declaration(char flag);
double get_sqrt();
double get_pow();
//For Logic Calculator
int a();
int b();
int c();
int d();

void calculate_A();
void calculate_L();
void clean_up_mess();
void get_help();

int main()
{
	sym_table.declare("pi", 3.1415926535,const_k);
	sym_table.declare("e", 2.7182818284, const_k);

	cout << "Welcome to our simple calculator.\nInput " << help << " get help." << endl;
begin:	cout << "Select calculator's mode(Logic calculator -- "<<flag_L<<" ,Arithmetic Calculator -- "<<flag_A<<"):" << endl;
	try
	{
		char mode;
		cin >> mode;

		switch (mode)
		{
		case flag_L:
			calculate_L();
			break;
		case flag_A:
			calculate_A();
			break;
		case help:
			get_help();
			goto begin;
		default:
			error("Invalid Input");
		}			
	}
	catch (exception &e)
	{
		cerr << "Error: " << e.what() << endl;
		keep_window_open("~~");
		return 1;
	}
	catch (...)
	{
		cerr << "unkown exception"<< endl;
		keep_window_open("~~");
		return 2;
	}
	keep_window_open();
	return 0;
}

void calculate_A()
{
	double val = 0;
	while (cin)
	try
	{
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print)
			t = ts.get();
		if (t.kind == quit)
			return;
		ts.putback(t);
		cout << result << statement() << endl;
	}
	catch (exception &e)
	{
		cerr << e.what() << endl;
		clean_up_mess();
	}
}
void calculate_L()
{
	double val = 0;
	while (cin)
	try
	{
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print)
			t = ts.get();
		if(t.kind == quit)
			return;
		ts.putback(t);
		cout << result << a() << endl;
	}
	catch (exception &e)
	{
		cerr << e.what() << endl;
		clean_up_mess();
	}
}
void clean_up_mess()
{
	ts.ignore(print);
}
void get_help()
{
	cout << "Welcome to our simple calculator." << endl; 
	cout << flag_L << " -- Logic calculator\n" << flag_A << " -- Arithmetic Calculator\n" <<help<<" -- Get Help"<< endl;
	
	cout << "In Logic calculator please enter expression using binary numbers,enter '=' end it." << endl;
	cout << "You can use '~','!','|','&','^' in expression,also you can use '(',')','{','}'.\n" << endl;

	cout << "In Arithmetic Calculator please enter expression using floating-point numbers,enter '=' end it." << endl;
	cout << "You can use '+','-','*','/','!' in expression,also you can use '(',')','{','}'." << endl;
	cout << "sqrt(x) and pow(x,y) is also avaliable." << endl;
	cout << "You can use 'let' assignment a variable and use '=' modify variable,but if you use 'const' before 'let',you can't modify it." << endl;
}

double statement()
{
	Token t = ts.get();
	switch (t.kind)
	{
	case let:
		return declaration(var_k);
	case const_k:
	{
					t = ts.get();
					if (t.kind == let)
						return declaration(const_k);
					else
						error("const error");
	}
	default:
		ts.putback(t);
		return expression();
	}
}
double expression()
{
	double left = term();
	Token t = ts.get();
	while (true)
	{
		switch (t.kind)
		{
		case '+':
			left += term();
			t = ts.get();
			break;
		case '-':
			left -= term();
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}
double term()
{
	double left = primary();
	Token t = ts.get();
	while (true)
	{
		switch (t.kind)
		{
		case '*':
			left *= primary();
			t = ts.get();
			break;
		case '/':
		{
					double right = primary();
					if (right == 0)
						error("divided zero");
					left /= right;
					t = ts.get();
					break;
		}
		case '%':
		{
					int a = narrow_cast<int>(left);
					int b = narrow_cast<int>(term());
					if (b == 0)
						error("%:divide by zero");
					left = a%b;
					t = ts.get();
					break;

		}
		default:
			ts.putback(t);
			return left;
		}
	}
}
double primary()
{
	Token t = ts.get();
	double data = 0;
	switch (t.kind)
	{
	case '(':
	{
				data = expression();
				t = ts.get();
				if (t.kind != ')')
					error("')' excepted");
				break;
	}
	case '{':
	{
				data = expression();
				t = ts.get();
				if (t.kind != '}')
					error("'}' excepted");
				break;
	}
	case number:
		data = t.value;
		break;
	case name:
	{
				 Token t1 = ts.get();
				 if (t1.kind == '=')
					 sym_table.set(t.name, expression());
				 else
					 ts.putback(t1);
				 data = sym_table.get(t.name);
				 break;
	}
		
	case sqrt_k:
		data = get_sqrt();
		break;
	case pow_k:
		data = get_pow();
		break;
	case quit:
		ts.putback(t);
		return data;
	case '-':
		return -primary();
	case '+':
		return primary();
	default:
		error("Primary Excepted");
	}
	t = ts.get();
	if (t.kind == '!')
	{
		if (data == 0)
			return 1;
		for (int j = data - 1; j > 0; j--)
			data *= j;
	}
	else
	{
		ts.putback(t);
	}
	return data;
}
double declaration(char flag)
{
	Token t = ts.get();
	if (t.kind != name)
		error("name expected in declaration");

	string var_name = t.name;

	Token t2 = ts.get();
	if (t2.kind != '=')
		error("= missing in declarations of ",var_name);
	double d = expression();
	sym_table.declare(var_name, d, flag);
	return d;
}
double get_sqrt()
{
	Token t = ts.get();
	if (t.kind != '(')
		error("In sqrt '(' expected");

	double tmp = expression();

	t = ts.get();
	if (t.kind != ')')
		error("In sqrt ')' excepted");
	if (tmp < 0)
		error("sqrt negative number");
	return sqrt(tmp);
}
double get_pow()
{
	double result = 1;
	Token t = ts.get();
	if (t.kind != '(')
		error("In pow '(' expected");

	double tmp1 = expression();

	t = ts.get();
	if (t.kind != ',')
		error("In pow ',' excepted");

	double tmp2 = narrow_cast<int>(expression());

	t = ts.get();
	if (t.kind != ')')
		error("In pow ')' excepted");

	for (int i = 0; i < tmp2; i++)
		result *= tmp1;
	return result;
}


int a()
{
	int left = b();
	Token t = ts.get();
	while (true)
	{
		if (t.kind == '|')
		{
			left |= b();
			t = ts.get();
		}
		else
		{
			ts.putback(t);
			return left;
		}
	}
}
int b()
{
	int left = c();
	Token t = ts.get();
	while (true)
	{
		if (t.kind == '^')
		{
			left ^= c();
			t = ts.get();
		}
		else
		{
			ts.putback(t);
			return left;
		}
	}
}
int c()
{
	int left = d();
	Token t = ts.get();
	while (true)
	{
		if (t.kind == '&')
		{
			left &= d();
			t = ts.get();
		}
		else
		{
			ts.putback(t);
			return left;
		}
	}
}
int d()
{
	Token t = ts.get();
	int data = 0;
	switch (t.kind)
	{
	case '(':
	{
				data = a();
				t = ts.get();
				if (t.kind != ')')
				{
					error("')' Except");
				}
				break;
	}
	case '{':
	{
				data = a();
				t = ts.get();
				if (t.kind != '}')
				{
					error("'}' Except");
				}
				break;
	}
	case '~': case '!':
	{
				  data = a();
				  if (t.kind == '~')
					  data = ~data;
				  else if (t.kind == '!')
					  data = !data;
	}
	case number:
		data = t.value;
		break;
	case quit:
		ts.putback(t);
		return data;
	default:
		error("d Except");
	}
	return data;
}