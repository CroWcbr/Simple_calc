#pragma once

# include <iostream>
# include <stack>
# include <signal.h>
# include <vector>
# include <cmath>
# include "Lexer.hpp"

class Calculator
{
private:
	std::stack<Token>	_st_n;
	std::stack<Token>	_st_o;
	void				math();
	void				calculate(std::vector<Token> const &token);
	void				erase_a_b(Token &a, Token &b, token_type const &t);

public:
	Calculator();
	~Calculator();
	Calculator(Calculator const &copy) = delete;
	Calculator &operator=(Calculator const &copy) = delete;

	void				analysis(std::string const &input);
};
