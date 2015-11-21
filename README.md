#Calculator
>一个基于文法的计算器，来自于《C++程序设计原理与实践》
**算术计算器**：支持+，-，*，/，%，sqrt()，pow()，！，（，），{，}，负数，用let关键词声明变量
**逻辑计算器**：支持&，|，！，~，^，（，），{，}

##文法规则
###算术计算器
- Calculation
    - Statement
    - Print
    - Quit
    - Calculation Statement
- Statement
    - Declaration
    - Expression
- Declaration
	- "let" var_name"="Expression
- Expression
	 - Term
	 - Expression"+"Term
	 - Expression"-"Term
- Term
	- Primary
	- Term"*"Primary
	- Term"/"Primary
	- Term"%"Primary
- Primary
	- Number
	- "("Expression")"
	- Primary"!"
	- "-"Primary
	- "+"Primary
	- "sqrt""("Expression")"
	- "pow""("Expresion","Expression")"
- Number
	- floating-point-literal 

###逻辑计算器

- a
    - b
    - b"|"b
- b
    - c
    - c"^"c
- c
    - d
    - d"&"d
- d
    - num
    - "~"num
    - "!"num
    - "("a")"
    - "{"a"}"
- num
    - 0
    - 1