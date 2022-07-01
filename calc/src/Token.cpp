#include "../include/Token.hpp"

Token::Token()
{

}

Token::Token(std::string const &lexeme)
{
	_lexeme = lexeme;
	_type = _which_token_type(lexeme);
	if (_type == token_type::DIGIT)
		_val = stod(_lexeme);
	else
		_val = 0;
	if (_type == token_type::MINUS || \
			_type == token_type::PLUS)
		_rang = 1;
	else if (_type == token_type::MULTIPLICATION || \
			_type == token_type::DIVISION || \
			_type == token_type::DIVISION_MOD)
		_rang = 2;
	else if (_type == token_type::POWER)
		_rang = 3;
	else if (_type == token_type::FUNCTION)
		_rang = 4;
	else
		_rang = 0;
}

Token::Token(double const &result)
{
	_lexeme = std::to_string(result);
	_type = token_type::DIGIT;
	_val = result;
	_rang = 0;
}

Token::~Token() 
{}

Token::Token(Token const &copy) 
{
	*this = copy;
}

Token &Token::operator=(Token const &copy)
{
	if (this == &copy)
		return *this;
	_lexeme = copy._lexeme;
	_type = copy._type;
	_val = copy._val;
	_rang = copy._rang;
	return *this;
}

std::string const &Token::getLexem() const 
{
	return _lexeme;
}

token_type const &Token::getType() const
{
	return _type;
}

double const &Token::getVal() const
{
	return _val;
}

int const &Token::getRang() const
{
	return _rang;
}

Token Token::operator+(Token const &other)
{
	return Token(_val + other._val);
}

Token Token::operator-(Token const &other)
{
	return Token(_val - other._val);
}

Token Token::operator*(Token const &other)
{
	return Token(_val * other._val);
}

Token Token::operator/(Token const &other)
{
	if (other._val == 0)
		throw std::runtime_error("ERROR! Zero division!!!");
	return Token(_val / other._val);
}
Token Token::operator%(Token const &other)
{
	if (other._val == 0)
		throw std::runtime_error("ERROR! Zero division!!!");
	return Token(_val - other._val * ((int)(_val / other._val)));
}

Token Token::tok_power(Token const &other)
{
	return Token(std::pow(other.getVal(), getVal()));
}

Token Token::tok_sin()
{
	return Token(std::sin(getVal()));
}

Token Token::tok_cos()
{
	return Token(std::cos(getVal()));
}

Token Token::tok_tg()
{
	return Token(tok_sin()/tok_cos());
}

Token Token::tok_ctg()
{
	return Token(tok_cos()/tok_sin());
}

Token Token::tok_sqrt()
{
	return Token(sqrt(getVal()));
}

Token Token::tok_exp()
{
	return Token(exp(getVal()));
}

//private
token_type Token::_which_token_type(std::string const &lexeme)
{
	if (lexeme == "+")
		return token_type::PLUS;
	else if (lexeme == "-")
		return token_type::MINUS;
	else if (lexeme == "*")
		return token_type::MULTIPLICATION;
	else if (lexeme == "/")
		return token_type::DIVISION;
	else if (lexeme == "%")
		return token_type::DIVISION_MOD;
	else if (lexeme == "^")
		return token_type::POWER;
	else if (lexeme == "(")
		return token_type::ROUND_BRACET_OPEN;
	else if (lexeme == ")")
		return token_type::ROUND_BRACET_CLOSE;
	else if (_is_digit_double(lexeme))
		return token_type::DIGIT;
	else if (_is_func(lexeme))
		return token_type::FUNCTION;
	else if (lexeme[0] == (char)27)
		throw std::runtime_error("TOKEN ERROR! Unknown lexeme");
	else
		throw std::runtime_error("TOKEN ERROR! Unknown lexeme : |" + lexeme + "|");
}

bool Token::_is_digit_double(std::string const &lexeme) const
{
	bool point = false;
	for (const auto &symbol : lexeme)
	{
		if (symbol == '.' && point == true)
			return false;
		else if (symbol == '.')
			point = true;
		else if (!isdigit(symbol))
			return false;
	}
	return true;
}

bool Token::_is_func(std::string const &lexeme) const
{
	if (lexeme == "sin" || \
			lexeme == "cos" || \
			lexeme == "tg" || \
			lexeme == "ctg" || \
			lexeme == "sqrt" || \
			lexeme == "exp")
		return true;
	return false;
}
