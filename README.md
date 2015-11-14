#Calculator
>一个基于文法的计算器，来自于《C++程序设计原理与实践》
##文法规则
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
- Number
	- floating-point-literal 
