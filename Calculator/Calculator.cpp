#include "std_lib_facilities.h"
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
private:
	bool full;
	Token buffer;
};

Token_stream ts;
double expression();
double term();
double primary();

int main()
{
	cout << "Welcome to our simple calculator." << endl;
	cout << "Please enter expression using floating-point numbers,enter '=' end it." << endl;
	cout << "You can use '+','-','*','/','!' in expression,also you can use '(',')','{','}'." << endl;
	try
	{
		double val = 0;
		while (cin)
		{
			Token t = ts.get();
			if (t.kind == '=')
				cout << val << endl;
			else if (t.kind == 'q')
				break;
			else
				ts.putback(t);
			val = expression();
		}
		keep_window_open();
	}
	catch (exception &e)
	{
		cerr << "Error: " << e.what() << endl;
		keep_window_open();
		return 1;
	}
	catch (...)
	{
		cerr << "unkown exception"<< endl;
		keep_window_open();
		return 2;
	}
	return 0;
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
	case '8':
		data = t.value;
		break;
	case 'q':
		ts.putback(t);
		return data;
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
	case 'q':
	case '=':
	case '(': case ')': case '+': case '-': case '*': case '/': case '%': case '{': case '}': case '!':
		return Token(ch);
	case '.':
	case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
	{
				  cin.putback(ch);
				  double data;
				  cin >> data;
				  return Token('8', data);
	}
	default:
		error("Bad token");
	}
}