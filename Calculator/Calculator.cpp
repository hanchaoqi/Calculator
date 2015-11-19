#include "std_lib_facilities.h"

const char result = '=';
const char number = '8';
const char quit = 'q';
const char flag_L = '0';
const char flag_A = '1';
const string prompt = "> ";

class Token
{
public:
	char kind;
	double value;
	Token(char ch)
		:kind(ch), value(0){}
	Token(char ch, double val)
		:kind(ch), value(val){}
};
class Token_stream
{
public:
	Token_stream();
	Token get();
	void putback(Token t);
	void ignore(char c);
private:
	bool full;
	Token buffer;
};

Token_stream ts;
//For Arithmetic Calculator
double expression();
double term();
double primary();

//For Logic Calculator
int a();
int b();
int c();
int d();

void calculate_A();
void calculate_L();
void clean_up_mess();
int main()
{
	cout << "Welcome to our simple calculator." << endl;
	cout << "Select calculator's mode(Logic calculator -- "<<flag_L<<" ,Arithmetic Calculator -- "<<flag_A<<"):" << endl;
	try
	{
		char mode;
		cin >> mode;

		if (mode == flag_L)
			calculate_L();
		else if (mode == flag_A)
			calculate_A();
		else
			error("Wrong Mode Index");
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
	cout << "Please enter expression using floating-point numbers,enter '=' end it." << endl;
	cout << "You can use '+','-','*','/','!' in expression,also you can use '(',')','{','}'." << endl;

	double val = 0;
	while (cin)
	try
	{
		Token t = ts.get();
		if (t.kind == result)
			cout << val << endl;
		else if (t.kind == quit)
			break;
		else
			ts.putback(t);
		val = expression();
	}
	catch (exception &e)
	{
		cerr << e.what() << endl;
		clean_up_mess();
	}
}
void calculate_L()
{
	cout << "Please enter expression using binary numbers,enter '=' end it." << endl;
	cout << "You can use '~','!','|','&','^' in expression,also you can use '(',')','{','}'." << endl;

	double val = 0;
	while (cin)
	try
	{
		Token t = ts.get();
		if (t.kind == result)
			cout << val << endl;
		else if (t.kind == quit)
			break;
		else
			ts.putback(t);
		val = a();
	}
	catch (exception &e)
	{
		cerr << e.what() << endl;
		clean_up_mess();
	}
}
void clean_up_mess()
{
	ts.ignore(result);
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

Token_stream::Token_stream()
	: full(false), buffer(0){}
void Token_stream::putback(Token t)
{
	if (full)
	{
		error("putback() into a full buffer");
	}
	buffer = t;
	full = true;
}
Token Token_stream::get()
{
	if (full)
	{
		full = false;
		return buffer;
	}
	char ch;
	cin >> ch;
	switch (ch)
	{
	case quit:
	case result:
	case '(': case ')': case '{': case '}':
	case '~': case '&': case '|': case '^':
	case '+': case '-': case '*': case '/': case '%':case '!':
		return Token(ch);
	case '.':
	case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
	{
				  cin.putback(ch);
				  double data;
				  cin >> data;
				  return Token(number, data);
	}
	default:
		error("Bad token");
	}
}
void Token_stream::ignore(char c)
{
	if (full&&c == buffer.kind)
	{
		full = false;
		return;
	}
	full = false;
	char ch = 0;
	while (cin >> ch)
	{
		if (ch == c)
			return;
	}
}