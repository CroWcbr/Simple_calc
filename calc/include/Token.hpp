#pragma once

# include <string>
# include <iostream>
# include <cmath>

enum class token_type
{
	PLUS,					// +
	MINUS,					// -
	MULTIPLICATION,			// *
	DIVISION,				// /
	DIVISION_MOD,			// %
	POWER,					// ^
	ROUND_BRACET_OPEN,		// (
	ROUND_BRACET_CLOSE,		// )
	DIGIT,					// double
	FUNCTION				// function
};

class Token
{
private:
	std::string		_lexeme;
	token_type		_type;
	double			_val;
	int				_rang;
private:
	token_type	_which_token_type(std::string const &lexeme);
	bool		_is_digit_double(std::string const &lexeme) const;
	bool		_is_func(std::string const &lexeme) const;

public:
	Token();
	Token(std::string const &lexeme);
	Token(double const &result);
	~Token();
	Token(Token const &copy);
	Token &operator=(Token const &copy);

	std::string const	&getLexem() const;
	token_type const	&getType() const;
	double const		&getVal() const;
	int const			&getRang() const;

	Token				operator+(Token const &other);
	Token				operator-(Token const &other);
	Token				operator*(Token const &other);
	Token				operator/(Token const &other);
	Token				operator%(Token const &other);
	Token 				tok_power(Token const &other);
	Token 				tok_sin();
	Token 				tok_cos();
	Token 				tok_tg();
	Token 				tok_ctg();
	Token				tok_sqrt();
	Token				tok_exp();
};
