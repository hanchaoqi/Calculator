#include "token.h"

class Variable{
public:
	string name;
	char flag;
	double value;
	Variable(string n, double v, char f) :name(n), value(v), flag(f){}
};

class Symbol_table{
public:
	Symbol_table();
	double get(string name);
	void set(string name, double value);
	bool is_declared(string name);
	double declare(string name, double value, char flag);
private:
	vector<Variable> var_table;
};