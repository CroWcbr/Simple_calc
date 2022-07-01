#pragma once

# include <string>
# include <vector>

# include "Token.hpp"

class Lexer
{
private:
	std::vector<Token>	_tokens;

private:
	void		_addToken(std::string &tmp_lexeme);
	void		_split(std::string const &input);
	bool		_is_separate_symbol(char symbol);


	void		_check();
	void 		_check_handle_error(std::string msg, int i) const;
	void		_check_first_last(int i, int len) const;
	void		_check_minus_plus(int i) const;
	void		_check_mult_div_pow(int i) const;

	void		_check_digit(int i) const;
	void		_check_func(int i) const;
	void		_check_round_bracet_open(int i) const;
	void		_check_round_bracet_close(int i) const;

	void		_print();

public:
	Lexer() = delete;
	Lexer(std::string const &input);
	~Lexer();
	Lexer(Lexer const &copy) = delete;
	Lexer &operator=(Lexer const &copy) = delete;

	std::vector<Token> const	&getTokens() const;
	void						print();
};
