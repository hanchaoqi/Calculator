#include "symbol_table.h"

Symbol_table::Symbol_table(){}
double Symbol_table::get(string name)
{
	for (int i = 0; i < var_table.size(); i++)
	if (var_table[i].name == name)
		return var_table[i].value;
	error("get:undefined variable ", name);
}
void Symbol_table::set(string name, double value)
{
	for (int i = 0; i < var_table.size(); i++)
	if (var_table[i].name == name)
	{
		if (var_table[i].flag == const_k)
			error("set: can't revise const variable ", name);
		var_table[i].value = value;
		return;
	}
	error("set: undefined variable ", name);
}
bool Symbol_table::is_declared(string name)
{
	for (int i = 0; i < var_table.size(); i++)
	if (var_table[i].name == name)
		return true;
	return false;
}
double Symbol_table::declare(string name, double value, char flag)
{
	if (is_declared(name))
		error(name, "declared twice");
	var_table.push_back(Variable(name, value, flag));
	return value;
}