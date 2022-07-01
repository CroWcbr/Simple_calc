#include "../include/Lexer.hpp"

Lexer::Lexer(std::string const &input)
{
	_split(input);
	_check();
}

Lexer::~Lexer()
{}

std::vector<Token> const &Lexer::getTokens() const
{
	return _tokens;
}

void Lexer::print()
{
	_print();
}

//private
void Lexer::_addToken(std::string &tmp_lexeme)
{
	_tokens.push_back(Token(tmp_lexeme));
	tmp_lexeme.clear();
}

void Lexer::_split(std::string const &input)
{
	std::string	tmp_lexeme;

	for (int i = 0, len = input.size(); i < len; i++)
	{
		char symbol = input[i];
		if (_is_separate_symbol(symbol))
		{
			if (!(tmp_lexeme.empty()))
				_addToken(tmp_lexeme);
			if (!isspace(symbol))
			{
				tmp_lexeme += symbol;
				_addToken(tmp_lexeme);
			}
			continue;
		}
		tmp_lexeme += symbol;
	}
	if (!(tmp_lexeme.empty()))
		_addToken(tmp_lexeme);
}

bool Lexer::_is_separate_symbol(char symbol)
{
	return	symbol == '+' || \
			symbol == '-' || \
			symbol == '*' || \
			symbol == '/' || \
			symbol == '%' || \
			symbol == '^' || \
			symbol == '(' || \
			symbol == ')' || \
			isspace(symbol);
}

void Lexer::_check()
{
	int bracet = 0;

	for (int i = 0, len = _tokens.size(); i < len; i++)
	{
		token_type type_i = _tokens[i].getType();
		if (type_i == token_type::ROUND_BRACET_OPEN)
			bracet++;
		if (type_i == token_type::ROUND_BRACET_CLOSE)
			bracet--;
		if (i == 0)
			_check_first_last(i, len - 1);
		else if (i == len - 1)
			;
		else if (type_i == token_type::MINUS || \
				type_i == token_type::PLUS)
			_check_minus_plus(i);
		else if (type_i == token_type::MULTIPLICATION ||
				type_i == token_type::DIVISION ||
				type_i == token_type::DIVISION_MOD ||
				type_i == token_type::POWER)
			_check_mult_div_pow(i);
		else if (type_i == token_type::ROUND_BRACET_OPEN)
			_check_round_bracet_open(i);
		else if (type_i == token_type::ROUND_BRACET_CLOSE)
			_check_round_bracet_close(i);
		else if (type_i == token_type::DIGIT)
			_check_digit(i);
		else if (type_i == token_type::FUNCTION)
			_check_func(i);
	}
	if (bracet)
		throw std::runtime_error("PARSE ERROR in : bracket");
}

void Lexer::_check_handle_error(std::string msg, int i) const
{
	std::string where_error;
	for (int ii = 0; ii <= i; ii++)
		where_error += _tokens[ii].getLexem();
	throw std::runtime_error("PARSE ERROR in : " + where_error + " : " + msg);
}

void Lexer::_check_first_last(int i, int len) const
{
	token_type tmp = _tokens[i].getType();
	if (tmp != token_type::PLUS && \
			tmp != token_type::MINUS && \
			tmp != token_type::ROUND_BRACET_OPEN && \
			tmp != token_type::DIGIT && \
			tmp != token_type::FUNCTION)
		_check_handle_error("_check_first", i);
	
	tmp = _tokens[len].getType();
	if (tmp != token_type::ROUND_BRACET_CLOSE && \
			tmp != token_type::DIGIT)
		_check_handle_error("_check_last", len);	
}

void Lexer::_check_minus_plus(int i) const
{
	token_type type_prev = _tokens[i - 1].getType();
	if (type_prev != token_type::ROUND_BRACET_OPEN && \
			type_prev != token_type::ROUND_BRACET_CLOSE &&
			type_prev != token_type::DIGIT)
		_check_handle_error("_check_minus_plus", i);
	
	token_type type_next = _tokens[i + 1].getType();
	if (type_next != token_type::ROUND_BRACET_OPEN && \
			type_next != token_type::DIGIT && \
			type_next != token_type::FUNCTION)
		_check_handle_error("_check_minus_plus", i + 1);
}

void Lexer::_check_mult_div_pow(int i) const
{
	token_type type_prev = _tokens[i - 1].getType();
	if (type_prev != token_type::ROUND_BRACET_CLOSE && \
			type_prev != token_type::DIGIT)
		_check_handle_error("_check_mult_div_pow", i);
	
	token_type type_next = _tokens[i + 1].getType();
	if (type_next != token_type::ROUND_BRACET_OPEN && \
			type_next != token_type::DIGIT && \
			type_next != token_type::FUNCTION)
		_check_handle_error("_check_mult_div_pow", i + 1);
}

void Lexer::_check_digit(int i) const
{
	token_type type_prev = _tokens[i - 1].getType();
	if (type_prev == token_type::ROUND_BRACET_CLOSE || \
			type_prev == token_type::DIGIT ||
			type_prev == token_type::FUNCTION)
		_check_handle_error("_check_digit", i);
	
	token_type type_next = _tokens[i + 1].getType();
	if (type_next == token_type::ROUND_BRACET_OPEN || \
			type_next == token_type::DIGIT ||
			type_next == token_type::FUNCTION)
		_check_handle_error("_check_digit", i + 1);
}

void Lexer::_check_func(int i) const
{
	token_type type_prev = _tokens[i - 1].getType();
	if (type_prev == token_type::ROUND_BRACET_CLOSE || \
			type_prev == token_type::DIGIT ||
			type_prev == token_type::FUNCTION)
		_check_handle_error("_check_func", i);
	
	token_type type_next = _tokens[i + 1].getType();
	if (type_next != token_type::ROUND_BRACET_OPEN)
		_check_handle_error("_check_func", i + 1);
}

void Lexer::_check_round_bracet_open(int i) const
{
	token_type type_prev = _tokens[i - 1].getType();
	if (type_prev == token_type::DIGIT || \
			type_prev == token_type::ROUND_BRACET_CLOSE)
		_check_handle_error("_check_round_bracet_open", i);
	
	token_type type_next = _tokens[i + 1].getType();
	if (type_next != token_type::PLUS &&
			type_next != token_type::MINUS &&
			type_next != token_type::ROUND_BRACET_OPEN &&
			type_next != token_type::DIGIT &&
			type_next != token_type::FUNCTION)
		_check_handle_error("_check_round_bracet_open", i + 1);
}

void Lexer::_check_round_bracet_close(int i) const
{
	token_type type_prev = _tokens[i - 1].getType();
	if (type_prev != token_type::DIGIT && \
			type_prev != token_type::ROUND_BRACET_CLOSE)
		_check_handle_error("_check_round_bracet_close", i);
	
	token_type type_next = _tokens[i + 1].getType();
	if (type_next == token_type::DIGIT ||
			type_next == token_type::FUNCTION ||
			type_next == token_type::ROUND_BRACET_OPEN)
		_check_handle_error("_check_round_bracet_close", i + 1);
}

void Lexer::_print()
{
	std::cout << "\033[94m";
	std::cout << "LEXER: " << std::endl;
	std::cout << "\t";
	for (const auto &symbol : _tokens)
		std::cout << symbol.getLexem() << " ";
	std::cout <<  std::endl;
	std::cout << "\033[0m";
}
