#include "token.h"

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
	case print:
	case '=': case ',':
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
		if (isalpha(ch))
		{
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch)))
				s += ch;
			cin.putback(ch);
			if (s == declkey)
				return Token(let);
			else if (s == sqrtkey)
				return Token(sqrt_k);
			else if (s == powkey)
				return Token(pow_k);
			else if (s == constkey)
				return Token(const_k);
			return Token(name, s);
		}
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