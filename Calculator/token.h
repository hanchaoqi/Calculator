#include "std_lib_facilities.h"


const string result = "= ";
const char number = '8';
const char print = ';';
const char quit = 'q';
const char flag_L = '0';
const char flag_A = '1';
const char help = '?';
const string prompt = "> ";

const char name = 'v';
const char let = 'L';
const string declkey = "let";

const char sqrt_k = 'S';
const string sqrtkey = "sqrt";
const char pow_k = 'P';
const string powkey = "pow";
const char const_k = 'C';
const char var_k = 'V';
const string constkey = "const";


class Token
{
public:
	char kind;
	double value;
	string name;
	Token(char ch)
		:kind(ch), value(0){}
	Token(char ch, double val)
		:kind(ch), value(val){}
	Token(char ch, string s)
		:kind(ch), name(s){}
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